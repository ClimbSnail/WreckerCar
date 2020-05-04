#include "uart.h"

//uchar message = 0; //消息
//uchar receiveFlag = 0;//接收标志

//使用独立波特率发生器
void uart_init12M(uint  baudRate)		//串口初始化 2400~57600bps@12MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T

	//设定独立波特率发生器重装值
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
			
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
}

void uart_init110592M(uint baud_rate)		//串口初始化 2400~57600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T

	//设定独立波特率发生器重装值
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
			
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
}

void UART_send_char(uchar *dat)		  //发送字符串
{
	int i;
	for(i = 0 ; dat[i] ; i++ )
	{
		SBUF = dat[i];   //将要发送的数据放入到发送寄存器
		while(!TI);		  //等待发送数据完成
		TI=0;			  //清除发送完成标志位	
	}
	SBUF = 0x0A;
	while(!TI);		  //等待发送数据完成
	TI=0;			  //清除发送完成标志位	
}

void UART_send(uchar dat)		  //发送字符
{
	SBUF = dat;
	while(!TI);		  //等待发送数据完成
	TI=0;			  //清除发送完成标志位	
}

int UART_check(uchar dat)	  //奇校验
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

////串口1中断
//void uart(void) interrupt 4
//{
//	if( RI )
//	{
//		RI = 0;	 //接收位清零
//		receiveFlag = 1;//接收标志位置1
//		message = SBUF;	
////以下程序测试用
////		SBUF = message;
////		while(!TI);		  //等待发送数据完成
////		TI=0;			  //清除发送完成标志位	
//	}
//}