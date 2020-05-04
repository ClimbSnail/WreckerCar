#include "adc.h"
#include "oled.h"

uint ADValue[2];

#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADCת����־λ
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEED   0x60            //540

uchar chFlag = 0;
uchar ch[2]={6,7};	//ѡ��P1.6��P1.7��ΪA/D�������

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
	EA = 1;		//�������ж�
	EADC = 1;	//����A/Dת��
	P1ASF = 0xC0;	//����P1.7/P1.6Ϊģ�⹦��
	ADC_RES = 0;
	ADC_CONTR |= ADC_POWER;	//��ADCת����Դ
	ADC_CONTR |= ADC_SPEED;	//����ADת������ 540��ʱ��ת��һ��
	ADC_CONTR |= ADC_START;	//AD��ʼת��
	Delay(2);
}

void adc_result() interrupt 5
{
	ADC_CONTR &= !ADC_FLAG;//�����־λ
	ADValue[chFlag] = ADC_RES*50/256; //����õ��ɼ��صĵ�ѹֵ��10������

	chFlag = (chFlag+1)%2;
	ADC_CONTR = ADC_POWER | ADC_SPEED | ADC_START | ch[chFlag];//�ڶ���ת��
}
