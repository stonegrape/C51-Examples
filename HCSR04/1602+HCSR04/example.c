#include <STC12C5A.h>
#include <1602.h>
#include <HCSR04.h>

#define uchar unsigned char
#define uint unsigned int

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	LCD_Init();
	LCD_Clear();	
    while(1)
    {
		HCSR04_GetDistance();
		LCD_Clear();
		LCD_Write_String(0,0,"distance:");
		LCD_Write_Char(4,1,distance);
		delay(50);
    }
}