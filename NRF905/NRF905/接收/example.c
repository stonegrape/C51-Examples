#include <STC12C5A.h>
#include <NRF905.h>

#define uchar unsigned char
#define uint unsigned int

sbit LED=P1^0;

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main(){
	LED=1;
	NRF905_Init();
	while(1){
		NRF905_data[0]=0x00;
		NRF905_Rx();
		if(NRF905_data[0]==0x11){
			LED=0;
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			LED=1;
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
		}
		
	}
}