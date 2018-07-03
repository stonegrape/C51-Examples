#include <STC12C5A.h>
#include <1602.h>
#include <DS1302.h>

#define uchar unsigned char
#define uint unsigned int
//sbit key = P2^4;

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	LCD_Init();
	LCD_Clear();
	DS1302_Init();
	DS1302_SetTime(12,2,29,23,59,0,4);
    while(1)
    {
	//	if(key==0){
	//		delay(10);
	//		if(key==0){
				LCD_Clear();
				DS1302_GetTime();
				LCD_Write_String(0,0,"time:20  -  -  ");
				LCD_Write_String(3,1,"  :  :");
				LCD_Write_Char(7,0,DS1302_nian);
				LCD_Write_Char(10,0,DS1302_yue);
				LCD_Write_Char(13,0,DS1302_ri);
				LCD_Write_Char(3,1,DS1302_shi);
				LCD_Write_Char(6,1,DS1302_fen);
				LCD_Write_Char(9,1,DS1302_miao);
				delay(50);
	//		}
	//	}
    }
}