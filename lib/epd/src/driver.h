/****************************************************************
 * @file        :   driver.h
 * @version     :   1.0.0
 * @date        :   2024-01-29 00:04:34
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   the driver file for UC8253c
 ****************************************************************/

#ifndef _H_HEADER_NAME_
#define _H_HEADER_NAME_

/**
 * @brief source x gate
 * @remark w/d
 */
typedef enum _EpdPanelSize
{
    /**
     * @brief
     * Active gate channels: G0 - G249, active source channels: S0 - S119
     */
    S240x120 = 0x00b, // default

    S320x160 = 0x01b, // Current using...
    S400x200 = 0x10b,
    S480x240 = 0x11b,
} EpdPanelSize;

/**
 * @brief 执行PSR命令后设置参数
 * @cond ssd1675
 */
typedef struct _PSRConfig
{
    /**
     * @brief display resolution setting (source x gate)
     *
     */
    int RES;
} psr_config;

/**
 * @brief
 *
 */
typedef enum _EpdCommand
{
    /**
     * @brief Pannel Setting (Register R00H)
     * @remark w/c
     */
    PSR = 0x00,

    /**
     * @brief Power Setting (R01hH)
     * @remark w/c
     */
    PWR = 0x01,

    /**
     * @brief Power off
     * After the Power OFF command, the driver will be powered OFF. Refer to the POWER MANAGEMENT section for the sequence.
     * @remark w/c
     */
    POF = 0x02,

    /**
     * @brief Power off sequence setting
     * @remark w/c
     */
    PFS = 0x03,

    /**
     * @brief Power on
     * After the Power ON command, the driver will be powered ON. Refer to the POWER MANAGEMENT section for the sequence.
     * @remark w/c
     */
    PON = 0x04,

    /**
     * @brief Power on measure
     * This command enables the internal bandgap, which will be cleared by the next POF.
     * @remark w/c
     */
    PMES = 0x05,

    /**
     * @brief Booster soft start
     * This command starts the phase 1 voltage transition of the booster capacitor.
     * @remark w/c
     */
    BTST = 0x06,

    /**
     * @brief Deep sleep
     * After this command is transmitted, the chip will enter Deep Sleep Mode to save power.
     * Deep Sleep Mode will return to Standby Mode by hardware reset.
     * The only one parameter is a check code, the command will be executed if check code = 0xA5.
     * @remark w/c
     */
    DSLP = 0x07,

    /**
     * @brief Data start transmission 1
     * This command starts transmitting data and write them into SRAM.
     *
     * In KW mode, this command writes “OLD” data to SRAM.
     * In KWR mode, this command writes “B/W” data to SRAM.
     * In Program mode, this command writes “OTP” data to SRAM for programming.
     */
    DTM1 = 0x10,

    /**
     * @brief Data stop
     * Check the completeness of data. If data is complete, start to refresh display.
     */
    DSP = 0x11,

} EpdCommand;

/**
 * @remark w/d
 *
 */
typedef enum _EdpSleepValid
{
    SleepCheckCode = 0xA5,
} EdpSleepValid;

#endif /* _H_HEADER_NAME_ */