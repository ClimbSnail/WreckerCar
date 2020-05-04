#include "delay.h"

void Delay2500ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 114;
    j = 255;
    k = 107;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay1000ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 46;
    j = 153;
    k = 245;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay500ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 23;
    j = 205;
    k = 120;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay300ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 14;
    j = 174;
    k = 224;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay200ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 10;
    j = 31;
    k = 147;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay150ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 7;
    j = 215;
    k = 238;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay100ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 5;
    j = 144;
    k = 71;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay20ms()		//@12.000MHz
{
    unsigned char i, j, k;

//	_nop_();
//	_nop_();
    i = 1;
    j = 234;
    k = 113;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

void Delay10ms()		//@12.000MHz
{
    unsigned char i, j;

    i = 117;
    j = 184;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay5ms()		//@12.000MHz
{
    unsigned char i, j;

    i = 59;
    j = 90;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay3ms()		//@12.000MHz
{
    unsigned char i, j;

    i = 36;
    j = 1;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay1ms()		//@12.000MHz
{
    unsigned char i, j;

    i = 12;
    j = 169;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay500us()		//@12.000MHz
{
    unsigned char i, j;

    i = 6;
    j = 211;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay200us()		//@12.000MHz
{
    unsigned char i, j;

    i = 3;
    j = 82;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay50us()		//@12.000MHz
{
    unsigned char i, j;

    i = 1;
    j = 146;
    do
    {
        while (--j);
    }
    while (--i);
}

void Delay20us()		//@12.000MHz
{
    unsigned char i;

//	_nop_();
//	_nop_();
    i = 57;
    while (--i);
}
