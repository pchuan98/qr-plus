#ifndef _SPI_INIT_H_
#define _SPI_INIT_H_

#include "stm32f10x.h"


#define EPD_SCL_GPIO_PORT		GPIOG
#define EPD_SCL_GPIO_PIN		GPIO_Pin_12	
#define EPD_SCL_GPIO_CLK		RCC_APB2Periph_GPIOG

#define EPD_SDA_GPIO_PORT		GPIOD
#define EPD_SDA_GPIO_PIN		GPIO_Pin_5	
#define EPD_SDA_GPIO_CLK		RCC_APB2Periph_GPIOD

#define EPD_RES_GPIO_PORT		GPIOD
#define EPD_RES_GPIO_PIN		GPIO_Pin_4	
#define EPD_RES_GPIO_CLK		RCC_APB2Periph_GPIOD

#define EPD_DC_GPIO_PORT		GPIOD
#define EPD_DC_GPIO_PIN			GPIO_Pin_15	
#define EPD_DC_GPIO_CLK			RCC_APB2Periph_GPIOD

#define EPD_CS_GPIO_PORT		GPIOD
#define EPD_CS_GPIO_PIN			GPIO_Pin_1	
#define EPD_CS_GPIO_CLK			RCC_APB2Periph_GPIOD

#define EPD_BUSY_GPIO_PORT	GPIOE
#define EPD_BUSY_GPIO_PIN		GPIO_Pin_8	
#define EPD_BUSY_GPIO_CLK		RCC_APB2Periph_GPIOE

#define EPD_SCL_Clr() GPIO_ResetBits(EPD_SCL_GPIO_PORT,EPD_SCL_GPIO_PIN)
#define EPD_SCL_Set() GPIO_SetBits(EPD_SCL_GPIO_PORT,EPD_SCL_GPIO_PIN)

#define EPD_SDA_Clr() GPIO_ResetBits(EPD_SDA_GPIO_PORT,EPD_SDA_GPIO_PIN)
#define EPD_SDA_Set() GPIO_SetBits(EPD_SDA_GPIO_PORT,EPD_SDA_GPIO_PIN)

#define EPD_RES_Clr() GPIO_ResetBits(EPD_RES_GPIO_PORT,EPD_RES_GPIO_PIN)
#define EPD_RES_Set() GPIO_SetBits(EPD_RES_GPIO_PORT,EPD_RES_GPIO_PIN)

#define EPD_DC_Clr() GPIO_ResetBits(EPD_DC_GPIO_PORT,EPD_DC_GPIO_PIN)
#define EPD_DC_Set() GPIO_SetBits(EPD_DC_GPIO_PORT,EPD_DC_GPIO_PIN)

#define EPD_CS_Clr() GPIO_ResetBits(EPD_CS_GPIO_PORT,EPD_CS_GPIO_PIN)
#define EPD_CS_Set() GPIO_SetBits(EPD_CS_GPIO_PORT,EPD_CS_GPIO_PIN)

#define EPD_ReadBusy GPIO_ReadInputDataBit(EPD_BUSY_GPIO_PORT,EPD_BUSY_GPIO_PIN)


void EPD_GPIOInit(void);  //��ʼ��EPD��ӦGPIO��
void EPD_WR_Bus(u8 dat);	//д��һ���ֽ�
void EPD_WR_REG(u8 reg);	//д��ָ��
void EPD_WR_DATA8(u8 dat);//д������

#endif



