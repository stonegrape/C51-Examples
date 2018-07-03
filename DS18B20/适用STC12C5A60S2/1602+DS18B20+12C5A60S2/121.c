#include <STC12C5A.h>
#include <1602.h>
#include <DS18B20.h>

#define uchar unsigned char
#define uint unsigned int

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
//	int a;
	LCD_Init();		
    while(1)
    {
//		a=-3;
		LCD_Clear();
		DS18B20_GetTmp();
		LCD_Write_String(0,0,"temperature:");
        LCD_Write_Char(4,1,temperature/10);
		LCD_Write_Char(7,1,temperature%10);
		LCD_Write_String(6,1,".");
		delay(1000);
    }
}