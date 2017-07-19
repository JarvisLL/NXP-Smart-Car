/****************************************************************************************************
【平    台】龙邱K60VG核心板
【编    写】林锦河
【时    间】17/5/13

=============================================================
******************************************************************************************************/
#include "include.h"
#include "allinit.h"



extern  unsigned short int speed[1];
  u16 ADC_Result[6];
  u8 KeyValue,ModeValue;
void time_delay_ms(u32 ms)
{
  LPTMR_delay_ms(ms);
}

//起跑线检测标志
uint16 stop_result[3] = {0,0,0};
uint16 stop_car_line_flag = 0;



//主函数
 
void main(void)
{
   //u16 Key_board;
   DisableInterrupts;        //关闭总中断
   PLL_Init(PLL180);         //初始化PLL为100M，总线为50MHZ
   all_init();               //初始化
   time_delay_ms(1000);
   LCD_CLS();
   EnableInterrupts;
 
   PIT_Init(PIT0,1);//信号采集中断
   PIT_Init(PIT2,10);//液晶屏中断
   PIT_Init(PIT3,5);//速度采集中断 

}