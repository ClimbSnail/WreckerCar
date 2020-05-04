#ifndef __ADC_H
#define __ADC_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int

extern void ADC_init();//AD采集的初始化	P1.6与P1.7
extern uint ADValue[2];//用来存AD采集完的两个变量

#endif