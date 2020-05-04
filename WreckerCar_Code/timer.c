#include "timer.h"
#include "TB6612.h"

//��ʱֵ�ĸ�8λ���8λ
static uchar timingValueH[9]= {0xFA,0xFA,0xFE,0xFE,0xFC,0xFA,0xFD,0xFB, 0x00};
static uchar timingValueL[9]= {0x24,0x24,0x0C,0x0C,0x18,0x24,0xDA,0xB3, 0x00};
//   0xF6	0x3C

//��ʱ����ʹ�õĶ�ʱ����ֵ�±�
static uchar pwm_flag0 = 0;
static uint pwm_flag1 = 0;
static uchar pwm7H = 0xFB;
static uchar pwm7L = 0xB3;
uchar pos;

//�͵�ƽ��ʣ��ʱ��
static uint timingLeftValue0 = 0;

static uchar pwm;
//P0��ӦPWM0~7   Ŀǰ������û����
sbit pwm0 = P0^0;
sbit pwm1 = P0^1;
sbit pwm2 = P0^2;
sbit pwm3 = P0^3;
sbit pwm4 = P0^4;
sbit pwm5 = P0^5;
sbit pwm6 = P0^6;
sbit pwm7 = P0^7;


//��ʱ��0��ʼ��
void timer0_init()
{
    EA = 1;	  //�������ж�
    ET0 = 1;	   // ��ʱ��0����
    TMOD |= 0x01;//���ö�ʱ��0Ϊ������ʽ1(16λ������)
    //�ȳ�ʼ��ֵpwm0
    TH0 = timingValueH[0];
    TL0 = timingValueL[0];
    TR0 = 1;//��ʱ��0��ʼ����
}
//��ʱ��1��ʼ��
void timer1_init()
{
    EA = 1;	  //�������ж�
    ET1 = 1;	   // ��ʱ��1����
    TMOD |= 0x10;//���ö�ʱ��0Ϊ������ʽ1(16λ������)
    //�ȳ�ʼ��ֵpwm9
    TH1 = timingValueH[8];
    TL1 = timingValueL[8];
    TR1 = 1;//��ʱ��1��ʼ����
}

//��ʱ���ж�0
void timer0 (void) interrupt 1
{

    if( pwm_flag0 == 8 )  //��Ҫִ��PWM8ʱ
    {
        P0 = 0x00;
        TH0 = timingValueH[8];
        TL0 = timingValueL[8];
    }
    else				  //��ʱPWM0~7
    {
        if( pwm_flag0 == 0 )
            P0 = 0x01;
        else
            P0 <<= 1;
        TH0 = timingValueH[pwm_flag0]; //��ʱʱ�丳ֵ
        TL0 = timingValueL[pwm_flag0];
    }
    pwm_flag0 = (pwm_flag0+1)%9;	//�±��ƽ�
}

//��ʱ���ж�1
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


void pwm_change(uchar pwmNumber,uint pwmDuty)	//pwmNumber��Χ0~7 pwmDuty(1~2500us)
{
    pwmDuty = 65536-pwmDuty;
//�ȸı䶨ʱʱ���ֵ
//	timingValueH[pwmNumber]	=  pwmDuty/256;
//	timingValueL[pwmNumber]	=  pwmDuty%256;
//ʹ��λ����,�����ٶȸ���
    timingValueH[pwmNumber]	=  pwmDuty>>8;
    timingValueL[pwmNumber]	=  (pwmDuty<<8)>>8;

//	if( pwmNumber == 5 )
//		SREET6 = 65536-(timingValueH[5]*256+timingValueL[5]);
//	if( pwmNumber == 0 )
//		SREET1 = 65536-(timingValueH[0]*256+timingValueL[0]);
}

//����ʣ��͵�ƽʱ��
void updata_TimingLeft()
{
    uchar count;
    //����ʣ��͵�ƽ��ʣ��ʱ��
    timingLeftValue0 = 65536-20000;
    for( count = 0 ; count<8 ; count++ )
        timingLeftValue0 += ( 65536-(timingValueH[count]*256+timingValueL[count]) );
    timingValueH[8] = timingLeftValue0>>8;	//����ʣ��͵�ƽʱ��
    timingValueL[8] = (timingLeftValue0<<8)>>8;
}

int getSteering(int num)
{
    return 65536-(timingValueH[num]*256+timingValueL[num]);
}


void set_circle_pwm7(uchar num)//����pwm7ѭ��ת 1Ϊ���� 0Ϊ�ر�
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

void open_Dustbin(uchar num)//���������� 1Ϊ���� 0Ϊ�ر�
{
	if( num )//�ߵ�ƽ1500us
	{
		timingValueH[6] = 0xFA;
		timingValueL[6] = 0x24;
	}
	else//�ߵ�ƽ550us
	{
		timingValueH[6] = 0xFD;
		timingValueL[6] = 0xDA;
	}
}