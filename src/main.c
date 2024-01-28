/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver.h"
#include "demo.h"

void app_main(void)
{
    DemoRun();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // esp_restart();
}

/****************************************************************
 * @file        :   main.c
 * @version     :   1.0.0
 * @date        :   2024-01-22 23:53:11
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   brief
 ****************************************************************/
