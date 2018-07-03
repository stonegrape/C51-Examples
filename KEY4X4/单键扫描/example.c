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
		KEY4X4_scan();
		switch(KEY4X4){
			case 0x11:{
				LED=0;
				delay(1000);
				delay(1000);
				delay(1000);
				delay(1000);
				break;
			}
			case 0x22:{
				LED=0;
				delay(1000);
				delay(1000);
				delay(1000);
				delay(1000);
				break;
			}
			case 0x33:{
				LED=0;
				delay(1000);
				delay(1000);
				delay(1000);
				delay(1000);
				break;
			}
			case 0x44:{
				LED=0;
				delay(1000);
				delay(1000);
				delay(1000);
				delay(1000);
				break;
			}
			default:{
				LED=1;
				break;
			}
		}
	}
}