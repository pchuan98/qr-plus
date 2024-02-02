#include "SPI_Init.h"

void EPD_GPIOInit(void)
{
	pinMode(EPD_SCK, OUTPUT);
	pinMode(EPD_MOSI, OUTPUT);
	pinMode(EPD_RES, OUTPUT);
	pinMode(EPD_DC, OUTPUT);
	pinMode(EPD_CS, OUTPUT);
	pinMode(EPD_BUSY, INPUT);
}

void EPD_WR_Bus(u8 dat)
{
	u8 i;
	EPD_CS_Clr();
	for (i = 0; i < 8; i++)
	{
		EPD_SCK_Clr();
		if (dat & 0x80)
		{
			EPD_MOSI_Set();
		}
		else
		{
			EPD_MOSI_Clr();
		}
		EPD_SCK_Set();
		dat <<= 1;
	}
	EPD_CS_Set();
}

void EPD_WR_REG(u8 reg)
{
	EPD_DC_Clr();
	EPD_WR_Bus(reg);
	EPD_DC_Set();
}
void EPD_WR_DATA8(u8 dat)
{
	EPD_DC_Set();
	EPD_WR_Bus(dat);
	EPD_DC_Set();
}
