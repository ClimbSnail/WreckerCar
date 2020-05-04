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

//�����ٶ�ֵ
extern uchar CAR12Speed;
extern uchar CAR34Speed;
extern uchar WaterSpeed;
extern uchar CleanSpeed;
extern uchar LedSpeed;

extern void Forward();//��ǰ
extern void Back();//���
extern void Turnrigth();//��ת
extern void Turnleft();//��ת
extern void Stop();//ͣ��
extern void StartWater();//����ˮ��
extern void StopWater();//ֹͣˮ��
extern void StartClean();//�������
extern void StopClean();//ֹͣ���
extern void SetLed(uchar num);//numΪ0ʱ�ر� ������ֵΪ1-9,1��� 9��С
extern void SetSpeed(uchar s);//�����ٶ� ֵΪ1-9,1��� 9��С 0ʱ�ر�


#endif