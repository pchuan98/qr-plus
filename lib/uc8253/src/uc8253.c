/****************************************************************
 * @file        :   uc8253.c
 * @version     :   1.0.0
 * @date        :   2024-01-22 23:59:09
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   the implementation of epd
 ****************************************************************/

#include "uc8253.h"

// ########################################################################
// The tools and spi functions
// ########################################################################

/**
 * @brief reverse the bits data
 *
 * @param num
 * @return unsigned char
 */
uint8_t reverse_bits(uint8_t num)
{
    uint8_t result = 0;

    for (int i = 0; i < 8; i++)
    {
        result = (result << 1) | (num & 1);
        num >>= 1;
    }

    return result;
}

/**
 * @brief detect the error
 *
 * @param msg the message to print
 */
void detect(char *msg, esp_err_t err)
{
    if (err != ESP_OK)
    {
        ESP_LOGE("uc8253", "detect error in %s: %s", msg, esp_err_to_name(err));
        return;
    }
    else
        ESP_LOGI("uc8253", "detect success in %s", msg);
}

/**
 * @brief delay ms
 *
 * @param ms the time to delay
 */
void delay_ms(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

/**
 * @brief delay s
 *
 * @param s the time to delay
 */
void delay_s(uint32_t s)
{
    vTaskDelay(s * 1000 / portTICK_PERIOD_MS);
}

/**
 * @brief detect the busy pin
 *
 */
void wait_busy(uc8253_t *uc8253)
{
    while (gpio_get_level(uc8253->pinmap.busy) == 0)
    {
        delay_ms(100);
    }
}

/**
 * @brief send the command
 *
 * @param uc8253
 * @param cmd
 */
void send_command(uc8253_t *uc8253, const uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t;
    gpio_set_level(uc8253->pinmap.dc, 0);
    gpio_set_level(uc8253->pinmap.cs, 0);
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &cmd;
    t.user = (void *)0;
    ret = spi_device_polling_transmit(uc8253->device, &t);
    gpio_set_level(uc8253->pinmap.cs, 1);
    assert(ret == ESP_OK);
}

/**
 * @brief send the data
 *
 * @param uc8253
 * @param data
 */
void send_data(uc8253_t *uc8253, const uint8_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    gpio_set_level(uc8253->pinmap.dc, 1);
    gpio_set_level(uc8253->pinmap.cs, 0);
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;
    t.user = (void *)1;
    ret = spi_device_polling_transmit(uc8253->device, &t);
    gpio_set_level(uc8253->pinmap.cs, 1);
    assert(ret == ESP_OK);
}
// ########################################################################

uc8253_t *uc8253_init(spi_host_device_t host, uc8253_pinmap_t pinmap)
{
    esp_err_t err;
    uc8253_t *result = malloc(sizeof(uc8253_t));
    if (result == NULL)
        return NULL;

    result->host = host;
    result->pinmap = pinmap;

    // init gpio
    gpio_config_t gpioc = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask =
            (1ULL << pinmap.reset) |
            (1ULL << pinmap.dc) |
            (1ULL << pinmap.cs),
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    err = gpio_config(&gpioc);
    detect("gpio-all", err);

    gpioc.pin_bit_mask = (1ULL << pinmap.busy);
    gpioc.mode = GPIO_MODE_INPUT;
    err = gpio_config(&gpioc);
    detect("gpio-busy", err);

    gpio_set_level(pinmap.busy, 1);
    gpio_set_level(pinmap.reset, 1);
    gpio_set_level(pinmap.dc, 1);

    // init spi
    spi_bus_config_t busc = {
        .mosi_io_num = pinmap.mosi,
        .sclk_io_num = pinmap.clk,
        .miso_io_num = pinmap.miso,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 64 * 8,
    };
    err = spi_bus_initialize(HSPI_HOST, &busc, 0);
    detect("spi-bus", err);

    // init spi device
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = SPI_MASTER_FREQ_20M,
        .mode = 0,
        .queue_size = 7,
        .spics_io_num = -1,
    };

    spi_device_handle_t spi;
    err = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    detect("spi-device", err);

    result->device = spi;

    // todo 传入参数
    result->height = 415;
    result->width = 240;

    return result;
}

void uc8253_set_pannel(uc8253_t *uc8253, uc8253_data_psr_t psr_data)
{
    wait_busy(uc8253);
    send_command(uc8253, UC8253_C_PSR);
    wait_busy(uc8253);
    uint8_t data = *((uint8_t *)&psr_data);
    data = reverse_bits(data);
    send_data(uc8253, data);
}

void uc8253_reset(uc8253_t *uc8253)
{
    delay_ms(100);
    gpio_set_level(uc8253->pinmap.reset, 0);
    delay_ms(20);
    gpio_set_level(uc8253->pinmap.reset, 1);
    wait_busy(uc8253);
}

void uc8253_clear(uc8253_t *uc8253, uint8_t color)
{
    uint16_t cols = (uc8253->width % 8 == 0)
                        ? (uc8253->width / 8)
                        : (uc8253->width / 8 + 1);
    uint16_t rows = uc8253->height;

    wait_busy(uc8253);
    send_command(uc8253, UC8253_C_DTM1);
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            send_data(uc8253, color);

    wait_busy(uc8253);
    send_command(uc8253, UC8253_C_DTM2);
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            send_data(uc8253, color);

    uc8253_update(uc8253);
}

void uc8253_update(uc8253_t *uc8253)
{
    wait_busy(uc8253);
    send_command(uc8253, UC8253_C_PON);
    wait_busy(uc8253);
    send_command(uc8253, UC8253_C_DRF);
}

void uc8253_fast_refresh(uc8253_t *uc8253)
{
    uc8253_set_pannel(uc8253, psr_data_g);

    send_command(uc8253, UC8253_C_CCSET);
    uint8_t data = 0;
    data |= ccset_data_g.ccen << 0;
    data |= ccset_data_g.tsfix << 1;
    send_data(uc8253, data);

    send_command(uc8253, UC8253_C_TSSET);
    send_data(uc8253, UC8253_D_FAST_TEMPERATURE);
}

void uc8253_part_refresh(uc8253_t *uc8253)
{
    uc8253_set_pannel(uc8253, psr_data_g);

    send_command(uc8253, UC8253_C_CCSET);
    uint8_t data = 0;
    data |= ccset_data_g.ccen << 0;
    data |= ccset_data_g.tsfix << 1;
    send_data(uc8253, data);

    send_command(uc8253, UC8253_C_TSSET);
    send_data(uc8253, UC8253_D_PART_TEMPERATURE);
}

void test()
{
    uc8253_pinmap_t pinmap = {
        .busy = 13,
        .reset = 16,
        .dc = 15,
        .cs = 14,
        .clk = 18,
        .mosi = 17,
        .miso = -1,
    };

    uc8253_t *uc8253 = uc8253_init(HSPI_HOST, pinmap);

    // reset
    uc8253_reset(uc8253);
    uc8253_set_pannel(uc8253, psr_data_g);

    for (int i = 0; i < 10; i++)
    {
        uc8253_clear(uc8253, WHITE);
        ESP_LOGI("uc8253", "clear white");
        delay_s(5);
        uc8253_clear(uc8253, BLACK);
        ESP_LOGI("uc8253", "clear black");
        delay_s(5);
    }
}