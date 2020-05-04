#include "action.h"

uint target_pwm_duty[3]= {1500,1500,1500}; //??pwm
static uint cos_pwm[180];//?????????pwm
void Init_cos_pwm();

void steering_init()//�����ʼ��
{
    Init_cos_pwm();
}

void Init_cos_pwm()//��������Ƕȶ�Ӧ��PWM��ֵ
{
    int i;
    for( i = 1 ; i<181 ; i++ )
        cos_pwm[i-1] = (500+i*11.11);
}


void Change_angle(float x,float z) //���㲢���¶���Ƕ�
{
    if( z >= 0 )
    {
        float arm_long=sqrt(x*x+z*z);//?????

        //���������Ǹ��Ե�����ֵ
        float cosa = x/arm_long;
        float cosb = (105*105+arm_long*arm_long-145*145)/2/105/arm_long;
        float cosc = (145*145+arm_long*arm_long-105*105)/2/145/arm_long;

        //����Ƕ�
        int angle_a = (int)(acos(cosa)*180/3.14);
        int angle_b = (int)(acos(cosb)*180/3.14);
        int angle_c = (int)(acos(cosc)*180/3.14);

        target_pwm_duty[0] = cos_pwm[45+ (angle_a - angle_c)];//��Ϊ������
        target_pwm_duty[1] = cos_pwm[90 - (angle_b + angle_c)];
        target_pwm_duty[2] = cos_pwm[180- angle_a - angle_b ] ;

        steering_pwm_change();
    }
    else
    {
        float arm_long=sqrt(x*x+z*z);

        //���������Ǹ��Ե�����ֵ
        float cosa = x/arm_long;
        float cosb = (arm_long*arm_long+145*145-180*180)/2/145/arm_long;
        float cosc = (145*145+180*180-arm_long*arm_long)/2/145/180;

        //����Ƕ�
        int angle_a = (int)(acos(cosa)*180/3.14);
        int angle_b = (int)(acos(cosb)*180/3.14);
        int angle_c = (int)(acos(cosc)*180/3.14);

        target_pwm_duty[0] = cos_pwm[ angle_c - 90 ];
        target_pwm_duty[1] = cos_pwm[90 + (angle_b - angle_a)];

        pwm_change(2,target_pwm_duty[0]);
        pwm_change(3,target_pwm_duty[1]);
        pwm_change(4,2500);
        updata_TimingLeft();
    }
}
void steering_pwm_change(void)	 //���PWM�ĸ���
{
    pwm_change(2,target_pwm_duty[0]);
    pwm_change(3,target_pwm_duty[1]);
    pwm_change(4,target_pwm_duty[2]);
    updata_TimingLeft();	//����PWMʣ��ĵ͵�ƽʱ��
}
