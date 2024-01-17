//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : ZhaoJian
//  ��������   : 2023-11-30
//  ����޸�   : 
//  ��������   :��ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   3.3v��Դ
//              SCL   PG12��SCLK��
//              SDA   PD5��MOSI��
//              RES   PD4
//              DC    PD15
//              CS    PD1
//              BLK   PE8
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : ZhaoJian
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2023-11-30
//All rights reserved
//******************************************************************************/

#include "delay.h"
#include "usart.h"
#include "EPD_GUI.h"
#include "Pic.h"


u8 ImageBW[5624];
u8 ImageR[5624];
int main()
{
	u8 dat=0;
	float num=12.05;
	delay_init();
	uart_init(115200);
	EPD_GPIOInit();	
	printf("OK\r\n");
	EPD_Init();
	Paint_NewImage(ImageBW,EPD_W,EPD_H,0,WHITE);		//��������
  Paint_Clear(WHITE);															//��ջ�������
  Paint_NewImage(ImageR,EPD_W,EPD_H,0,WHITE);			//��������
  Paint_Clear(WHITE);															//��ջ�������
	/************************ȫˢ************************/
	EPD_Init();
	EPD_Display_Clear();
	EPD_Update();
	EPD_DeepSleep();
	printf("Clear-OK\r\n");
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	EPD_Init();
	EPD_Display(ImageBW,gImage_1);
	EPD_Update();
	EPD_DeepSleep();
	printf("RED_Picture-OK\r\n");
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	EPD_Init();
	EPD_Display(ImageBW,gImage_1);
	EPD_Update();
	EPD_DeepSleep();
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
  Paint_Clear(WHITE);
	Paint_SelectImage(ImageBW);
	EPD_Init();
	EPD_Display(gImage_2,ImageR);
	EPD_Update();
	EPD_DeepSleep();
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	Paint_Clear(WHITE);
 	EPD_Init();
	while(1)
	{
		Paint_SelectImage(ImageR);
		EPD_ShowPicture(24,0,368,200,gImage_3,BLACK);
		EPD_DrawRectangle(20,200,55,235,BLACK,1);
		EPD_DrawCircle(376,220,18,BLACK,0); 
		Paint_SelectImage(ImageBW);
		EPD_DrawRectangle(80,200,115,235,BLACK,0); 
		EPD_DrawCircle(331,220,18,BLACK,1); //Hollow circle.
		EPD_ShowWatch(148,190,num,4,2,48,BLACK);
		num+=0.01;
		EPD_Display(ImageBW,ImageR);
		EPD_Update();
		delay_ms(1000);
		dat++;
		if(dat==5)
		{
			while(1)
			{
			 EPD_Display_Clear();
			 EPD_Update();
	     EPD_DeepSleep();
			}
		}
	}
}
