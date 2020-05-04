#include "timer.h"
#include "TB6612.h"

//定时值的高8位与低8位
static uchar timingValueH[9]= {0xFA,0xFA,0xFE,0xFE,0xFC,0xFA,0xFD,0xFB, 0x00};
static uchar timingValueL[9]= {0x24,0x24,0x0C,0x0C,0x18,0x24,0xDA,0xB3, 0x00};
//   0xF6	0x3C

//定时器中使用的定时计数值下标
static uchar pwm_flag0 = 0;
static uint pwm_flag1 = 0;
static uchar pwm7H = 0xFB;
static uchar pwm7L = 0xB3;
uchar pos;

//低电平的剩余时间
static uint timingLeftValue0 = 0;

static uchar pwm;
//P0对应PWM0~7   目前申明都没用上
sbit pwm0 = P0^0;
sbit pwm1 = P0^1;
sbit pwm2 = P0^2;
sbit pwm3 = P0^3;
sbit pwm4 = P0^4;
sbit pwm5 = P0^5;
sbit pwm6 = P0^6;
sbit pwm7 = P0^7;


//定时器0初始化
void timer0_init()
{
    EA = 1;	  //开启总中断
    ET0 = 1;	   // 定时器0可用
    TMOD |= 0x01;//设置定时器0为工作方式1(16位计数器)
    //先初始赋值pwm0
    TH0 = timingValueH[0];
    TL0 = timingValueL[0];
    TR0 = 1;//定时器0开始计数
}
//定时器1初始化
void timer1_init()
{
    EA = 1;	  //开启总中断
    ET1 = 1;	   // 定时器1可用
    TMOD |= 0x10;//设置定时器0为工作方式1(16位计数器)
    //先初始赋值pwm9
    TH1 = timingValueH[8];
    TL1 = timingValueL[8];
    TR1 = 1;//定时器1开始计数
}

//定时器中断0
void timer0 (void) interrupt 1
{

    if( pwm_flag0 == 8 )  //当要执行PWM8时
    {
        P0 = 0x00;
        TH0 = timingValueH[8];
        TL0 = timingValueL[8];
    }
    else				  //定时PWM0~7
    {
        if( pwm_flag0 == 0 )
            P0 = 0x01;
        else
            P0 <<= 1;
        TH0 = timingValueH[pwm_flag0]; //定时时间赋值
        TL0 = timingValueL[pwm_flag0];
    }
    pwm_flag0 = (pwm_flag0+1)%9;	//下标推进
}

//定时器中断1
void timer1 (void) interrupt 3
{
		TH1 = 0xFC;
    TL1 = 0x18;
//		TH1 = 0xF4;
//    TL1 = 0x48;
		pwm_flag1 = (pwm_flag1+1)%2000;
		
		pos = pwm_flag1%10;
		
		if( CAR12Speed == pos )
		{
			CARPwm1 = 1;
		}
		if( CAR34Speed == pos )
		{
			CARPwm2 = 1;
			CARPwm3 = 1;
		}
		if( WaterSpeed == pos )
		{
			WaterPwm = 1;
		}
		if( CleanSpeed == pos )
		{
			CleanPwm = 1;
		}
		if( LedSpeed == pos )
		{
			LEDPwm = 1;
		}
		
		if( pos == 0 )
		{
			CARPwm1 = 0;
			CARPwm2 = 0;
			CARPwm3 = 0;
			WaterPwm = 0;
			CleanPwm = 0;
			LEDPwm = 0;
		}
		
		if( pwm_flag1 == 999)
		{
			timingValueH[7] = 0xFB;
			timingValueL[7] = 0xB3;
			updata_TimingLeft();
		}
		if( pwm_flag1 == 1999)
		{
			timingValueH[7] = pwm7H;
			timingValueL[7] = pwm7L;
			updata_TimingLeft();
		}
}


void pwm_change(uchar pwmNumber,uint pwmDuty)	//pwmNumber范围0~7 pwmDuty(1~2500us)
{
    pwmDuty = 65536-pwmDuty;
//先改变定时时间的值
//	timingValueH[pwmNumber]	=  pwmDuty/256;
//	timingValueL[pwmNumber]	=  pwmDuty%256;
//使用位操作,运算速度更快
    timingValueH[pwmNumber]	=  pwmDuty>>8;
    timingValueL[pwmNumber]	=  (pwmDuty<<8)>>8;

//	if( pwmNumber == 5 )
//		SREET6 = 65536-(timingValueH[5]*256+timingValueL[5]);
//	if( pwmNumber == 0 )
//		SREET1 = 65536-(timingValueH[0]*256+timingValueL[0]);
}

//更新剩余低电平时间
void updata_TimingLeft()
{
    uchar count;
    //计算剩余低电平的剩余时间
    timingLeftValue0 = 65536-20000;
    for( count = 0 ; count<8 ; count++ )
        timingLeftValue0 += ( 65536-(timingValueH[count]*256+timingValueL[count]) );
    timingValueH[8] = timingLeftValue0>>8;	//更新剩余低电平时间
    timingValueL[8] = (timingLeftValue0<<8)>>8;
}

int getSteering(int num)
{
    return 65536-(timingValueH[num]*256+timingValueL[num]);
}


void set_circle_pwm7(uchar num)//启用pwm7循环转 1为启用 0为关闭
{
	if( num )
	{
		pwm7H = 0xF8;
		pwm7L = 0xF7;
	}
	else
	{
		pwm7H = 0xFB;
		pwm7L = 0xB3;
	}
}

void open_Dustbin(uchar num)//开关垃圾箱 1为启用 0为关闭
{
	if( num )//高电平1500us
	{
		timingValueH[6] = 0xFA;
		timingValueL[6] = 0x24;
	}
	else//高电平550us
	{
		timingValueH[6] = 0xFD;
		timingValueL[6] = 0xDA;
	}
}