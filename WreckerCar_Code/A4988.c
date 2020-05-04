#include "A4988.h"

sbit DIR = P3^7;
sbit STEP = P3^6;
sbit ENA = P3^5;////��������ʹ�ܿ�

void SetPulsePositive (uint Number)//����
{
    DIR = 1;
		ENA = 1;
    while( Number-- )
    {
        STEP = 0;
        Delay200us();
				Delay200us();
        STEP = 1;
        Delay200us();
				Delay200us();
    }
		ENA = 0;
}

void SetPulseReverse(uint Number)//����
{
    DIR = 0;
		ENA = 1;
    while( Number-- )
    {
        STEP = 0;
        Delay200us();
				Delay200us();
        STEP = 1;
        Delay200us();
				Delay200us();
    }
		ENA = 0;
}

