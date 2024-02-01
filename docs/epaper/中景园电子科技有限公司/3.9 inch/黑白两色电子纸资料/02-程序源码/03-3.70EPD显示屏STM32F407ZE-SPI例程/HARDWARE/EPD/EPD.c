#include "EPD.h"
#include "delay.h"

u8 oldImage[12480];

/*******************************************************************
		����˵��:��æ����
		��ڲ���:��
		˵��:æ״̬Ϊ0
*******************************************************************/
void EPD_READBUSY(void)
{
	while (EPD_ReadBusy == 0)
		;
}

/*******************************************************************
		����˵��:Ӳ����λ����
		��ڲ���:��
		˵��:��E-Paper����Deepsleep״̬����ҪӲ����λ
*******************************************************************/
void EPD_HW_RESET(void)
{
	delay_ms(100);
	EPD_RES_Clr();
	delay_ms(20);
	EPD_RES_Set();
	delay_ms(20);
	EPD_READBUSY();
}

/*******************************************************************
		����˵��:���º���
		��ڲ���:��
		˵��:������ʾ���ݵ�E-Paper
*******************************************************************/
void EPD_Update(void)
{
	EPD_WR_REG(0x04); // Power ON
	EPD_READBUSY();
	EPD_WR_REG(0x12);
	EPD_READBUSY();
}
/*******************************************************************
		����˵��:��ˢ��ʼ������
		��ڲ���:��
		˵��:E-Paper�����ھ�ˢģʽ
*******************************************************************/
void EPD_PartInit(void)
{
	EPD_HW_RESET();
	EPD_READBUSY();
	EPD_WR_REG(0x00);
	EPD_WR_DATA8(0x1B);
	EPD_WR_REG(0xE0);
	EPD_WR_DATA8(0x02);
	EPD_WR_REG(0xE5);
	EPD_WR_DATA8(0x6E);
}

/*******************************************************************
		����˵��:��ˢ��ʼ������
		��ڲ���:��
		˵��:E-Paper�����ڿ�ˢģʽ
*******************************************************************/
void EPD_FastInit(void)
{
	EPD_HW_RESET();
	EPD_READBUSY();
	EPD_WR_REG(0x00);
	EPD_WR_DATA8(0x1B);
	EPD_WR_REG(0xE0);
	EPD_WR_DATA8(0x02);
	EPD_WR_REG(0xE5);
	EPD_WR_DATA8(0x5F);
}

/*******************************************************************
		����˵��:���ߺ���
		��ڲ���:��
		˵��:��Ļ����͹���ģʽ
*******************************************************************/
void EPD_DeepSleep(void)
{
	EPD_WR_REG(0x02); // Power OFF
	EPD_READBUSY();
	EPD_WR_REG(0x07);
	EPD_WR_DATA8(0xA5);
}

/*******************************************************************
		����˵��:��ʼ������
		��ڲ���:��
		˵��:����E-PaperĬ����ʾ����
*******************************************************************/
void EPD_Init(void)
{
	EPD_HW_RESET();
	EPD_READBUSY();
	EPD_WR_REG(0x00);
	EPD_WR_DATA8(0x1B);
}

/*******************************************************************
		����˵��:��������
		��ڲ���:��
		˵��:E-Paperˢ����
*******************************************************************/
void EPD_Display_Clear(void)
{
	u16 i, j, Width, Height;
	Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
	Height = EPD_H;
	EPD_WR_REG(0x10);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_WR_DATA8(oldImage[i + j * Width]);
		}
	}
	EPD_WR_REG(0x13);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_WR_DATA8(0xFF);
			oldImage[i + j * Width] = 0xFF;
		}
	}
}

/*******************************************************************
		����˵��:�������ݸ��µ�E-Paper
		��ڲ���:��
		˵��:
*******************************************************************/
void EPD_Display(const u8 *image)
{
	u16 i, j, Width, Height;
	Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
	Height = EPD_H;
	EPD_WR_REG(0x10);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_WR_DATA8(oldImage[i + j * Width]);
		}
	}
	EPD_WR_REG(0x13);
	for (j = 0; j < Height; j++)
	{
		for (i = 0; i < Width; i++)
		{
			EPD_WR_DATA8(image[i + j * Width]);
			oldImage[i + j * Width] = image[i + j * Width];
		}
	}
}
