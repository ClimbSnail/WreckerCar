#ifndef __IIC_H
#define __IIC_H

#include "60s2.h"
#define uchar unsigned char
#define uint  unsigned int

//--����ʹ�õ�IO��--//
sbit I2C_SCL = P1^0;
sbit I2C_SDA = P1^1;

//--����ȫ�ֱ���--//
extern void I2C_Start();//��ʼ�ź�
extern void I2C_Stop();//��ֹ�ź�
extern void I2C_SendByte(uchar dat);//����һ���ֽ�
extern uchar I2C_ReadByte();//��ȡһ���ֽ�
extern void I2C_SendACK(bit ack);//����Ӧ���ź�
extern bit I2C_RecvACK();//����Ӧ���ź�
extern void WriteI2C(uchar SlaveAddress,uchar REG_Address,uchar REG_data);//ָ����ַ��д������
extern uchar ReadI2C(uchar SlaveAddress,uchar REG_Address);//��ȡָ����ַ�µ�����

#endif