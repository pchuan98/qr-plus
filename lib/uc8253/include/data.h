/****************************************************************
 * @file        :   data.h
 * @version     :   1.0.0
 * @date        :   2024-01-31 17:00:31
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   The Data Follows the Command
 ****************************************************************/
#ifndef _H_UC8253_DATA_
#define _H_UC8253_DATA_

#include "config.h"

/**
 * @brief Follow the Command UC8253_C_PSR
 *
 */
typedef struct
{
    /**
     * @brief Display Resolution setting (source x gate)
     *
     * 00b: 240x120
     * 01b: 320x160
     * 10b: 400x200
     * 11b: 480x240
     */
    u32 res1 : 1;

    /**
     * @brief Display Resolution setting (source x gate)
     *
     * 00b: 240x120
     * 01b: 320x160
     * 10b: 400x200
     * 11b: 480x240
     */
    u32 res2 : 1;

    /**
     * @brief LUT selection
     *
     * 0: LUT from OTP. (Default)
     * 1: LUT from register.
     */
    u32 reg : 1;

    /**
     * @brief Black / White / Red
     *
     * 0: Pixel with Black/White/Red, KWR mode. (Default)
     * 1: Pixel with Black/White, KW mode.
     */
    u32 kwr : 1;

    /**
     * @brief Gate Scan Direction
     *
     * 0: Scan down.            First line to Last line: Gn1->Gn2->Gn3->...->G0
     * 1: Scan up. (Default)    First line to Last line: G0->G1->G2->...->Gn-1
     */
    u32 ud : 1;

    /**
     * @brief Source Shift Direction
     * 0: Shift left.               First data to Last data: Sn1->Sn2->Sn3->...->S0
     * 1: Shift right. (Default)    First data to Last data: S0->S1->S2->...->Sn-1
     */
    u32 shl : 1;

    /**
     * @brief Booster Switch
     *
     * 0: Booster OFF
     * 1: Booster ON  (Default)
     *
     * When SHD_N becomes LOW, charge pump will be turned OFF,
     * register and SRAM data will keep until VDD OFF.
     * And Source/Gate/Border/VCOM will be released to floating.
     */
    u32 shd : 1;

    /**
     * @brief Soft Reset
     *
     * 0: Reset.
     * Booster OFF, Register data are set to their default values,
     * all drivers will be reset, and all functions will be disabled.
     * Source/Gate/Border/VCOM will be released to floating.
     * After soft reset is transmitted, the internal operation needs at least 50uS to execute.
     * During this period of time, the BUSY_N pin keeps low and any command will be ignored.
     *
     * 1: No effect  (Default).
     */
    u32 rst : 1;

} uc8253_data_psr_t;

#endif /* _H_UC8253_DATA_ */