#ifndef __A4988_H
#define __A4988_H

#include "60s2.h"
#include "delay.h"

#define uchar unsigned char
#define uint  unsigned int

extern void SetPulsePositive (uint Number); //���������������������
extern void SetPulseReverse(uint Number);	  //�������巴�����������

#endif