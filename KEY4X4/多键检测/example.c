#include <STC12C5A.h>
#include <KEY4X4.h>

#define uchar unsigned char
#define uint unsigned int

sbit LED=P2^0;

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	while(1){
		LED=1;
		KEY4X4_many();
		if(KEY1_3==1){
			LED=0;
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			LED=1;
		}
		if((KEY1_1==1)&&(KEY1_2==1)&&(KEY2_2==1)){
			LED=0;
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			LED=1;
		}
		if((KEY3_1==1)&&(KEY4_2==1)&&(KEY3_3==1)){
			LED=0;
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			LED=1;
		}
		delay(20);
	}
}