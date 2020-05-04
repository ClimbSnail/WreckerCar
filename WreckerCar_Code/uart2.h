#ifndef __UART2_H
#define __UART2_H
#include "60s2.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

//#define FOSC 11059200L      //System frequency
#define FOSC 12000000L      //System frequency
#define BAUD 9600         //UART baudrate

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT EVEN_PARITY   //Testing even parity

/*Declare SFR associated with the UART2 */
//sfr AUXR  = 0x8e;           //Auxiliary register
//sfr S2CON = 0x9a;           //UART2 control register
//sfr S2BUF = 0x9b;           //UART2 data buffer
//sfr BRT   = 0x9c;           //Baudrate generator
//sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3
void usart_init();

#endif
