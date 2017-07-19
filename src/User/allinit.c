#include "allinit.h"
#include "common.h"
#include "include.h"

void all_init(void)
{
  interrupt_priority_set();//�ж����ȼ�����
  LCD_Init();//oled��ʼ��
  KeyboardReadInit();//������̳�ʼ��
  //UART_Init(UART4,9600);//���ڳ�ʼ��
  ad_init();//AD��ʼ��
  servo_init();//�����ʼ��
  motor_init();//�����ʼ��
  FTM_AB_Init(FTM1);//���������ʼ��

}

void interrupt_priority_set(void)//�ж����ȼ�����
{
  set_irq_priority(68,0);
  set_irq_priority(71,2);
  set_irq_priority(70,1);

}