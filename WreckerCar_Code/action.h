#ifndef __ACTION_H
#define __ACTION_H

#include "math.h"
#include "timer.h"
#define uchar unsigned char
#define uint  unsigned int


extern void steering_pwm_change();//���PWM�ĸ���
extern void steering_init();//�����ʼ��
extern void Change_angle(float x,float z);	 //���㲢���¶���Ƕ�

#endif