#ifndef _EPD_H_
#define _EPD_H_

#include "SPI_Init.h"

#define EPD_W	240 
#define EPD_H	416

#define WHITE 0xFF
#define BLACK 0x00
#define RED   BLACK


#define Source_BITS    240
#define Source_BYTES    30
#define Gate_BITS   416  
#define ALLSCREEN_BYTES   12480


void EPD_READBUSY(void);
void EPD_HW_RESET(void);
void EPD_Update(void);
void EPD_DeepSleep(void);
void EPD_Init(void);
void EPD_Display_Clear(void);
void EPD_Display(const u8 *imageBW,const u8 *imageR);
#endif




