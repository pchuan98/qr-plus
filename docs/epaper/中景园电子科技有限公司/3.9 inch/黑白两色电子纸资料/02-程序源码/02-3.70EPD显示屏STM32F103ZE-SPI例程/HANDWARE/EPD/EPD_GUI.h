#ifndef _EPD_GUI_H_
#define _EPD_GUI_H_

#include "EPD.h"

typedef struct {
	u8 *Image;
	u16 width;
	u16 height;
	u16 widthMemory;
	u16 heightMemory;
	u16 color;
	u16 rotate;
	u16 widthByte;
	u16 heightByte;
	
}PAINT;
extern PAINT Paint;

//����E-Paper��ʾ���� 
/*******************
Rotaion:0-0�ȷ���
Rotaion:90-90�ȷ���
Rotaion:180-180�ȷ���
Rotaion:270-270�ȷ���
*******************/
#define Rotation 0  


void Paint_NewImage(u8 *image,u16 Width,u16 Height,u16 Rotate,u16 Color); 					 //��������������ʾ����
void Paint_SetPixel(u16 Xpoint,u16 Ypoint,u16 Color);
void Paint_Clear(u8 Color);
void EPD_DrawLine(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color);
void EPD_DrawRectangle(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color,u8 mode);  //������
void EPD_DrawCircle(u16 X_Center,u16 Y_Center,u16 Radius,u16 Color,u8 mode);        //��Բ
void EPD_ShowChar(u16 x,u16 y,u16 chr,u16 size1,u16 color);                         //��ʾ�ַ�
void EPD_ShowString(u16 x,u16 y,u8 *chr,u16 size1,u16 color);                       //��ʾ�ַ���
void EPD_ShowNum(u16 x,u16 y,u32 num,u16 len,u16 size1,u16 color);                  //��ʾ����
void EPD_ShowPicture(u16 x,u16 y,u16 sizex,u16 sizey,const u8 BMP[],u16 Color);			//��ʾͼƬ      
void EPD_ClearWindows(u16 xs,u16 ys,u16 xe,u16 ye,u16 color);
void EPD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u8 pre,u8 sizey,u8 color);
void EPD_ShowWatch(u16 x,u16 y,float num,u8 len,u8 pre,u8 sizey,u8 color);

void EPD_ShowChinese(u16 x,u16 y,u8 *s,u8 sizey,u16 color);//��ʾ���ִ�
void EPD_ShowChinese12x12(u16 x,u16 y,u8 *s,u8 sizey,u16 color);//��ʾ����12x12����
void EPD_ShowChinese16x16(u16 x,u16 y,u8 *s,u8 sizey,u16 color);//��ʾ����16x16����
void EPD_ShowChinese24x24(u16 x,u16 y,u8 *s,u8 sizey,u16 color);//��ʾ����24x24����
void EPD_ShowChinese32x32(u16 x,u16 y,u8 *s,u8 sizey,u16 color);//��ʾ����32x32����


#endif



