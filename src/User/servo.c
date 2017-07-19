#include "include.h"
#include "servo.h"
#include "math.h"
#include "LQ12864.h"


/*************  ����K60  **********************
************** ������� ***********************
**************��ؽṹ�����*******************
//���������
typedef  struct 
{
  float kp; 
  float kd;
  float kp_2;
  float kd_2;
  float error[20];
  int16  output;
  uint16 pulse_width;   //�����ֵ
  float  dis1cm_err_store[25];           //1cm��·ƫ��
  float  distance_err_max_val;           //���λƫ�� ,ң�ؿ��޸�
  float  distance_err_d_max_val;         //���ƫ����(ƫ��΢��),���޸�
  float  max_dis_err;                    // ���ƫ��仯
  float  max_dis_err_d;                  // ���ƫ��仯�� 
  uint16 mode_select;
}Servo_pid_info;  //���������Ʋ���

**********************************************/
 Servo_pid_info Servo;
 uint16 zhijiao_cnt = 0; //ֱ�ǿ���
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
/***************  ����K60  ********************************
 *  * �ļ�˵���������ʼ��
 *  * ��    �ߣ�jarvis_lin
 *  * ��    �ڣ�2017/6/27
 *  * ��    ����V1.0
 *  * �޸���  ��
 *  * �޸����ڣ�
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
  FTM_PWM_Init(FTM2,FTM_CH0,25000,0);//���pwm��ʼ��,250Hz

}

//�������
void servo_pid_caculate(void)
{
  
  /***************************************
    ��ת��־
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
  /********* ����޷� **************/
  if(Servo.output < SERVO_RIGHT_VAL)
  {
    Servo.output = SERVO_RIGHT_VAL;
  }
  if(Servo.output > SERVO_LEFT_VAL)
  {
    Servo.output = SERVO_LEFT_VAL; 
  }
  
  FTM_PWM_Duty(FTM2,FTM_CH0,Servo.output); //���PWM�����ڶ��
 
}


