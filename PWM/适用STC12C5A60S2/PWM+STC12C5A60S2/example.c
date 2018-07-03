#include <STC12C5A.h>
#include <PWM.h>

#define uchar unsigned char
#define uint unsigned int

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	PWM_Init();
	PWM_Set(0,0x40);
	PWM_Set(1,0x80);
	while(1);
}