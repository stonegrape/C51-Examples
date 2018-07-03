#ifndef _PWM_H_
#define _PWM_H_

void PWM_Init()
{
	CCON = 0;					 	//初始化PCA控制寄存器,PCA定时器关闭，清CF标志，清中断标志
	CL = 0;							//复位 PCA base timer
	CH = 0;
	CMOD = 0X00;			 		//PCA时钟源：FOSC/12,关闭PCA定时器溢出中断

	CCAP0H = CCAP0L = 0X20;			//设置PWM0输出占空比的方波		等于0x80的时候占空比50%	数字越小对应转速越快
	CCAPM0 = 0X42;				  	//设置PCA工作方式为PWM方式(0100 0010)	8位PWM模式，无PCA中断

	CCAP1H = CCAP1L =0XA0;
	CCAPM1 = 0X42;

	CR = 1;						  	//使能PCA定时器
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