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
char count = 0;//��ժˮ���ļ���ֵ
int temp;
uchar message = 0x00; //��Ϣ
uchar receiveFlag = 0x00;//���ձ�־
bit busy;
uchar dat[4]= {0,0x80,0x80,0};	//Camera���յĻ�����
uchar dat_pos = 0;	  //����2���ݻ�����
uchar uart2flag = 0;  //����2���ձ�־
//uchar CameraStatus = 0;	  //����ͷ������־
//uchar TCameraStatus = 0;  //����ͷʹ��״̬��־��¼
uchar BluetoothLink = 0;	//�������ӱ�־ ��������ʱ�ᷢ��һ��"����" ���ñ�־λ��������
uchar brightness = 0;
int pwm2;
int pwm3;

float x=100,z=150;//ʵ�������

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
        RI = 0;	 //����λ����
        receiveFlag = 1;//���ձ�־λ��1
        message = SBUF;	//������Ϣ
				if( message == 0xff )		//��������ʱ�ᷢ��һ��"����" ���ñ�־λ��������
				{
					BluetoothLink = !BluetoothLink;
					Stop();//����ֹͣ
					StopWater();//ֹͣ��ˮ
					set_circle_pwm7(0);//�ر�pwm7ѭ��ת
					StopClean();//ֹͣ���
					SetLed(0);//�ص�
				}

//���³��������
//		SBUF = message;
//		while(!TI);		  //�ȴ������������
//		TI=0;			  //���������ɱ�־λ
    }
}

void Camera_RECEIVE()//����ͷ��Ϣ�������
{
    
}
void RECEIVE_JUGE( )//������Ϣ�������
{
	if( BluetoothLink )//��������ʱ�ᷢ��һ��"����" ���ñ�־λ��������
	{
    if( receiveFlag == 1 )
    {
        switch( message )
        {
        case 0x00:         
            receiveFlag = 0;
						Stop();
            break;
        case 0x01://��ǰ
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
        case 0x02://���
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
        case 0x03://����
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
        case 0x04://����
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
            if(temp>=2497)pwm_change(5,2497); //��ʱ��
						else
							pwm_change(5,temp+1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x06:
            temp = 	getSteering(5);
            if(temp<=503)pwm_change(5,503); //˳ʱ��
						else
							pwm_change(5,temp-1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x07:
            temp = 	getSteering(0);
            if(temp>=1600)pwm_change(0,1600); //�н�
						else
							pwm_change(0,temp+1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x08:
            temp = 	getSteering(0);
            if(temp<=900)
							pwm_change(0,900); //�ɿ�
						else
						pwm_change(0,temp-1);
            updata_TimingLeft();
            Delay1ms();
            break;
        case 0x09://ǰ��
						Forward();
            Delay100ms();
            break;
        case 0x0a://����
						Back();
            Delay100ms();
            break;
        case 0x0b://˳��
						Turnrigth();
            Delay100ms();
            break;
        case 0x0c://���
						Turnleft();
            Delay100ms();
            break;
        case 0x0d://��ˮ��
            StartWater();
            break;
        case 0x0e://�ر�ˮ��
            StopWater();
            break;
        case 0x0f://��ʼ���
						StartClean();
            break;
        case 0x10://ֹͣ���
						StopClean();
            break;
        case 0x11:
            SetPulsePositive(1000);//��������
						receiveFlag = 0;
						break;
        case 0x12:
            SetPulseReverse(1000);//��������
						receiveFlag = 0;
						break;
				case 0x13:
						set_circle_pwm7(1);//����pwm7ѭ��ת
						receiveFlag = 0;
						break;
				case 0x14:
						set_circle_pwm7(0);//�ر�pwm7ѭ��ת
						receiveFlag = 0;
						break;
				case 0x15://��������
						open_Dustbin(1);//���������� 1Ϊ���� 0Ϊ�ر�
						receiveFlag = 0;
						break;
				case 0x16://��������
						open_Dustbin(0);//���������� 1Ϊ���� 0Ϊ�ر�
						receiveFlag = 0;
						break;
				case 0x17://Led����һ����λ
						if( brightness == 1 )
							brightness = 1;
						else
							brightness = (brightness+10-1)%10;
						SetLed(brightness);//numΪ0ʱ�ر� ������ֵΪ1-9,1��� 9��С
						receiveFlag = 0;
						break;
				case 0x18://Led��Сһ����λ
						if( brightness == 0 )
							brightness = 0;
						else
							brightness = (brightness+1)%10;
						SetLed(brightness);//numΪ0ʱ�ر� ������ֵΪ1-9,1��� 9��С
						receiveFlag = 0;
						break;
				case 0x19://���ٵ����
					SetSpeed(1);//�����ٶ� ֵΪ1-9,1��� 9��С 0ʱ�ر�
					break;
				case 0x1A://���ٵ�һ��
					SetSpeed(8);//�����ٶ� ֵΪ1-9,1��� 9��С 0ʱ�ر�
					break;
        default:
            break;
        }

    }
	}
}


void main()	//������
{
		P0 = 0x00;
		P1 = 0x00;
		P2 = 0xff;
		P3 = 0xdf;//��������ʹ�ܹ�
    P4SW |= 0x70;	 //����P4.4 P4.5 P4.6
	
		SetLed(0);//numΪ0ʱ�ر� ������ֵΪ1-9,1���
	
//    OLED_Init();
//    OLED_Clear();
//    OLED_ShowCHinese(0,0,9);//��
//    OLED_ShowCHinese(20,0,10);//��
//    OLED_ShowCHinese(40,0,5);//��
//    OLED_ShowCHinese(60,0,6);//��
//    OLED_ShowCHinese(80,0,11);//��
//    OLED_ShowCHinese(100,0,12);//ѧ
//    OLED_ShowCHinese(0,4,17);//ˮ
//    OLED_ShowCHinese(14,4,18);//��
//    OLED_ShowCHinese(28,4,19);//��
//    OLED_ShowCHinese(42,4,20);//ժ
//    OLED_ShowCHinese(56,4,21);//��
//    OLED_ShowCHinese(70,4,22);//��
//    OLED_ShowChar(84,4,':');
//    OLED_ShowNum(92,4,0,3,16);//��ʾASCII�ַ�����ֵ
		
	  pwm_change(0,900);
		pwm_change(1,1500);
		pwm_change(2,1500-90);
    pwm_change(3,1500-70);
    pwm_change(4,1500);
    updata_TimingLeft();//����ʣ��͵�ƽʱ��
		
//    usart_init();
    uart_init12M(9600); //���ڳ�ʼ��
    timer0_init();//��ʱ��0��ʼ��
		timer1_init();//��ʱ��1��ʼ��
    steering_init();//��������ĳ�ʼ��
//    ext0_init();	//�ⲿ�ж�0��ʼ��
//    ext1_init();	//�ⲿ�ж�1��ʼ��
    while(1)
    {
        RECEIVE_JUGE();  //���ڽ����ж�
    }
}
