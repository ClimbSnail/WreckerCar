#ifndef _TB6612_H_
#define _TB6612_H_

#include "60s2.h"
#include "delay.h"

#define uchar unsigned char
#define uint  unsigned int

sbit CARPwm1 = P2^0;
sbit CAR1 = P2^6;
sbit CAR2 = P2^7;

sbit CARPwm2 = P2^2;
sbit CARPwm3 = P2^3;
sbit CAR3 = P1^5;
sbit CAR4 = P1^6;

sbit WaterPwm = P2^4;
sbit CleanPwm = P1^3;

sbit LEDPwm = P2^1;
sbit CAR5 = P4^4;
sbit CAR6 = P4^5;
sbit CAR7 = P4^6;
sbit CAR8 = P1^7;

//各个速度值
extern uchar CAR12Speed;
extern uchar CAR34Speed;
extern uchar WaterSpeed;
extern uchar CleanSpeed;
extern uchar LedSpeed;

extern void Forward();//向前
extern void Back();//向后
extern void Turnrigth();//右转
extern void Turnleft();//左转
extern void Stop();//停车
extern void StartWater();//开启水箱
extern void StopWater();//停止水箱
extern void StartClean();//开启清洁
extern void StopClean();//停止清洁
extern void SetLed(uchar num);//num为0时关闭 开启的值为1-9,1最大 9最小
extern void SetSpeed(uchar s);//设置速度 值为1-9,1最大 9最小 0时关闭


#endif