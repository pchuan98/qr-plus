#ifndef _SPI_INIT_H_
#define _SPI_INIT_H_

#include "Arduino.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define EPD_SCK 14
#define EPD_MOSI 15
#define EPD_RES 16
#define EPD_DC 17
#define EPD_CS 18
#define EPD_BUSY 13

#define EPD_SCK_Clr() digitalWrite(EPD_SCK, LOW)
#define EPD_SCK_Set() digitalWrite(EPD_SCK, HIGH)

#define EPD_MOSI_Clr() digitalWrite(EPD_MOSI, LOW)
#define EPD_MOSI_Set() digitalWrite(EPD_MOSI, HIGH)

#define EPD_RES_Clr() digitalWrite(EPD_RES, LOW)
#define EPD_RES_Set() digitalWrite(EPD_RES, HIGH)

#define EPD_DC_Clr() digitalWrite(EPD_DC, LOW)
#define EPD_DC_Set() digitalWrite(EPD_DC, HIGH)

#define EPD_CS_Clr() digitalWrite(EPD_CS, LOW)
#define EPD_CS_Set() digitalWrite(EPD_CS, HIGH)

#define EPD_ReadBusy digitalRead(EPD_BUSY)

void EPD_GPIOInit(void);   // ?????EPD???GPIO??
void EPD_WR_Bus(u8 dat);   // ?????????
void EPD_WR_REG(u8 reg);   // ??????
void EPD_WR_DATA8(u8 dat); // ???????

#endif
