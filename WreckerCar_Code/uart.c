#include "uart.h"

//uchar message = 0; //��Ϣ
//uchar receiveFlag = 0;//���ձ�־

//ʹ�ö��������ʷ�����
void uart_init12M(uint  baudRate)		//���ڳ�ʼ�� 2400~57600bps@12MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T

	//�趨���������ʷ�������װֵ
	switch( baudRate )
	{
	case 2400 : BRT = 0x64;break;//2400bps
	case 4800 : BRT = 0x04;break;//4800bps
	case 9600 : BRT = 0xD9;break;//9600bps
	case 19200: BRT = 0xEC;break;//19200bps
	case 38400: BRT = 0xF6;break;//38400bps
	case 57600: BRT = 0xF9;break;//57600bps
	default   : BRT = 0xD9;break;//9600bps
	}
			
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
}

void uart_init110592M(uint baud_rate)		//���ڳ�ʼ�� 2400~57600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T

	//�趨���������ʷ�������װֵ
	switch( baud_rate )
	{
	case 2400 : BRT = 0x70;break;//2400bps
	case 4800 : BRT = 0xB8;break;//4800bps
	case 9600 : BRT = 0xDC;break;//9600bps
	case 19200: BRT = 0xEE;break;//19200bps
	case 38400: BRT = 0xF7;break;//38400bps
	case 57600: BRT = 0xFA;break;//57600bps
	default   : BRT = 0xDC;break;//9600bps 
	}
			
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
}

void UART_send_char(uchar *dat)		  //�����ַ���
{
	int i;
	for(i = 0 ; dat[i] ; i++ )
	{
		SBUF = dat[i];   //��Ҫ���͵����ݷ��뵽���ͼĴ���
		while(!TI);		  //�ȴ������������
		TI=0;			  //���������ɱ�־λ	
	}
	SBUF = 0x0A;
	while(!TI);		  //�ȴ������������
	TI=0;			  //���������ɱ�־λ	
}

void UART_send(uchar dat)		  //�����ַ�
{
	SBUF = dat;
	while(!TI);		  //�ȴ������������
	TI=0;			  //���������ɱ�־λ	
}

int UART_check(uchar dat)	  //��У��
{
	 uint i,count=0;
	 for( i = 0 ; i<8 ; i++ )
	 {
	 	if( dat&0x01 )
			count++;
		dat >>= 1;
	 }
	 return count%2;
}

////����1�ж�
//void uart(void) interrupt 4
//{
//	if( RI )
//	{
//		RI = 0;	 //����λ����
//		receiveFlag = 1;//���ձ�־λ��1
//		message = SBUF;	
////���³��������
////		SBUF = message;
////		while(!TI);		  //�ȴ������������
////		TI=0;			  //���������ɱ�־λ	
//	}
//}