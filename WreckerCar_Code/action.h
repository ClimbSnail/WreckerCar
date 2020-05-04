#ifndef __ACTION_H
#define __ACTION_H

#include "math.h"
#include "timer.h"
#define uchar unsigned char
#define uint  unsigned int


extern void steering_pwm_change();//舵机PWM的更新
extern void steering_init();//舵机初始化
extern void Change_angle(float x,float z);	 //计算并更新舵机角度

#endif