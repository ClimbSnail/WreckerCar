#include "external.h"

static char ext0,ext1;   //�жϵı�־λ

void exint0(void) interrupt 0  //�ⲿ�ж�0���жϷ������
{
    ext0 = 1;
}

void ext0_init()		//�ⲿ�ж�0�ĳ�ʼ��
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    ext0 = 0;
}

char get_ext0()		  //��ѯ�Ƿ�����ж�
{
    char temp = ext0;
    ext0 = 0;
    return temp;	//���ز�ѯ��ֵ
}

void exint1(void) interrupt 2  //�ⲿ�ж�0���жϷ������
{
    ext1 = 1;
}

void ext1_init()		//�ⲿ�ж�0�ĳ�ʼ��
{
    IT1 = 1;
    EX1 = 1;
    EA = 1;
    ext1 = 0;
}

char get_ext1()		  //��ѯ�Ƿ�����ж�
{
    char temp = ext1;
    ext1 = 0;
    return temp;	//���ز�ѯ��ֵ
}

