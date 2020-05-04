#ifndef __UART_H
#define __UART_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int

//extern uchar receiveFlag;  //接收标志
//extern uchar message;	 //消息
extern void uart_init12M(uint  baudRate);//串口初始化 baud_rate为要设定的值 12M晶振
extern void uart_init110592M(uint  baudRate);//串口初始化 baud_rate为要设定的值 11.0592M晶振
extern void UART_send_char(uchar *dat); //发送字符串
extern void UART_send(uchar dat);		  //发送字符
extern int UART_check(uchar dat);//奇校验

#endif