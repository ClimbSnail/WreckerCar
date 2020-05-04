#ifndef __MPU6050_H
#define __MPU6050_H

#include "60s2.h"

#define uchar unsigned char
#define uint  unsigned int
	
//���ٶȸ�������ֵ
static int AccelXValue;
static int AccelYValue;
static int AccelZValue;
//�Ƕȸ�������ֵ
static int GyroXValue;
static int GyroYValue;
static int GyroZValue;
//�¶�ֵ
static int TempValue;

extern void InitMPU6050();//MPU6050��ʼ��
extern int GetData(uchar REG_Address);//��ȡָ����ַ�µ�����
extern void UpDataAll();//������������

#endif