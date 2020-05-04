//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ÖĞ¾°Ô°µç×Ó
//µêÆÌµØÖ·£ºhttp://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  ÎÄ ¼ş Ãû   : main.c
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : HuangKai
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üĞŞ¸Ä   : 
//  ¹¦ÄÜÃèÊö   : OLED 4½Ó¿ÚÑİÊ¾Àı³Ì(51ÏµÁĞ)
//              ËµÃ÷: 
//              ----------------------------------------------------------------
//              GND    µçÔ´µØ
//              VCC  ½Ó5V»ò3.3vµçÔ´
//              D0   P1^0£¨SCL£©
//              D1   P1^1£¨SDA£©
//              RES  ½ÓP12
//              DC   ½ÓP13
//              CS   ½ÓP14               
//              ----------------------------------------------------------------
// ĞŞ¸ÄÀúÊ·   :
// ÈÕ    ÆÚ   : 
// ×÷    Õß   : HuangKai
// ĞŞ¸ÄÄÚÈİ   : ´´½¨ÎÄ¼ş
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÖĞ¾°Ô°µç×Ó2014/3/16
//All rights reserved
//******************************************************************************/
#include "60s2.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//Ğ´ÃüÁî
#define OLED_DATA 1	//Ğ´Êı¾İ
#define OLED_MODE 0

sbit OLED_CS=P1^4; //Æ¬Ñ¡
sbit OLED_RST =P4^2;//¸´Î»
sbit OLED_DC =P4^1;//Êı¾İ/ÃüÁî¿ØÖÆ
sbit OLED_SCL=P1^1;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^0;//D1£¨MOSI£© Êı¾İ


#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;


//OLEDÄ£Ê½ÉèÖÃ
//0:4Ïß´®ĞĞÄ£Ê½
//1:²¢ĞĞ8080Ä£Ê½

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED¶Ë¿Ú¶¨Òå----------------  					   

void delay_ms(unsigned int ms);	     

//OLED¿ØÖÆÓÃº¯Êı
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);	  //¿ªÆôOLEDÏÔÊ¾
void OLED_Display_Off(void);//¹Ø±ÕOLEDÏÔÊ¾	   							   		    
void OLED_Init(void);		//³õÊ¼»¯
void OLED_Clear(void);	//ÇåÆÁº¯Êı,ÇåÍêÆÁ,Õû¸öÆÁÄ»ÊÇºÚÉ«µÄ!ºÍÃ»µãÁÁÒ»Ñù!!!
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);	//ÏÔÊ¾×Ö·û
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y, u8 *p);	//ÏÔÊ¾Ò»¸ö×Ö·ûºÅ´® 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);	//ÏÔÊ¾ºº×Ö
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);	 //ÏÔÊ¾BMPÍ¼Æ¬
#endif  
	 



