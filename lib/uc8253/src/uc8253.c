/****************************************************************
 * @file        :   uc8253.c
 * @version     :   1.0.0
 * @date        :   2024-01-22 23:59:09
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   the implementation of epd
 ****************************************************************/

#include "uc8253.h"
#include "esp_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HSPI_HOST SPI2_HOST

uc8253_pinmap_t pinmap_g;

uc8253_t *uc8253_init(spi_host_device_t host, uc8253_pinmap_t pinmap)
{
    uc8253_t *result = malloc(sizeof(uc8253_t));
    if (result == NULL)
        return NULL;

    result->host = host;
    result->pinmap = pinmap;

    return result;
}

void detect(esp_err_t msg)
{
    if (msg != ESP_OK)
    {
        ESP_LOGE("uc8253", "detect error: %s", esp_err_to_name(msg));
        return;
    }
    else
    {
        ESP_LOGI("uc8253", "detect success");
    }
}

void spi_send_cmd(spi_device_handle_t spi, const uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t;
    gpio_set_level(pinmap_g.dc, 0);
    gpio_set_level(pinmap_g.cs, 0);
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &cmd;
    t.user = (void *)0;
    ret = spi_device_polling_transmit(spi, &t);
    gpio_set_level(pinmap_g.cs, 1);
    detect(ret);
}

void spi_send_data(spi_device_handle_t spi, const uint8_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    gpio_set_level(pinmap_g.dc, 1);
    gpio_set_level(pinmap_g.cs, 0);
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;
    t.user = (void *)1;
    ret = spi_device_polling_transmit(spi, &t);
    gpio_set_level(pinmap_g.cs, 1);
    detect(ret);
}

void test()
{
    esp_err_t ret;

    uc8253_pinmap_t pinmap = {
        .busy = 13,
        .reset = 16,
        .dc = 15,
        .cs = 14,
        .clk = 18,
        .mosi = 17,
        .miso = -1,
    };

    pinmap_g = pinmap;

    gpio_config_t ioc = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << pinmap_g.busy) |
                        (1ULL << pinmap_g.reset) |
                        (1ULL << pinmap_g.dc) |
                        (1ULL << pinmap_g.cs),
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    ret = gpio_config(&ioc);
    detect(ret);

    gpio_set_level(pinmap_g.busy, 1);
    gpio_set_level(pinmap_g.reset, 1);
    gpio_set_level(pinmap_g.dc, 1);

    spi_bus_config_t busc = {
        .mosi_io_num = pinmap_g.mosi,
        .sclk_io_num = pinmap_g.clk,
        .miso_io_num = pinmap_g.miso,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 64 * 8,
    };
    ret = spi_bus_initialize(HSPI_HOST, &busc, 0);
    detect(ret);

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = SPI_MASTER_FREQ_20M,
        .mode = 0,
        .queue_size = 7,
        .spics_io_num = -1,
    };

    spi_device_handle_t spi;

    ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    detect(ret);
}