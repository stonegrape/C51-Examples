#ifndef _12864_H_
#define _12864_H_

#include <intrins.h>

#define LCD12864_data  P0             //数据口
sbit LCD12864_RS  =  P2^5;            //寄存器选择输入 
sbit LCD12864_RW  =  P2^6;            //液晶读/写控制
sbit LCD12864_EN  =  P2^7;            //液晶使能控制

void LCD12864_delayNOP()
{
	nop_();_nop_();_nop_();_nop_();
}

void LCD12864_delay(int ms)
{
    while(ms--)
	{
      unsigned char i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
	   }
	}
}		

bit LCD12864_busy()
 {                          
    bit result;
    LCD12864_RS = 0;
    LCD12864_RW = 1;
    LCD12864_EN = 1;
    LCD12864_delayNOP();
    result = (bit)(P0&0x80);
    LCD12864_EN = 0;
    return(result); 
 }

void LCD12864_wcmd(unsigned char cmd)
{                          
   while(LCD12864_busy());
    LCD12864_RS = 0;
    LCD12864_RW = 0;
    LCD12864_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    LCD12864_delayNOP();
    LCD12864_EN = 1;
    LCD12864_delayNOP();
    LCD12864_EN = 0;  
}

void LCD12864_Settle(unsigned char X,unsigned char Y)
{                          
   unsigned char pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;
   LCD12864_wcmd(pos);     //显示地址
}

void LCD12864_Write_Char(unsigned char dat)
{                    
	while(LCD12864_busy());
    LCD12864_RS = 1;
    LCD12864_RW = 0;
    LCD12864_EN = 0;
    P0 = dat;
    LCD12864_delayNOP();
    LCD12864_EN = 1;
    LCD12864_delayNOP();
    LCD12864_EN = 0; 
}

void LCD12864_String(unsigned char X,unsigned char Y,unsigned char *str){
	LCD12864_Settle(X,Y);
	LCD12864_delay(1);
	while(*str){
		LCD12864_Write_Char(*str++);
		LCD12864_delay(1);
	}
}

void LCD12864_Clear_Draw()
{
    unsigned char j,k; 
	LCD12864_wcmd(0x34);         
	for(j = 0;j < 32;j++)
	{
        LCD12864_wcmd(0x80+j);
		LCD12864_delay(1);
        LCD12864_wcmd(0x80);
		LCD12864_delay(1);
  		for(k = 0;k < 16;k++)
  		{
  		    LCD12864_Write_Char(0x00);
			LCD12864_delay(1);
  		}
	}
 	for(j = 0;j < 32;j++)
	{
 	    LCD12864_wcmd(0x80+j);
		LCD12864_delay(1);
        LCD12864_wcmd(0x88);
		LCD12864_delay(1);	   
  		for(k = 0;k < 16;k++)
  		{
   		    LCD12864_Write_Char(0x00);
			LCD12864_delay(1);
   		} 
	}  
    LCD12864_wcmd(0x36);        
	LCD12864_delay(1);
	LCD12864_wcmd(0x30);      
	LCD12864_delay(1);       
}

void LCD12864_Draw(unsigned char *dat){ 
	unsigned char j,k; 
	LCD12864_wcmd(0x34);
	LCD12864_delay(1);         
	for(j = 0;j < 32;j++)
	{
        LCD12864_wcmd(0x80+j);
		LCD12864_delay(1);
        LCD12864_wcmd(0x80);
		LCD12864_delay(1);
  		for(k = 0;k < 16;k++)
  		{
  		    LCD12864_Write_Char(*dat++);
			LCD12864_delay(1);
  		}
	}
 	for(j = 0;j < 32;j++)
	{
 	    LCD12864_wcmd(0x80+j);
		LCD12864_delay(1);
        LCD12864_wcmd(0x88);
		LCD12864_delay(1);	   
  		for(k = 0;k < 16;k++)
  		{
   		    LCD12864_Write_Char(*dat++);
			LCD12864_delay(1);
   		} 
	}  
    LCD12864_wcmd(0x36);        
	LCD12864_delay(1);
	LCD12864_wcmd(0x30);      
	LCD12864_delay(1);
}

void LCD12864_Char(unsigned char X,unsigned char Y,unsigned char dat1,unsigned char dat2){
	LCD12864_wcmd(0x34);
	LCD12864_delay(1);	
	if(Y<32){
		LCD12864_wcmd(0x80+Y);
		LCD12864_delay(1);
   	 	LCD12864_wcmd(0x80+X);
		LCD12864_delay(1);	
	}else{
		LCD12864_wcmd(0x80+Y-32);
		LCD12864_delay(1);
		LCD12864_wcmd(0x88+X);
		LCD12864_delay(1);
	}
	LCD12864_Write_Char(dat1);
	LCD12864_delay(1);
	LCD12864_Write_Char(dat2);
	LCD12864_delay(1);
	LCD12864_wcmd(0x36);        
	LCD12864_delay(1);
	LCD12864_wcmd(0x30);      
	LCD12864_delay(1);
}

void LCD12864_Clear(){
	LCD12864_wcmd(0x01);      //清除LCD的显示内容
	LCD12864_delay(5);
	LCD12864_Clear_Draw();
	LCD12864_delay(5);
	LCD12864_wcmd(0x30);
	LCD12864_delay(5);
	LCD12864_wcmd(0x02);
	LCD12864_delay(5);	 
}

void LCD12864_Init()
{ 
    LCD12864_wcmd(0x34);      //扩充指令操作
    LCD12864_delay(5);
    LCD12864_wcmd(0x30);      //基本指令操作
    LCD12864_delay(5);
    LCD12864_wcmd(0x0C);      //显示开，关光标
    LCD12864_delay(5);
	LCD12864_Clear();
}

#endif