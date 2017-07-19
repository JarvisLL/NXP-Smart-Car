#ifndef __STRUCT_H
#define __STRUCT_H

#include "common.h"


//ADC
typedef struct
{

 uint16 ad_mid_val[10]; //AD������ֵ 
 uint32 ad_add_val[10]; //AD������ֵ��
 float ad_avr_val[10]; //AD����ƽ��ֵ
 uint16 ad_max_val[10]; //AD���ֵ
 uint16 ad_max_temp[10];
 uint16 ad_int_val[10][3];
 uint16 ad_avr_temp[5][10];
}ADC_info;


//������
typedef struct 
{

  float once_uni_ad[9];  //һ�ι�һ������
  float twice_uni_ad[9]; //���ι�һ������

}Sensor_info;

//Բ��
/*typedef struct
{
  

}Round_info;
*/
//����
typedef struct
{
  uint16 lose_line_flag;        //���߱�־λ
  uint16 lose_line_val;         //������ֵ
  uint16 lose_line_counter;     //���ߴ���
  uint16 turn_left_flag;        //��ת��־λ
  uint16 turn_right_flag;       //��ת��־λ
}LoseLine_info;


//ʮ��
typedef struct
{
  uint16 cross_flag;           //ʮ�ֵ���־λ
  uint16 cross_keep_dis;       //ʮ�ֵ����־���
}Cross_info;



//�µ�
/*typedef struct
{
  
}RampRoad_info;*/



//��������
/*typedef struct
{
  uint16 cross_road_remember;   //ʮ�ִ���  
  uint16 zhijiao_road_remember; //ֱ�Ǵ���
  uint16 lose_line_remember;    //���ߴ���
  uint16 ramp_road_remember;    //�µ�����
  uint16 special_cross_remember;
}RoadRemember_info;*/


  
  
  
//���������
typedef  struct 
{
  float kp; 
  float kd;
  float error[20];
  int16  output;
  u16 pulse_width;   //�����ֵ                  // ���ƫ��仯�� 
  
  uint16 mode_select;
}Servo_pid_info;


//������ٶ�
typedef struct 
{ 

  int16 output;
  float  kp;
  float  ki;
  float  kd; 
  float error[4];          //������
  float motorduty;
  float motorspeed;
 
}Motor_pid_info;             //���PID�������Ϣ����


typedef struct
{
  uint16 zhidao_speed_val; //ֱ���ٶ�
  uint16 cross_speed_val;  //СS�ٶ�
  uint16 shizi_speed_val;  //ʮ���ٶ�
  uint16 ramp1_speed_val; //�µ��ٶ�
  uint16 ramp2_speed_val;
  uint16 speed_high_mode; //����ģʽʹ��
  uint16 stop_car_enable; //ͣ��
  uint16 test_time;       //����ʱ��
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

