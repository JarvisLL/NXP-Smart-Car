#include "include.h"
#include "sensor.h"
#include "struct.h"
#include "servo.h"
#include "math.h"
#include "LQ12864.h"
/*******************************************************
                    赛道检测算法
*******************************************************/
//拟合系数
//丢线处理
//冲出跑道判定
//十字道判定
//直角判定
//直道判定



Sensor_info Sensor={0}; 

ADC_info  Adc = {0};

float sum_34_56 = 0;

 u16 stop_car_cnt = 0;
 u16 stop_car_flag = 0;
 
 
 //圆环标志
 u16 round_enter_flag = 0; //进圆环
 u16 round_exit_flag = 0;  //出圆环
 u16 round_driving_flag = 0;//在圆环内行驶
 
 //普通十字
 u16 normal_cross_flag = 0;
 
 //
 u16 run_off_enable = 0;
  
 //转弯标志
 u8 turn_left_flag = 0;
 u8 turn_right_flag = 0;
 
 //丢线标志 

 u8 part_lose_line = 0;
 
 u16 sensor_fazhi = 8000;

/**************** 蓝旗K60  ****************************
 *  * 函数名称 ：ad_init
 *  * 函数参数 : 无
 *  * 返回值   : 无
 *  * 函数功能 ：ADC初始化
 *  * 作    者 ：jarvis
 *  * 日    期 : 2017/6/27
********************************************************/
void ad_init(void)
{  
  ADC_Init(ADC1);//ADC1模块初始化
  ADC_Init(ADC0);
}
/**************** 蓝旗K60  ****************************
 *  * 函数名称 ：get_adc_int_val
 *  * 函数参数 : 无
 *  * 返回值   : 无
 *  * 函数功能 ：get_adc_int_val
 *  * 作    者 ：jarvis_lin
 *  * 日    期 : 2017/6/27
********************************************************/
void get_adc_int_val(void)    //中值滤波  均值滤波   求取平均值
{
  Adc.ad_avr_val[1] = ADC_Ave(ADC1,ADC1_SE10,ADC_16bit,3);
  Adc.ad_avr_val[2] = ADC_Ave(ADC1,ADC1_SE11,ADC_16bit,3);
  Adc.ad_avr_val[3] = ADC_Ave(ADC1,ADC1_SE12,ADC_16bit,3);
  Adc.ad_avr_val[4] = ADC_Ave(ADC1,ADC1_SE13,ADC_16bit,3);
  Adc.ad_avr_val[5] = ADC_Ave(ADC1,ADC1_SE14,ADC_16bit,3);
  Adc.ad_avr_val[6] = ADC_Ave(ADC1,ADC1_SE15,ADC_16bit,3);  
  
  
  
  
}






/*************************************************
 * 蓝旗K60电感分布 
          
              5    3   4   6 
                1        2 

接口：         5 3 1 2 4 6
**************************************************/ 
/*************************************************
 * 成电疾影电感分布 
    2      5
 1    3  4   6 
  7         8 
 
 * 成电幻影电感分布
    4      6   
 5    1  2    3
*******************************************************/ 

 /*************** 蓝旗K60**************************
*  * 函数名称 ：deal_sensor
 *  * 函数参数 : Sensor_info *sensor
 *  * 返回值   : 无
 *  * 函数功能 ：电感偏差处理
 *  * 作    者 ：jarvis_lin
 *  * 日    期 : 2016/7/1
********************************************************/
void deal_sensor(Sensor_info *sensor)
{
  u8 i;
  get_adc_int_val(); //滤波后AD值
  
  
  /***********************************************
    -------------  半圆弯道判断  左转弯--------------
   近半圆弯道判断。3456号电感丢线，12哪边大往哪边转
     1 >> 2  左转  同时减速
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
  ---------------  半圆弯道判断 左转弯 减速 ----------------
  
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
  
  /*******************正常巡线***************************/
     
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

  

