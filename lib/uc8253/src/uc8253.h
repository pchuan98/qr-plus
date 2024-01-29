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

#include "uc8253_common.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

typedef struct
{
    /**
     * @brief
     *
     */
    gpio_num_t busy;

    /**
     * @brief
     *
     */
    gpio_num_t reset;

    /**
     * @brief
     *
     */
    gpio_num_t dc;

    /**
     * @brief
     *
     */
    gpio_num_t cs;

} uc8253_pinmap_t;

typedef struct
{
    /**
     * @brief
     *
     */
    spi_host_device_t host;

    /**
     * @brief
     *
     */
    spi_device_handle_t device;

    /**
     * @brief
     *
     */
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