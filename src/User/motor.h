#ifndef __MOTOR_H
#define __MOTOR_H


#include "struct.h"
#include "common.h"
#include "include.h"


//#define DIR_PORT        PTC6
//#define DIR             GPIO_Get(PTC6) //电机方向

void motor_init(void);

void motor_set(int16 duty);
void motor_pid_caculate(Motor_pid_info *motor_info);




#define MOTOR_DUTY_MAX       150
#define MOTOR_DUTY_MIN       -150



void motor_pid_caculate(Motor_pid_info *motor_info);


#endif
