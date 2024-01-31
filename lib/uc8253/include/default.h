/****************************************************************
 * @file        :   default.h
 * @version     :   1.0.0
 * @date        :   2024-01-31 17:12:58
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   一些默认的设置
 ****************************************************************/

#ifndef _H_UC8253_DEFAULT_
#define _H_UC8253_DEFAULT_

#include "command.h"
#include "data.h"

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

#endif /* _H_UC8253_DEFAULT_ */