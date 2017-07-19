#ifndef __STRUCT_H
#define __STRUCT_H

#include "common.h"


//ADC
typedef struct
{

 uint16 ad_mid_val[10]; //AD采样中值 
 uint32 ad_add_val[10]; //AD采样中值和
 float ad_avr_val[10]; //AD采样平均值
 uint16 ad_max_val[10]; //AD最大值
 uint16 ad_max_temp[10];
 uint16 ad_int_val[10][3];
 uint16 ad_avr_temp[5][10];
}ADC_info;


//传感器
typedef struct 
{

  float once_uni_ad[9];  //一次归一化处理
  float twice_uni_ad[9]; //二次归一化处理

}Sensor_info;

//圆环
/*typedef struct
{
  

}Round_info;
*/
//丢线
typedef struct
{
  uint16 lose_line_flag;        //丢线标志位
  uint16 lose_line_val;         //丢线阈值
  uint16 lose_line_counter;     //丢线次数
  uint16 turn_left_flag;        //左转标志位
  uint16 turn_right_flag;       //右转标志位
}LoseLine_info;


//十字
typedef struct
{
  uint16 cross_flag;           //十字道标志位
  uint16 cross_keep_dis;       //十字道保持距离
}Cross_info;



//坡道
/*typedef struct
{
  
}RampRoad_info;*/



//赛道记忆
/*typedef struct
{
  uint16 cross_road_remember;   //十字次数  
  uint16 zhijiao_road_remember; //直角次数
  uint16 lose_line_remember;    //丢线次数
  uint16 ramp_road_remember;    //坡道次数
  uint16 special_cross_remember;
}RoadRemember_info;*/


  
  
  
//舵机，方向
typedef  struct 
{
  float kp; 
  float kd;
  float error[20];
  int16  output;
  u16 pulse_width;   //舵机中值                  // 最大偏差变化率 
  
  uint16 mode_select;
}Servo_pid_info;


//电机，速度
typedef struct 
{ 

  int16 output;
  float  kp;
  float  ki;
  float  kd; 
  float error[4];          //误差队列
  float motorduty;
  float motorspeed;
 
}Motor_pid_info;             //电机PID所需的信息类型


typedef struct
{
  uint16 zhidao_speed_val; //直道速度
  uint16 cross_speed_val;  //小S速度
  uint16 shizi_speed_val;  //十字速度
  uint16 ramp1_speed_val; //坡道速度
  uint16 ramp2_speed_val;
  uint16 speed_high_mode; //高速模式使能
  uint16 stop_car_enable; //停车
  uint16 test_time;       //测试时间
}Speed_info;

extern ADC_info         Adc;
extern Sensor_info      Sensor;
extern LoseLine_info    LoseLine;
extern Cross_info       CrossRoad;
//extern RampRoad_info    RampRoad;
//extern Round_info       Round;
//extern RoadRemember_info RoadRemember;
extern Servo_pid_info   Servo;
extern Motor_pid_info   Motor;
extern Speed_info       Speed;






#endif

