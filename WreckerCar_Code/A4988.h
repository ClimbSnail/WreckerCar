#ifndef __A4988_H
#define __A4988_H

#include "60s2.h"
#include "delay.h"

#define uchar unsigned char
#define uint  unsigned int

extern void SetPulsePositive (uint Number); //设置脉冲正向发生脉冲个数
extern void SetPulseReverse(uint Number);	  //设置脉冲反向发生脉冲个数

#endif