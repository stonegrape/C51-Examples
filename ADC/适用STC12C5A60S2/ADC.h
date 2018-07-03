#ifndef _ADC_H_
#define _ADC_H_

#include <intrins.h>

#define ADC_POWER 0X80  //ADC最高位给adc部分供电，类似于片选
#define ADC_START 0X08  //模数转换启动控制位
#define ADC_FLAG  0x10  //ad转换需要时间，这个是转换完成标志位
#define ADC_SPEEDLL 0X00   //540 clock
#define ADC_SPEEDL  0X20   //360 clock
#define ADC_SPEEDH 0X40   //180 clock
#define ADC_SPEEDHH 0X60   //90  clock

#define VCC 5                   //可根据最高电压手动调整满值电压
#define ADC_SPEED ADC_SPEEDLL   //可根据所需的采样频率手动调整AD转换速度

unsigned int ADC_value=0;

void ADC_Get(unsigned char road)
{
	switch(road){
		case 0x00:{
			P1ASF=0x01;
			break;
		}
		case 0x01:{
			P1ASF=0x02;
			break;
		}
		case 0x02:{
			P1ASF=0x04;
			break;
		}
		case 0x03:{
			P1ASF=0x08;
			break;
		}
		case 0x04:{
			P1ASF=0x10;
			break;
		}
		case 0x05:{
			P1ASF=0x20;
			break;
		}
		case 0x06:{
			P1ASF=0x40;
			break;
		}
		case 0x07:{
			P1ASF=0x80;
			break;
		}
		default:{
			P1ASF=0x00;
			break;
		}
	}
	ADC_RES=0x00;
	ADC_RESL=0x00;
	AUXR1 |= 0x04;
	ADC_CONTR=ADC_POWER|ADC_SPEED|ADC_START|road;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & ADC_FLAG));   
	ADC_CONTR = 0x00; 
	ADC_value=(ADC_RES<<8)+ADC_RESL;
    ADC_value=(float)(ADC_value)*5*1000/1024;
}

#endif