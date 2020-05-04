#include "adc.h"
#include "oled.h"

uint ADValue[2];

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC转换标志位
#define ADC_START   0x08            //ADC开始控制位
#define ADC_SPEED   0x60            //540

uchar chFlag = 0;
uchar ch[2]={6,7};	//选择P1.6与P1.7作为A/D输入口用

void Delay(uint n)
{
    uint x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

void ADC_init()
{
	EA = 1;		//开启总中断
	EADC = 1;	//允许A/D转换
	P1ASF = 0xC0;	//设置P1.7/P1.6为模拟功能
	ADC_RES = 0;
	ADC_CONTR |= ADC_POWER;	//打开ADC转化电源
	ADC_CONTR |= ADC_SPEED;	//设置AD转换速率 540个时钟转换一次
	ADC_CONTR |= ADC_START;	//AD开始转换
	Delay(2);
}

void adc_result() interrupt 5
{
	ADC_CONTR &= !ADC_FLAG;//清零标志位
	ADValue[chFlag] = ADC_RES*50/256; //计算得到采集回的电压值的10倍数据

	chFlag = (chFlag+1)%2;
	ADC_CONTR = ADC_POWER | ADC_SPEED | ADC_START | ch[chFlag];//第二轮转换
}
