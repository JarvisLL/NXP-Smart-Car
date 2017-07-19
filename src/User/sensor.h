#ifndef __SENSOR_H
#define __SENSOR_H


#include "common.h"
#include "include.h"
#include "struct.h"

/***********  电感ADC采集通道 宏定义 *****************/

//
//#define  Induc_8    ADC0_SE1
//#define  Induc_7    ADC0_SE5a
#define  Induc_6    ADC1_SE15
#define  Induc_5    ADC1_SE14
#define  Induc_4    ADC1_SE13
#define  Induc_3    ADC1_SE12
#define  Induc_2    ADC1_SE11
#define  Induc_1    ADC1_SE10


//#define  BAT      ADC0_SE15         //电池电压检测
//#define  BAT_VAL  adc_once(ADC0_SE15,ADC_16bit) 


void ad_init(void); //ad初始化
void get_adc_int_val(void);  //ad采样值

void deal_sensor(Sensor_info *sensor);//电感处理


#endif
