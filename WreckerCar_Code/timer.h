#ifndef __TIMER_H
#define __TIMER_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int


extern int getSteering(int num);//获取舵机的值
extern void timer0_init();//定时器0初始化
extern void timer1_init();//定时器1初始化
extern void pwm_change(uchar pwmNumber,uint pwmDuty); //pwmNumber范围0~7 pwmDuty(1~2500)
extern void updata_TimingLeft();	//更新剩余低电平时间
extern void set_circle_pwm7(uchar num);//启用pwm7循环转 1为启用 0为关闭
extern void open_Dustbin(uchar num);//开关垃圾箱 1为启用 0为关闭


#endif