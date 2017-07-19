#include "motor.h"

/***************  蓝旗K60  ********************************
 *  * 文件说明：电机初始化及PID计算
 *  * 作    者：jarvis_lin
 *  * 日    期：2017/6/27
 *  * 版    本：V1.0
 *  * 修改者  ：
 *  * 修改日期：
 ***********************************************************/

Motor_pid_info Motor;
//定义电机结构体名称 Motor
/*
   
typedef struct 
{ 
  uint8 INH;                    //软件使能
  int16 set_value_temp;         //遥控设定速度临时变量
  int16 output;
  int16 speed_racc;             //电机加速度
  float  last_uk;               //上一次的控制量输出绝对值，即电机占空比/10
  float  kp;
  float  ki;
  float  kd; 
  float  kvff;                   //速度前馈系数
  float  kaff;                   //加速度系数
 
  uint16 kvff_param;             //前馈系数
  int16 present_value[10];       //编码器实际测得值
  int16 error[10];               //误差队列
  int16 set_value[10];           //速度设定队列   
}Motor_pid_info;                 //电机PID所需的信息类型
*/
   
//B车后轮直径56mm，大齿轮106齿,512线编码器齿轮44
//2ms周期,设测得脉冲数为N ,
//转速V  
// 
// 3.6cm/r
//轮子周长17.584cm
//编码器转1圈步进7.3cm
//v= 0.0713*N m/s = 7.13*N cm/s
//2ms,步进 0.01426cm, 1cm 70个脉冲
/**************** 蓝旗K60  ****************************
 *  * 函数名称 ：motor_init
 *  * 函数参数 : 无
 *  * 返回值   : 无
 *  * 函数功能 ：电机初始化
 *  * 作    者 ：jarvis_lin
 *  * 日    期 : 2017/6/27
********************************************************/
extern signed short int num;
uint16 plusecounter;
extern  u16 stop_car_flag;
extern u8 part_lose_line;
int16 timer = 0;//差速倍数

void motor_init(void)
{
  uint8 i = 0;
  GPIO_Init (PORTA, 16, GPO,1);
  FTM_PWM_Init(FTM0,FTM_CH1,562,0); //10kHz,duty = 0~625*20%
  FTM_PWM_Init(FTM0,FTM_CH2,562,0); //
  
  for(i = 0; i < 10; i++)
  {
    Motor.error[i] = 0;
  }
  Motor.motorduty = 100;
  Motor.ki = 200;
  Motor.kp = 12000;
  Motor.kd = 0 ;
  timer = 3;
}

//脉冲累加计数初始化
/*void pulse_acc_init(void)
{

    //PTC5脉冲累加
   lptmr_pulse_init(LPT0_ALT2,0xFFFF,LPT_Rising);
  
    //Dir -- PTC6,上拉输入
    gpio_init(PTC6,GPI,0);
    port_init(PTC6,ALT1|PULLUP);
}*/

/**************** 蓝旗K60  ****************************
 *  * 函数名称 ：motor_set
 *  * 函数参数 : int16 duty
 *  * 返回值   : 无
 *  * 函数功能 ：电机调速
 *  * 作    者 ：jarvis_lin
 *  * 日    期 : 2017/06/27
********************************************************/

void motor_set(int16 duty)
{
  if(duty > 150)
   duty = 150;
  if(duty < -150)
   duty = -150;
  if(duty > 0)
  {
    FTM_PWM_Duty(FTM0,FTM_CH2,0);
    FTM_PWM_Duty(FTM0,FTM_CH1,duty);

    
  }
  
  else if(duty == 0)
  {
    FTM_PWM_Duty(FTM0,FTM_CH2,0);
    FTM_PWM_Duty(FTM0,FTM_CH1,0);
  }
  
  else
  {

    FTM_PWM_Duty(FTM0,FTM_CH0,(0-duty));
    FTM_PWM_Duty(FTM0,FTM_CH1,0);

  }
}


/**************** 蓝旗K60  ****************************
 *  * 函数名称 ：motor_pid_caculate
 *  * 函数参数 : Motor_pid_info *motor_info
 *  * 返回值   : 无
 *  * 函数功能 ：电机PID计算
 *  * 作    者 ：jarvis_lin
 *  * 日    期 : 2017/6/27
********************************************************/
void motor_pid_caculate(Motor_pid_info *motor_info)
{


  uint8 i = 0;
  for(i=3;i>0;i--)     //更新偏差队列
  {
    motor_info->error[i] = motor_info->error[i-1];
  }
  
  if(num>0){
   plusecounter = num;
  }
  else{
    plusecounter = num;
  }
   motor_info->motorspeed = plusecounter;
   motor_info->error[0] = motor_info->motorduty - motor_info->motorspeed;
   /******************************************************
               完全丢线判断
   ********************************************************/
    if(stop_car_flag == 1)
    {
      motor_set(0);
    
    }
    
    /*********************************************************
                  部分丢线判断   速度减半
    *********************************************************/
    
    else if(part_lose_line ==1)
    {
      motor_info->output += 
     ( motor_info->kp*(motor_info->error[0]-motor_info->error[1]) + 
      motor_info->ki*motor_info->error[0] + 
        motor_info->kd*((motor_info->error[0]-motor_info->error[1])-(motor_info->error[1]-motor_info->error[2])))/10000;
   
       motor_set(motor_info->output/timer);
    }
  
  
    else{
   motor_info->output += 
     ( motor_info->kp*(motor_info->error[0]-motor_info->error[1]) + 
      motor_info->ki*motor_info->error[0] + 
        motor_info->kd*((motor_info->error[0]-motor_info->error[1])-(motor_info->error[1]-motor_info->error[2])))/10000;
   
         motor_set(motor_info->output);
  }
  
  

  

}  






