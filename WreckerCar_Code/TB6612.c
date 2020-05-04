#include "TB6612.h"

uchar CAR12Speed = 1;
uchar CAR34Speed = 1;//
uchar WaterSpeed = 0;//WaterPwm P2.4
uchar CleanSpeed = 0;//CleanPwm P2.5
uchar LedSpeed = 0;//LedPwm P2.1


void Forward()
{
	CAR1 = 1;
	CAR2 = 0;
	CAR3 = 1;
	CAR4 = 0;
}

void Back()
{
	CAR1 = 0;
	CAR2 = 1;
	CAR3 = 0;
	CAR4 = 1;
}

void Turnrigth()
{
	CAR1 = 0;
	CAR2 = 1;
	CAR3 = 1;
	CAR4 = 0;
}

void Turnleft()
{
	CAR1 = 1;
	CAR2 = 0;
	CAR3 = 0;
	CAR4 = 1;
}

void Stop()
{
	CAR1 = 0;
	CAR2 = 0;
	CAR3 = 0;
	CAR4 = 0;
}

void SetSpeed(uchar s)//�����ٶ� ֵΪ1-9,1��� 9��С 0ʱ�ر�
{
	CAR12Speed = s;
	CAR34Speed = s;
}

void StartWater()
{
	WaterSpeed = 3;
}

void StopWater()
{
	WaterSpeed = 0;
}

void StartClean()
{
	CleanSpeed = 3;
}

void StopClean()
{
	CleanSpeed = 0;
}

void SetLed(uchar num)//numΪ0ʱ�ر� ������ֵΪ1-9,1��� 9��С
{
	CAR5 = 0;
	CAR6 = 1;
	CAR7 = 0;
	CAR8 = 1;
	LedSpeed = num;
}

