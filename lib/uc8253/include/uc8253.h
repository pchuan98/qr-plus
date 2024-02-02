/****************************************************************
 * @file        :   uc8253.h
 * @version     :   1.0.0
 * @date        :   2024-01-22 23:54:13
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   墨水屏相关代码
 ****************************************************************/

#ifndef _H_EPD_
#define _H_EPD_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_log.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "command.h"
#include "data.h"
#include "default.h"

#define HSPI_HOST SPI2_HOST

/**
 * @brief pin map for uc8253
 *
 */
typedef struct
{
    gpio_num_t clk;   // 0: low, 1: high
    gpio_num_t mosi;  // 0: low, 1: high
    gpio_num_t miso;  // 0: low, 1: high
    gpio_num_t dc;    // 0: command, 1: data
    gpio_num_t cs;    // 0: select, 1: unselect
    gpio_num_t reset; // 0: reset, 1: normal
    gpio_num_t busy;  // 0: busy, 1: idle
} uc8253_pinmap_t;

typedef struct
{
    spi_host_device_t host;
    spi_device_handle_t device;
    uc8253_pinmap_t pinmap;
    uint16_t height;
    uint16_t width;
} uc8253_t;

// ########################################################################
// The global variables
// ########################################################################

#define WHITE 0xFF
#define BLACK 0x00

// todo the old image and image data

// ########################################################################

/**
 * @brief init the uc8253
 *
 * @param host
 * @param pinmap
 * @return uc8253_t*
 */
uc8253_t *uc8253_init(spi_host_device_t host, uc8253_pinmap_t pinmap);

/**
 * @brief init the display panel
 *
 * @param uc8253
 * @param psr_data
 */
void uc8253_set_pannel(uc8253_t *uc8253, uc8253_data_psr_t psr_data);

/**
 * @brief the hardware reset
 *
 * This method needs to be called to reset E-Paper after entering the Deepsleep state.
 * @param uc8253
 */
void uc8253_reset(uc8253_t *uc8253);

/**
 * @brief update the display to the screen
 *
 * @param uc8253
 */
void uc8253_update(uc8253_t *uc8253);

/**
 * @brief clear the screen
 *
 * @param uc8253
 * @param color
 */
void uc8253_clear(uc8253_t *uc8253, uint8_t color);

/**
 * @brief fast refresh
 *
 * @param uc8253
 */
void uc8253_fast_refresh(uc8253_t *uc8253);

/**
 * @brief part refresh
 *
 * @param uc8253
 */
void uc8253_part_refresh(uc8253_t *uc8253);

void test();

#endif /* _H_EP D_ */