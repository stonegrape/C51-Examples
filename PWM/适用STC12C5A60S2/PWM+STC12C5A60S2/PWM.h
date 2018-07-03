#ifndef _PWM_H_
#define _PWM_H_

void PWM_Init()
{
	CCON = 0;					 	//��ʼ��PCA���ƼĴ���,PCA��ʱ���رգ���CF��־�����жϱ�־
	CL = 0;							//��λ PCA base timer
	CH = 0;
	CMOD = 0X00;			 		//PCAʱ��Դ��FOSC/12,�ر�PCA��ʱ������ж�

	CCAP0H = CCAP0L = 0X20;			//����PWM0���ռ�ձȵķ���		����0x80��ʱ��ռ�ձ�50%	����ԽС��Ӧת��Խ��
	CCAPM0 = 0X42;				  	//����PCA������ʽΪPWM��ʽ(0100 0010)	8λPWMģʽ����PCA�ж�

	CCAP1H = CCAP1L =0XA0;
	CCAPM1 = 0X42;

	CR = 1;						  	//ʹ��PCA��ʱ��
	//P3 = 0;
}
/********************************************************/
void PWM_Set(bit flg,unsigned char speed)
{
	speed=255-speed;
	if(flg == 0)
	{
		CCAP0H = speed;
		CCAP0L = speed;
	}
	else
	{
		CCAP1H = speed;
		CCAP1L = speed;
	}
}

#endif