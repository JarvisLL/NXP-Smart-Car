/****************************************************************************************************
��ƽ    ̨������K60VG���İ�
����    д���ֽ���
��ʱ    �䡿17/5/13

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

//�����߼���־
uint16 stop_result[3] = {0,0,0};
uint16 stop_car_line_flag = 0;



//������
 
void main(void)
{
   //u16 Key_board;
   DisableInterrupts;        //�ر����ж�
   PLL_Init(PLL180);         //��ʼ��PLLΪ100M������Ϊ50MHZ
   all_init();               //��ʼ��
   time_delay_ms(1000);
   LCD_CLS();
   EnableInterrupts;
 
   PIT_Init(PIT0,1);//�źŲɼ��ж�
   PIT_Init(PIT2,10);//Һ�����ж�
   PIT_Init(PIT3,5);//�ٶȲɼ��ж� 

}