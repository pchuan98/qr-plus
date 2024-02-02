/****************************************************************
 * @file        :   command.h
 * @version     :   1.0.0
 * @date        :   2024-01-31 16:59:35
 * @author      :   chuan
 * @copyright   :   MIT LICENSE
 * @brief       :   The Command Enum for UC8253
 ****************************************************************/

#ifndef _H_UC8253_COMMAND_
#define _H_UC8253_COMMAND_

/**
 * @brief
 * the command for UC8253c
 */
typedef enum
{
    /**
     * @brief Pannel Setting (Register R00H)
     */
    UC8253_C_PSR = 0x00,

    /**
     * @brief Power Setting (R01hH)
     */
    UC8253_C_PWR = 0x01,

    /**
     * @brief Power off
     *
     * After the Power OFF command, the driver will be powered OFF. Refer to the POWER MANAGEMENT section for the sequence.
     */
    UC8253_C_POF = 0x02,

    /**
     * @brief Power off sequence setting
     */
    UC8253_C_PFS = 0x03,

    /**
     * @brief Power on
     *
     * After the Power ON command, the driver will be powered ON. Refer to the POWER MANAGEMENT section for the sequence.
     */
    UC8253_C_PON = 0x04,

    /**
     * @brief Power on measure
     *
     * This command enables the internal bandgap, which will be cleared by the next POF.
     */
    UC8253_C_PMES = 0x05,

    /**
     * @brief Booster soft start
     *
     * This command starts the phase 1 voltage transition of the booster capacitor.
     */
    UC8253_C_BTST = 0x06,

    /**
     * @brief Deep sleep
     *
     * After this command is transmitted, the chip will enter Deep Sleep Mode to save power.
     * Deep Sleep Mode will return to Standby Mode by hardware reset.
     * The only one parameter is a check code, the command will be executed if check UC8253_C_code = 0xA5.
     */
    UC8253_C_DSLP = 0x07,

    /**
     * @brief Data start transmission 1
     *
     * This command starts transmitting data and write them into SRAM.
     *
     * In KW mode, this command writes “OLD” data to SRAM.
     * In KWR mode, this command writes “B/W” data to SRAM.
     * In Program mode, this command writes “OTP” data to SRAM for programming.
     */
    UC8253_C_DTM1 = 0x10,

    /**
     * @brief Data stop
     *
     * Check the completeness of data. If data is complete, start to refresh display.
     */
    UC8253_C_DSP = 0x11,

    /**
     * @brief Display Refresh
     *
     * While user sent this command, driver will refresh display (data/VCOM) according to SRAM data and LUT.
     * After Display Refresh command, BUSY_N signal will become "0" and the refreshing of panel starts.
     * The waiting interval form BUSY_N falling to the first FLG command must be larger than 200us.
     */
    UC8253_C_DRF = 0x12,

    /**
     * @brief Data start transmission 2
     *
     * This command starts transmitting data and write them into SRAM.
     * In KW mode, this command writes "NEW" data to SRAM.
     * In KWR mode, this command writes "RED" data to SRAM.
     */
    UC8253_C_DTM2 = 0x13,

    /**
     * @brief Auto Sequence
     *
     * The command can enable the internal sequence to execute several commands continuously. The successive execution can
     * minimize idle time to avoid unnecessary power consumption and reduce the complexity of host’s control procedure. The
     * sequence contains several operations, including PON, DRF, POF, DSLP.
     *
     * AUTO (0x17) + Code(0xA5) = (PON -> DRF -> POF)
     * AUTO (0x17) + Code(0xA7) = (PON -> DRF -> POF -> DSLP)
     */
    UC8253_C_AUTO = 0x17,

    /**
     * @brief VCOM LUT
     *
     * This command stores VCOM Look-Up Table with 8 groups of data. This LUT includes 8 kinds of groups; each group is of 7 bytes.
     * Each group is divied to 2states and group repeat number. Each state made up 2 phases and each phase is combined with repeat
     * time, level selection and frame number.
     */
    UC8253_C_LUTC = 0x20,

    /**
     * @brief W2W LUT
     *
     * This command stores LUTW2W Look-Up Table with 6 groups of data. This LUT includes 6 kinds of groups; each group is of 7
     * bytes. Each group is divied to 2states and group repeat number. Each state made up 2 phases and each phase is combined with
     * repeat time, level selection and frame number.
     */
    UC8253_C_LUTWW = 0x21,

    // todo 添加注释

    UC8253_C_LUTKW = 0x22,
    UC8253_C_LUTW = 0x23,
    UC8253_C_KUTKK = 0x24,
    UC8253_C_LUTK = 0x24,
    UC8253_C_LUTOPT = 0x2a,
    UC8253_C_PLL = 0x30,
    UC8253_C_TSC = 0x40,
    UC8253_C_TSE = 0x41,
    UC8253_C_TSW = 0x42,
    UC8253_C_TSR = 0x43,
    UC8253_C_PBC = 0x44,
    UC8253_C_CDI = 0x50,

    UC8253_C_LPD = 0x51,
    UC8253_C_TCON = 0x60,
    UC8253_C_TRES = 0x61,
    UC8253_C_GSST = 0x65,
    UC8253_C_REV = 0x70,
    UC8253_C_FLG = 0x71,
    UC8253_C_CRC = 0x71,
    UC8253_C_AWV = 0x80,
    UC8253_C_VV = 0x81,
    UC8253_C_VDCS = 0x82,
    UC8253_C_PTL = 0x90,
    UC8253_C_PTIN = 0x91,
    UC8253_C_PTOUT = 0x92,
    UC8253_C_PGM = 0xa0,
    UC8253_C_APG = 0xa1,
    UC8253_C_ROTP = 0xa2,

    /**
     * @brief CASCADE SETTING
     * This command is used for cascade.
     */
    UC8253_C_CCSET = 0xE0,
    UC8253_C_PWS = 0xE3,
    UC8253_C_LVSEL = 0xE4,

    /**
     * @brief FORCE TEMPERATURE
     *
     * This command is used for cascade to fix the temperature value of master and slave chip.
     */
    UC8253_C_TSSET = 0xE5,
} uc8253_command_t;

#endif /* _H_UC8253_COMMAND_ */