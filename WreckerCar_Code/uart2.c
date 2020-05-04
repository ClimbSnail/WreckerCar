#include "uart2.h"

void usart_init()
{
    S2CON|= 0x50;
    SCON|= 0x50;          //8-bit variable UART
    BRT = -(FOSC/32/BAUD);  //Set auto-reload vaule of baudrate generator
    AUXR|= 0x15;            //Baudrate generator work in 1T mode
    IE2 |= 0x01;             //Enable UART2 interrupt
    TR1 = 1;                //Timer1 start run
    ES = 1;
    EA = 1;
}