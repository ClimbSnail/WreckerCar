#ifndef __UART_H
#define __UART_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int

//extern uchar receiveFlag;  //���ձ�־
//extern uchar message;	 //��Ϣ
extern void uart_init12M(uint  baudRate);//���ڳ�ʼ�� baud_rateΪҪ�趨��ֵ 12M����
extern void uart_init110592M(uint  baudRate);//���ڳ�ʼ�� baud_rateΪҪ�趨��ֵ 11.0592M����
extern void UART_send_char(uchar *dat); //�����ַ���
extern void UART_send(uchar dat);		  //�����ַ�
extern int UART_check(uchar dat);//��У��

#endif