#ifndef __TIMER_H
#define __TIMER_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int


extern int getSteering(int num);//��ȡ�����ֵ
extern void timer0_init();//��ʱ��0��ʼ��
extern void timer1_init();//��ʱ��1��ʼ��
extern void pwm_change(uchar pwmNumber,uint pwmDuty); //pwmNumber��Χ0~7 pwmDuty(1~2500)
extern void updata_TimingLeft();	//����ʣ��͵�ƽʱ��
extern void set_circle_pwm7(uchar num);//����pwm7ѭ��ת 1Ϊ���� 0Ϊ�ر�
extern void open_Dustbin(uchar num);//���������� 1Ϊ���� 0Ϊ�ر�


#endif