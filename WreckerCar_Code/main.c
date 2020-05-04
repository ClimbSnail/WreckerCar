#include "60s2.h"
#include "timer.h"
#include "uart.h"
#include "uart2.h"
#include "delay.h"
#include "external.h"
#include "math.h"
#include "action.h"
#include "oled.h"
#include "A4988.h"
#include "TB6612.h"

#define uchar unsigned char
#define uint  unsigned int

char FruitFall = 0;
char count = 0;//采摘水果的计数值
int temp;
uchar message = 0x00; //消息
uchar receiveFlag = 0x00;//接收标志
bit busy;
uchar dat[4]= {0,0x80,0x80,0};	//Camera接收的缓冲区
uchar dat_pos = 0;	  //串口2数据缓冲器
uchar uart2flag = 0;  //串口2接收标志
//uchar CameraStatus = 0;	  //摄像头开启标志
//uchar TCameraStatus = 0;  //摄像头使能状态标志记录
uchar BluetoothLink = 0;	//蓝牙连接标志 蓝牙连接时会发送一串"乱码" 设置标志位用来消除
uchar brightness = 0;
int pwm2;
int pwm3;

float x=100,z=150;//实际坐标点

void Uart2() interrupt 8 using 1
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
        dat[dat_pos] = S2BUF;
//		S2BUF = dat[dat_pos];
        if( dat[dat_pos] == 0xff )
            dat_pos = 1;
        else
        {
            dat_pos++;
            if( dat_pos == 4 )
                uart2flag = 1;
            dat_pos %= 4;
        }
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}
void uart(void) interrupt 4
{
    if( RI )
    {
        RI = 0;	 //接收位清零
        receiveFlag = 1;//接收标志位置1
        message = SBUF;	//接收信息
				if( message == 0xff )		//蓝牙连接时会发送一串"乱码" 设置标志位用来消除
				{
					BluetoothLink = !BluetoothLink;
					Stop();//车轮停止
					StopWater();//停止抽水
					set_circle_pwm7(0);//关闭pwm7循环转
					StopClean();//停止清洁
					SetLed(0);//关灯
				}

//以下程序测试用
//		SBUF = message;
//		while(!TI);		  //等待发送数据完成
//		TI=0;			  //清除发送完成标志位
    }
}

void Camera_RECEIVE()//摄像头信息处理程序
{
    
}
void RECEIVE_JUGE( )//蓝牙信息处理程序
{
	if( BluetoothLink )//蓝牙连接时会发送一串"乱码" 设置标志位用来消除
	{
    if( receiveFlag == 1 )
    {
        switch( message )
        {
        case 0x00:         
            receiveFlag = 0;
						Stop();
            break;
        case 0x01://向前
            if( x*x+z*z<=58000 && x<240 && z>0)
            {
                if( x*x+z*z>=55000 && z>=0.5f)
                    z -= 0.5f;
                x += 0.5f;
                Change_angle(x,z);
            }
            else if( x*x+z*z>58000 && z>0 )
                x-=0.5f;
            else if( z<=0)
            {
                z+=0.1f;
								pwm2 = 2300+z*10;
								pwm3 = 2000+z*10;
								pwm_change(2,pwm2);
								pwm_change(3,pwm3);
								pwm_change(4,2300);
            }
//			Delay200us();
            break;
        case 0x02://向后
            if( x*x+z*z>=32000 && x>5 && z>0)
            {
                if( x*x+z*z<=33000 && z<240 )
                    z += 0.5f;
                x-=0.5f;
                Change_angle(x,z);
            }
            else if( x*x+z*z>=32000 && z>0 )
                x+=0.5f;
						else if( z <= 0 )
						{
								z-=0.1f;
								pwm2 = 2300+z*10;
								pwm3 = 2000+z*10;
								pwm_change(2,pwm2);
								pwm_change(3,pwm3);
								pwm_change(4,2300);
						}
//			Delay200us();
            break;
        case 0x03://向上
            if( z>0 )
            {
                if( x*x+z*z<58000 )
                {
                    if( x*x+z*z>=55000 && x>5 )
                        x-=0.5f;
                    z+=0.5f;
                    Change_angle(x,z);
                }
                else if( x*x+z*z>=58000 )
                {
                    z-=0.5f;
                }
            }
            else
							{
								z+=0.1f;
								pwm2 = 2300+z*10;
								pwm3 = 2000+z*10;
								pwm_change(2,pwm2);
								pwm_change(3,pwm3);
								pwm_change(4,2300);
							}
//			Delay200us();
            break;
        case 0x04://向下
            if( z>0 )
            {
                if( x*x+z*z>=32000 )
                {
                    if( x*x+z*z<=33000 && x<240)
                        x+=0.5f;
                    z-=0.5f;
                    Change_angle(x,z);
                }
            }
            else
							{
								z-=0.1f;
								pwm2 = 2300+z*10;
								pwm3 = 2000+z*10;
								pwm_change(2,pwm2);
								pwm_change(3,pwm3);
								pwm_change(4,2300);
							}
//			Delay200us();
            break;
        case 0x05:
            temp = 	getSteering(5);
            if(temp>=2497)pwm_change(5,2497); //逆时针
						else
							pwm_change(5,temp+1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x06:
            temp = 	getSteering(5);
            if(temp<=503)pwm_change(5,503); //顺时针
						else
							pwm_change(5,temp-1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x07:
            temp = 	getSteering(0);
            if(temp>=1600)pwm_change(0,1600); //夹紧
						else
							pwm_change(0,temp+1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x08:
            temp = 	getSteering(0);
            if(temp<=900)
							pwm_change(0,900); //松开
						else
						pwm_change(0,temp-1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x09://前进
						Forward();
            Delay100ms();
            break;
        case 0x0a://后退
						Back();
            Delay100ms();
            break;
        case 0x0b://顺拐
						Turnrigth();
            Delay100ms();
            break;
        case 0x0c://逆拐
						Turnleft();
            Delay100ms();
            break;
        case 0x0d://打开水泵
            StartWater();
            break;
        case 0x0e://关闭水泵
            StopWater();
            break;
        case 0x0f://开始清洁
						StartClean();
            break;
        case 0x10://停止清洁
						StopClean();
            break;
        case 0x11:
            SetPulsePositive(1000);//铲斗向上
						receiveFlag = 0;
						break;
        case 0x12:
            SetPulseReverse(1000);//铲斗向下
						receiveFlag = 0;
						break;
				case 0x13:
						set_circle_pwm7(1);//启用pwm7循环转
						receiveFlag = 0;
						break;
				case 0x14:
						set_circle_pwm7(0);//关闭pwm7循环转
						receiveFlag = 0;
						break;
				case 0x15://开垃圾箱
						open_Dustbin(1);//开关垃圾箱 1为启用 0为关闭
						receiveFlag = 0;
						break;
				case 0x16://关垃圾箱
						open_Dustbin(0);//开关垃圾箱 1为启用 0为关闭
						receiveFlag = 0;
						break;
				case 0x17://Led增量一个单位
						if( brightness == 1 )
							brightness = 1;
						else
							brightness = (brightness+10-1)%10;
						SetLed(brightness);//num为0时关闭 开启的值为1-9,1最大 9最小
						receiveFlag = 0;
						break;
				case 0x18://Led减小一个单位
						if( brightness == 0 )
							brightness = 0;
						else
							brightness = (brightness+1)%10;
						SetLed(brightness);//num为0时关闭 开启的值为1-9,1最大 9最小
						receiveFlag = 0;
						break;
				case 0x19://车速调最高
					SetSpeed(1);//设置速度 值为1-9,1最大 9最小 0时关闭
					break;
				case 0x1A://车速调一半
					SetSpeed(8);//设置速度 值为1-9,1最大 9最小 0时关闭
					break;
        default:
            break;
        }

    }
	}
}


void main()	//主程序
{
		P0 = 0x00;
		P1 = 0x00;
		P2 = 0xff;
		P3 = 0xdf;//步进驱动使能关
    P4SW |= 0x70;	 //启用P4.4 P4.5 P4.6
	
		SetLed(0);//num为0时关闭 开启的值为1-9,1最大
	
//    OLED_Init();
//    OLED_Clear();
//    OLED_ShowCHinese(0,0,9);//辽
//    OLED_ShowCHinese(20,0,10);//宁
//    OLED_ShowCHinese(40,0,5);//科
//    OLED_ShowCHinese(60,0,6);//技
//    OLED_ShowCHinese(80,0,11);//大
//    OLED_ShowCHinese(100,0,12);//学
//    OLED_ShowCHinese(0,4,17);//水
//    OLED_ShowCHinese(14,4,18);//果
//    OLED_ShowCHinese(28,4,19);//采
//    OLED_ShowCHinese(42,4,20);//摘
//    OLED_ShowCHinese(56,4,21);//累
//    OLED_ShowCHinese(70,4,22);//计
//    OLED_ShowChar(84,4,':');
//    OLED_ShowNum(92,4,0,3,16);//显示ASCII字符的码值
		
	  pwm_change(0,900);
		pwm_change(1,1500);
		pwm_change(2,1500-90);
    pwm_change(3,1500-70);
    pwm_change(4,1500);
    updata_TimingLeft();//更新剩余低电平时间
		
//    usart_init();
    uart_init12M(9600); //串口初始化
    timer0_init();//定时器0初始化
		timer1_init();//定时器1初始化
    steering_init();//舵机参数的初始化
//    ext0_init();	//外部中断0初始化
//    ext1_init();	//外部中断1初始化
    while(1)
    {
        RECEIVE_JUGE();  //串口接收判断
    }
}
