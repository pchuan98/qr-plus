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

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "command.h"
#include "data.h"
#include "default.h"

/**
 * @brief pin map for uc8253
 *
 */
typedef struct
{
    gpio_num_t busy;  // 0: busy, 1: idle
    gpio_num_t reset; // 0: reset, 1: normal
    gpio_num_t dc;    // 0: command, 1: data
    gpio_num_t cs;    // 0: select, 1: unselect
    gpio_num_t clk;   // 0: low, 1: high
    gpio_num_t mosi;  // 0: low, 1: high
    gpio_num_t miso;  // 0: low, 1: high

} uc8253_pinmap_t;

typedef struct
{
    spi_host_device_t host;
    spi_device_handle_t device;
    uc8253_pinmap_t pinmap;
} uc8253_t;

/**
 * @brief init the uc8253
 *
 * @param host
 * @param pinmap
 * @return uc8253_t*
 */
uc8253_t *uc8253_init(spi_host_device_t host, uc8253_pinmap_t pinmap);

#endif /* _H_EPD_ */