#include <STC12C5A.h>
#include <UART.h>

#define uchar unsigned char
#define uint unsigned int

sbit key = P1^0;

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main(){
	uchar i=0;
	UART_Init();
	while(1){
		if(key==0){
			delay(10);
			if(key==0){
				if(i==0){
					i=1;
				}else{
					i=0;
				}
				while(key==0);
				switch(i){
					case 0:
						UART_String("19");
						break;
					case 1:
						UART_String("222");
						break;
					default:
						break;
				}
			}
		}
		delay(100);
	}
}