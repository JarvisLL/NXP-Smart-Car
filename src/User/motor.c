#include "motor.h"

/***************  ����K60  ********************************
 *  * �ļ�˵���������ʼ����PID����
 *  * ��    �ߣ�jarvis_lin
 *  * ��    �ڣ�2017/6/27
 *  * ��    ����V1.0
 *  * �޸���  ��
 *  * �޸����ڣ�
 ***********************************************************/

Motor_pid_info Motor;
//�������ṹ������ Motor
/*
   
typedef struct 
{ 
  uint8 INH;                    //���ʹ��
  int16 set_value_temp;         //ң���趨�ٶ���ʱ����
  int16 output;
  int16 speed_racc;             //������ٶ�
  float  last_uk;               //��һ�εĿ������������ֵ�������ռ�ձ�/10
  float  kp;
  float  ki;
  float  kd; 
  float  kvff;                   //�ٶ�ǰ��ϵ��
  float  kaff;                   //���ٶ�ϵ��
 
  uint16 kvff_param;             //ǰ��ϵ��
  int16 present_value[10];       //������ʵ�ʲ��ֵ
  int16 error[10];               //������
  int16 set_value[10];           //�ٶ��趨����   
}Motor_pid_info;                 //���PID�������Ϣ����
*/
   
//B������ֱ��56mm�������106��,512�߱���������44
//2ms����,����������ΪN ,
//ת��V  
// 
// 3.6cm/r
//�����ܳ�17.584cm
//������ת1Ȧ����7.3cm
//v= 0.0713*N m/s = 7.13*N cm/s
//2ms,���� 0.01426cm, 1cm 70������
/**************** ����K60  ****************************
 *  * �������� ��motor_init
 *  * �������� : ��
 *  * ����ֵ   : ��
 *  * �������� �������ʼ��
 *  * ��    �� ��jarvis_lin
 *  * ��    �� : 2017/6/27
********************************************************/
extern signed short int num;
uint16 plusecounter;
extern  u16 stop_car_flag;
extern u8 part_lose_line;
int16 timer = 0;//���ٱ���

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

//�����ۼӼ�����ʼ��
/*void pulse_acc_init(void)
{

    //PTC5�����ۼ�
   lptmr_pulse_init(LPT0_ALT2,0xFFFF,LPT_Rising);
  
    //Dir -- PTC6,��������
    gpio_init(PTC6,GPI,0);
    port_init(PTC6,ALT1|PULLUP);
}*/

/**************** ����K60  ****************************
 *  * �������� ��motor_set
 *  * �������� : int16 duty
 *  * ����ֵ   : ��
 *  * �������� ���������
 *  * ��    �� ��jarvis_lin
 *  * ��    �� : 2017/06/27
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


/**************** ����K60  ****************************
 *  * �������� ��motor_pid_caculate
 *  * �������� : Motor_pid_info *motor_info
 *  * ����ֵ   : ��
 *  * �������� �����PID����
 *  * ��    �� ��jarvis_lin
 *  * ��    �� : 2017/6/27
********************************************************/
void motor_pid_caculate(Motor_pid_info *motor_info)
{


  uint8 i = 0;
  for(i=3;i>0;i--)     //����ƫ�����
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
               ��ȫ�����ж�
   ********************************************************/
    if(stop_car_flag == 1)
    {
      motor_set(0);
    
    }
    
    /*********************************************************
                  ���ֶ����ж�   �ٶȼ���
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






