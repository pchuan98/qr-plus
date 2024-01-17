#include "EPD.h"
#include "delay.h"

/*******************************************************************
		函数说明:判忙函数
		入口参数:无
		说明:忙状态为0	
*******************************************************************/
void EPD_READBUSY(void)
{
  while(EPD_ReadBusy==0);
}

/*******************************************************************
		函数说明:硬件复位函数
		入口参数:无
		说明:在E-Paper进入Deepsleep状态后需要硬件复位	
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
		函数说明:更新函数
		入口参数:无	
		说明:更新显示内容到E-Paper		
*******************************************************************/
void EPD_Update(void)
{
  EPD_WR_REG(0x04);  //Power ON
	EPD_READBUSY();
	EPD_WR_REG(0x12);
	EPD_READBUSY();
}

/*******************************************************************
		函数说明:休眠函数
		入口参数:无
		说明:屏幕进入低功耗模式		
*******************************************************************/
void EPD_DeepSleep(void)
{
  EPD_WR_REG(0x02); //Power OFF
	EPD_READBUSY();
	EPD_WR_REG(0x07);
	EPD_WR_DATA8(0xA5);
}

/*******************************************************************
		函数说明:初始化函数
		入口参数:无
		说明:调整E-Paper默认显示方向
*******************************************************************/
void EPD_Init(void)
{
	EPD_HW_RESET();
	EPD_READBUSY();
	EPD_WR_REG(0x00);
	EPD_WR_DATA8(0x0B);
}

/*******************************************************************
		函数说明:清屏函数
		入口参数:无
		说明:E-Paper刷白屏
*******************************************************************/
void EPD_Display_Clear(void)
{
	u16 i,j,Width,Height;
	Width=(EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
	Height=EPD_H;	
	EPD_WR_REG(0x10);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(0xFF);
		}
	}
	EPD_WR_REG(0x13);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(0x00);
		}
	}
}


/*******************************************************************
		函数说明:数组数据更新到E-Paper
		入口参数:无
		说明:
*******************************************************************/
void EPD_Display(const u8 *imageBW,const u8 *imageR)
{
	u16 i,j,Width,Height;
	Width=(EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
	Height=EPD_H;
	EPD_WR_REG(0x10);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(imageBW[i+j*Width]);
		}
	}
	EPD_WR_REG(0x13);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(~imageR[i+j*Width]);
		
		}
	}

}

void Epaper_Load_Image(u8 *imageB,u8 *imageR)
{
	u32 i; 	
	u8 tempOriginal;      
  u32 tempcol=0;
  u32 templine=0;	
	
    EPD_WR_REG(0x10);   //write RAM for black(0)/white (1)

		for(i=0;i<ALLSCREEN_BYTES;i++)
		 {          
			 tempOriginal=*(imageB+templine*Gate_BITS+tempcol);
			 templine++;
			 if(templine>=Source_BYTES)
			 {
				 tempcol++;
				 templine=0;
			 }     
			 EPD_WR_DATA8(~tempOriginal);
		 }

		tempcol=0;
		templine=0;	
    EPD_WR_REG(0x13);   //write RAM for black(0)/white (1)
		for(i=0;i<ALLSCREEN_BYTES;i++)
		 {          
			 tempOriginal=*(imageR+templine*Gate_BITS+tempcol);
			 templine++;
			 if(templine>=Source_BYTES)
			 {
				 tempcol++;
				 templine=0;
			 }     
			 EPD_WR_DATA8(tempOriginal);
		 } 		 
}

