#ifndef __SERVO_H
#define __SERVO_H

#include "struct.h"

#define  SERVO_MID_VAL    12300
#define  SERVO_LEFT_VAL    14300  //7200
#define  SERVO_RIGHT_VAL   10600   //11300


void servo_init(void);
void deal_sensor(Sensor_info *sensor);
void servo_pid_caculate(void);

#endif
