#include "allinit.h"
#include "common.h"
#include "include.h"

void all_init(void)
{
  interrupt_priority_set();//中断优先级配置
  LCD_Init();//oled初始化
  KeyboardReadInit();//矩阵键盘初始化
  //UART_Init(UART4,9600);//串口初始化
  ad_init();//AD初始化
  servo_init();//舵机初始化
  motor_init();//电机初始化
  FTM_AB_Init(FTM1);//正交解码初始化

}

void interrupt_priority_set(void)//中断优先级配置
{
  set_irq_priority(68,0);
  set_irq_priority(71,2);
  set_irq_priority(70,1);

}