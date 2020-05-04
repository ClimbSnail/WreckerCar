#include "A4988.h"

sbit DIR = P3^7;
sbit STEP = P3^6;
sbit ENA = P3^5;////步进驱动使能口

void SetPulsePositive (uint Number)//向上
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

void SetPulseReverse(uint Number)//向下
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

