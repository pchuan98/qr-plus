/****************************************************************
 * @file        :   uc8253.c
 * @version     :   1.0.0
 * @date        :   2024-01-22 23:59:09
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   the implementation of epd
 ****************************************************************/

#include "uc8253.h"

uc8253_t *uc8253_init(spi_host_device_t host, uc8253_pinmap_t pinmap)
{
    uc8253_t *result = malloc(sizeof(uc8253_t));
    if (result == NULL)
        return NULL;

    result->host = host;
    result->pinmap = pinmap;

    return result;
}