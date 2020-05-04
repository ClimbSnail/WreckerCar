#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

#include "60s2.h"
#include "delay.h"


extern void ext0_init();	   //外部中断0的初始化
extern char get_ext0();	    //查询是否产生中断

extern void ext1_init();	   //外部中断1的初始化
extern char get_ext1();	    //查询是否产生中断

#endif