#include "external.h"

static char ext0,ext1;   //中断的标志位

void exint0(void) interrupt 0  //外部中断0的中断服务程序
{
    ext0 = 1;
}

void ext0_init()		//外部中断0的初始化
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    ext0 = 0;
}

char get_ext0()		  //查询是否产生中断
{
    char temp = ext0;
    ext0 = 0;
    return temp;	//返回查询的值
}

void exint1(void) interrupt 2  //外部中断0的中断服务程序
{
    ext1 = 1;
}

void ext1_init()		//外部中断0的初始化
{
    IT1 = 1;
    EX1 = 1;
    EA = 1;
    ext1 = 0;
}

char get_ext1()		  //查询是否产生中断
{
    char temp = ext1;
    ext1 = 0;
    return temp;	//返回查询的值
}

