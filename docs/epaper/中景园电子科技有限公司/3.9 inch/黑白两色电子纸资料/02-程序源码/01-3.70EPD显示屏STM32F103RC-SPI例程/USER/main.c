//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
// �о�԰����
// ���̵�ַ��http://shop73023976.taobao.com
//
//   �� �� ��   : main.c
//   �� �� ��   : v2.0
//   ��    ��   : ZhaoJian
//   ��������   : 2023-12-1
//   ����޸�   :
//   ��������   :��ʾ����(STM32F103ϵ��)
//               ˵��:
//               ----------------------------------------------------------------
//               GND   ��Դ��
//               VCC   3.3v��Դ
//               SCL   PA5��SCLK��
//               SDA   PA7��MOSI��
//               RES   PD2
//               DC    PB5
//               CS    PA4
//               BLK   PB6
//               ----------------------------------------------------------------
//  �޸���ʷ   :
//  ��    ��   :
//  ��    ��   : ZhaoJian
//  �޸�����   : �����ļ�
// ��Ȩ���У�����ؾ���
// Copyright(C) �о�԰����2023-12-1
// All rights reserved
//******************************************************************************/

#include "delay.h"
#include "usart.h"
#include "EPD_GUI.h"
#include "Pic.h"

u8 ImageBW[12480];

int main()
{
	float num = 12.05;
	u8 dat = 0;
	delay_init();
	uart_init(115200);
	EPD_GPIOInit();
	Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE); // ��������
	Paint_Clear(WHITE);
	/************************ȫˢ************************/
	EPD_Init();
	EPD_Display(gImage_1);
	EPD_Update();
	EPD_DeepSleep();
	delay_ms(1000);
	/************************��ˢ************************/
	EPD_FastInit();
	EPD_Display(gImage_2);
	EPD_Update();
	EPD_DeepSleep();
	delay_ms(1000);
	/************************��ˢ************************/
	EPD_FastInit();
	EPD_Display_Clear();
	EPD_Update(); // ��ˢ֮ǰ�ȶ�E-Paper������������
	while (1)
	{
		EPD_PartInit();
		EPD_ShowPicture(24, 0, 368, 200, gImage_3, BLACK);
		EPD_DrawRectangle(20, 200, 55, 235, BLACK, 1);
		EPD_DrawRectangle(80, 200, 115, 235, BLACK, 0);
		EPD_DrawCircle(331, 220, 18, BLACK, 1); // Hollow circle.
		EPD_DrawCircle(376, 220, 18, BLACK, 0);
		EPD_ShowWatch(148, 190, num, 4, 2, 48, BLACK);
		num += 0.01;
		EPD_Display(ImageBW);
		EPD_Update();
		delay_ms(1000);
		dat++;
		if (dat == 5)
		{
			EPD_FastInit();
			while (1)
			{
				EPD_Display_Clear();
				EPD_Update();
				EPD_DeepSleep();
			}
		}
	}
}
