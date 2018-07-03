#include <STC12C5A.h>
#include <1602.h>
#include <AT24C02.h>

#define uchar unsigned char
#define uint unsigned int

char code music[] = {
55,66,77,88,0x55,0x66,0x77,0x88
};

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	LCD_Init();
	LCD_Clear();
	AT24C02_Init();
    while(1)
    {
		uchar add=0,k=0;
		LCD_Clear();
		LCD_Write_String(0,0,"Data is:");
		while(add!=sizeof(music)){
			AT24C02_Write(add+0x00,music[add]);
			add++;
		}
		add=0;
		while(add!=sizeof(music)){
			k=AT24C02_Read(add);
			LCD_Write_Char(4,1,k);
			add++;
			delay(1000);
		}
    }
}