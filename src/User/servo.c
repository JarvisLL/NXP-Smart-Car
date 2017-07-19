#include "include.h"
#include "servo.h"
#include "math.h"
#include "LQ12864.h"


/*************  蓝旗K60  **********************
************** 舵机控制 ***********************
**************相关结构体参数*******************
//舵机，方向
typedef  struct 
{
  float kp; 
  float kd;
  float kp_2;
  float kd_2;
  float error[20];
  int16  output;
  uint16 pulse_width;   //舵机中值
  float  dis1cm_err_store[25];           //1cm道路偏差
  float  distance_err_max_val;           //最大单位偏差 ,遥控可修改
  float  distance_err_d_max_val;         //最大偏差率(偏差微分),可修改
  float  max_dis_err;                    // 最大偏差变化
  float  max_dis_err_d;                  // 最大偏差变化率 
  uint16 mode_select;
}Servo_pid_info;  //舵机方向控制参数

**********************************************/
 Servo_pid_info Servo;
 uint16 zhijiao_cnt = 0; //直角控制
 uint16 special_cnt = 0;


 extern u8 turn_left_flag;
 extern u8  turn_right_flag;
 extern u16 straight_road_flag;
 extern  u16 special_cross_flag;
 extern u16 speed_change_flag;
 extern u16 special_left_flag;
 extern u16 special_right_flag;
 extern float sub_16;
 extern u16  zhidao_sum;
 float Servo_error = 0.68;
/***************  蓝旗K60  ********************************
 *  * 文件说明：舵机初始化
 *  * 作    者：jarvis_lin
 *  * 日    期：2017/6/27
 *  * 版    本：V1.0
 *  * 修改者  ：
 *  * 修改日期：
 ***********************************************************/

void servo_init(void)
{
  u8 i = 0;
  Servo.kp = 43.5;
  Servo.kd = 46.0;
  for(i = 0;i <20;i++)
  Servo.error[i] = 0;
  Servo.output = 12300;
  Servo.pulse_width = SERVO_MID_VAL;
  FTM_PWM_Init(FTM2,FTM_CH0,25000,0);//舵机pwm初始化,250Hz

}

//舵机控制
void servo_pid_caculate(void)
{
  
  /***************************************
    左转标志
  ***************************************/
  if( turn_left_flag == 1)
  {
    Servo.output = SERVO_LEFT_VAL;
  
  } 
  else if( turn_right_flag == 1 )
  {
    Servo.output = SERVO_RIGHT_VAL;
  
  }

  else { 
  if(Servo.error[0]<0)
  {  
  Servo.output = (u16)(Servo.pulse_width + (Servo.kp*Servo_error*Servo.error[0] + Servo.kd*5.0* (Servo.error[0]-Servo.error[9])));//10ms
  }
  else
  {
    Servo.output = (u16)(Servo.pulse_width + (Servo.kp *Servo.error[0] + Servo.kd*5.0* (Servo.error[0]-Servo.error[9])));
  
  }
  }
  /********* 输出限幅 **************/
  if(Servo.output < SERVO_RIGHT_VAL)
  {
    Servo.output = SERVO_RIGHT_VAL;
  }
  if(Servo.output > SERVO_LEFT_VAL)
  {
    Servo.output = SERVO_LEFT_VAL; 
  }
  
  FTM_PWM_Duty(FTM2,FTM_CH0,Servo.output); //输出PWM作用于舵机
 
}


