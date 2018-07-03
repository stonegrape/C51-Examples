#include <STC12C5A.h>
#include <1602.h>

#define uchar unsigned char
#define uint unsigned int

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	uchar k=234;
	LCD_Init();
	LCD_Clear();		
	LCD_Write_String(0,0,"Data is:");
	LCD_Write_String(8,0,"aa");
	LCD_Write_Char(7,1,k);
	LCD_Write_String(10,1,"aa");
	LCD_Write_Char(0,1,k);
	LCD_Write_String(12,0,"aa");
	LCD_Write_String(14,0,"aa");
	LCD_Write_Char(4,1,k);
	while(1);
}