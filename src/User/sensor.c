#include "include.h"
#include "sensor.h"
#include "struct.h"
#include "servo.h"
#include "math.h"
#include "LQ12864.h"
/*******************************************************
                    ��������㷨
*******************************************************/
//���ϵ��
//���ߴ���
//����ܵ��ж�
//ʮ�ֵ��ж�
//ֱ���ж�
//ֱ���ж�



Sensor_info Sensor={0}; 

ADC_info  Adc = {0};

float sum_34_56 = 0;

 u16 stop_car_cnt = 0;
 u16 stop_car_flag = 0;
 
 
 //Բ����־
 u16 round_enter_flag = 0; //��Բ��
 u16 round_exit_flag = 0;  //��Բ��
 u16 round_driving_flag = 0;//��Բ������ʻ
 
 //��ͨʮ��
 u16 normal_cross_flag = 0;
 
 //
 u16 run_off_enable = 0;
  
 //ת���־
 u8 turn_left_flag = 0;
 u8 turn_right_flag = 0;
 
 //���߱�־ 

 u8 part_lose_line = 0;
 
 u16 sensor_fazhi = 8000;

/**************** ����K60  ****************************
 *  * �������� ��ad_init
 *  * �������� : ��
 *  * ����ֵ   : ��
 *  * �������� ��ADC��ʼ��
 *  * ��    �� ��jarvis
 *  * ��    �� : 2017/6/27
********************************************************/
void ad_init(void)
{  
  ADC_Init(ADC1);//ADC1ģ���ʼ��
  ADC_Init(ADC0);
}
/**************** ����K60  ****************************
 *  * �������� ��get_adc_int_val
 *  * �������� : ��
 *  * ����ֵ   : ��
 *  * �������� ��get_adc_int_val
 *  * ��    �� ��jarvis_lin
 *  * ��    �� : 2017/6/27
********************************************************/
void get_adc_int_val(void)    //��ֵ�˲�  ��ֵ�˲�   ��ȡƽ��ֵ
{
  Adc.ad_avr_val[1] = ADC_Ave(ADC1,ADC1_SE10,ADC_16bit,3);
  Adc.ad_avr_val[2] = ADC_Ave(ADC1,ADC1_SE11,ADC_16bit,3);
  Adc.ad_avr_val[3] = ADC_Ave(ADC1,ADC1_SE12,ADC_16bit,3);
  Adc.ad_avr_val[4] = ADC_Ave(ADC1,ADC1_SE13,ADC_16bit,3);
  Adc.ad_avr_val[5] = ADC_Ave(ADC1,ADC1_SE14,ADC_16bit,3);
  Adc.ad_avr_val[6] = ADC_Ave(ADC1,ADC1_SE15,ADC_16bit,3);  
  
  
  
  
}






/*************************************************
 * ����K60��зֲ� 
          
              5    3   4   6 
                1        2 

�ӿڣ�         5 3 1 2 4 6
**************************************************/ 
/*************************************************
 * �ɵ缲Ӱ��зֲ� 
    2      5
 1    3  4   6 
  7         8 
 
 * �ɵ��Ӱ��зֲ�
    4      6   
 5    1  2    3
*******************************************************/ 

 /*************** ����K60**************************
*  * �������� ��deal_sensor
 *  * �������� : Sensor_info *sensor
 *  * ����ֵ   : ��
 *  * �������� �����ƫ���
 *  * ��    �� ��jarvis_lin
 *  * ��    �� : 2016/7/1
********************************************************/
void deal_sensor(Sensor_info *sensor)
{
  u8 i;
  get_adc_int_val(); //�˲���ADֵ
  
  
  /***********************************************
    -------------  ��Բ����ж�  ��ת��--------------
   ����Բ����жϡ�3456�ŵ�ж��ߣ�12�ıߴ����ı�ת
     1 >> 2  ��ת  ͬʱ����
  ***********************************************/
  if( 
     (Adc.ad_avr_val[3]<sensor_fazhi)&&(Adc.ad_avr_val[4]<sensor_fazhi)&&
     (Adc.ad_avr_val[5]<sensor_fazhi)&&(Adc.ad_avr_val[6]<sensor_fazhi)&&
     (Adc.ad_avr_val[2]>1500||Adc.ad_avr_val[1]>1500)&&
     (Adc.ad_avr_val[2]<Adc.ad_avr_val[1])
     
     )
  {
    part_lose_line = 1;
    
    turn_right_flag = 0;
    turn_left_flag = 1;
    stop_car_flag = 0;
  }
  
 /*****************************************************
  ---------------  ��Բ����ж� ��ת�� ���� ----------------
  
  *****************************************************/
  else if(
            (Adc.ad_avr_val[3]<sensor_fazhi)&&(Adc.ad_avr_val[4]<sensor_fazhi)&&
     (Adc.ad_avr_val[5]<sensor_fazhi)&&(Adc.ad_avr_val[6]<sensor_fazhi)&&
       (Adc.ad_avr_val[2]>1500||Adc.ad_avr_val[1]>1500)&&
       (Adc.ad_avr_val[2]>Adc.ad_avr_val[1])
          )
  {
    part_lose_line = 1;
    
    turn_right_flag = 1;
    turn_left_flag = 0;
    stop_car_flag = 0;
  
  }
 
  else if(
          (Adc.ad_avr_val[3]<1500)&&(Adc.ad_avr_val[4]<1500)&&
     (Adc.ad_avr_val[5]<1500)&&(Adc.ad_avr_val[6]<1500)&&
       (Adc.ad_avr_val[2]<1500||Adc.ad_avr_val[1]<1500)
          
         )
  {
    
    part_lose_line = 0;
   
    turn_right_flag = 0;
    turn_left_flag = 0;
    stop_car_flag = 1;
  
  }
  
  /*******************����Ѳ��***************************/
     
  else {
      part_lose_line = 0;
    
    turn_right_flag = 0;
    turn_left_flag = 0;
    stop_car_flag = 0;
  
     for(i = 19; i > 0; i--)
         Servo.error[i] = Servo.error[i-1];
                 
     Servo.error[0] = ((Adc.ad_avr_val[5]-Adc.ad_avr_val[6])/(Adc.ad_avr_val[6]+Adc.ad_avr_val[5]))*100;

  }

}

  

