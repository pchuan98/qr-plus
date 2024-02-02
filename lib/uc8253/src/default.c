/****************************************************************
 * @file        :   default.c
 * @version     :   1.0.0
 * @date        :   2024-02-01 10:17:41
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   全局变量的初始化
 ****************************************************************/

#include "default.h"

uc8253_data_psr_t psr_data_g = {
    .res1 = 0,
    .res2 = 0,
    .reg = 0,
    .kwr = 1,
    .ud = 1,
    .shl = 0,
    .shd = 1,
    .rst = 1,
};

uc8253_data_ccset_t ccset_data_g = {
    .ccen = 0,
    .tsfix = 1,
};