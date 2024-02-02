//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 中景园电子
// 店铺地址：http://shop73023976.taobao.com
//
//   文 件 名   : main.c
//   版 本 号   : v1.0
//   作    者   : ZhaoJian
//   生成日期   : 2024-01-16
//   最近修改   :
//   功能描述   :演示例程(ESP32 S3系列)
//               说明:
//               ----------------------------------------------------------------
//               GND   电源地
//               VCC   3.3v电源
//               SCL   14
//               SDA   15
//               RES   16
//               DC    17
//               CS    18
//               BUSY  13
//               ----------------------------------------------------------------
//  修改历史   :
//  日    期   :
//  作    者   : ZhaoJian
//  修改内容   : 创建文件
// 版权所有，盗版必究。
// Copyright(C) 中景园电子2024-01-16
// All rights reserved
//******************************************************************************/

#include "EPD_GUI.h"
#include "Pic.h"

u8 ImageBW[12480];

void setup()
{
	float num = 12.05;
	u8 dat = 0;
	EPD_GPIOInit();
	Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE); // 创建画布
	Paint_Clear(WHITE);
	/************************全刷************************/
	EPD_Init();
	EPD_Display(gImage_1);
	EPD_Update();
	EPD_DeepSleep();
	delay(1000);
	/************************快刷************************/
	EPD_FastInit();
	EPD_Display(gImage_2);
	EPD_Update();
	EPD_DeepSleep();
	delay(1000);
	/************************局刷************************/
	EPD_FastInit();
	EPD_Display_Clear();
	EPD_Update(); // 局刷之前先对E-Paper进行清屏操作
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
		delay(1000);
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
void loop()
{
}
