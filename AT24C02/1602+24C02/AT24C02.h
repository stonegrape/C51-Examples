#ifndef _AT24C02_H_
#define _AT24C02_H_

#include <intrins.h>

sbit AT24C02_sda=P1^6;                          //IO口定义
sbit AT24C02_scl=P1^7;
				 
void AT24C02_nop()
{
	_nop_();
	_nop_();
}
/////////24C02读写驱动程序////////////////////
void AT24C02_delay1(unsigned int m)
{	unsigned int n;
  	for(n=0;n<m;n++);
}

void AT24C02_Init()  //24c02初始化子程序
{
	AT24C02_scl=1;
	AT24C02_nop();
	AT24C02_sda=1;
	AT24C02_nop();
}

void AT24C02_start()        //启动I2C总线
{
	AT24C02_sda=1;
	AT24C02_nop();
	AT24C02_scl=1;
	AT24C02_nop();
	AT24C02_sda=0;
	AT24C02_nop();
	AT24C02_scl=0;
	AT24C02_nop();
}

void AT24C02_stop()         //停止I2C总线
{
	AT24C02_sda=0;
	AT24C02_nop();
	AT24C02_scl=1;
	AT24C02_nop();
	AT24C02_sda=1;
	AT24C02_nop();
}

void AT24C02_writebyte(unsigned char j)  //写一个字节
{
	unsigned char i,temp;
   	temp=j;
   	for (i=0;i<8;i++)
   {
	   temp=temp<<1;
	   AT24C02_scl=0;
	   AT24C02_nop();
	   AT24C02_sda=CY;		//temp左移时，移出的值放入了CY中
	   AT24C02_nop();
	   AT24C02_scl=1;		//待sda线上的数据稳定后，将scl拉高
	   AT24C02_nop();
   }
   AT24C02_scl=0;
   AT24C02_nop();
   AT24C02_sda=1;
   AT24C02_nop();
}

unsigned char AT24C02_readbyte()   //读一个字节
{
   unsigned char i,j,k=0;
   AT24C02_scl=0; 
   AT24C02_nop(); 
   AT24C02_sda=1;
   for (i=0;i<8;i++)
   {  
		AT24C02_nop();
		AT24C02_scl=1;
		AT24C02_nop();
      	if(AT24C02_sda==1) 
		j=1;
      	else
		j=0;
      	k=(k<<1)|j;
	  	AT24C02_scl=0;
	}
   	AT24C02_nop();
	return(k);
}

void AT24C02_clock()         //I2C总线时钟
{
   unsigned char i=0;
   AT24C02_scl=1;
   AT24C02_nop();
   while((AT24C02_sda==1)&&(i<255))
   	  i++;
   AT24C02_scl=0;
   AT24C02_nop();
}

////////从24c02的地址address中读取一个字节数据/////
unsigned char AT24C02_Read(unsigned char address)
{
   unsigned char i;
   AT24C02_start();
   AT24C02_writebyte(0xa0);
   AT24C02_clock();
   AT24C02_writebyte(address);
   AT24C02_clock();
   AT24C02_start();
   AT24C02_writebyte(0xa1);
   AT24C02_clock();
   i=AT24C02_readbyte();
   AT24C02_stop();
   AT24C02_delay1(100);
   return(i);
}

//////向24c02的address地址中写入一字节数据info/////
void AT24C02_Write(unsigned char address,unsigned char info)
{
   AT24C02_start();
   AT24C02_writebyte(0xa0);
   AT24C02_clock();
   AT24C02_writebyte(address);
   AT24C02_clock();
   AT24C02_writebyte(info);
   AT24C02_clock();
   AT24C02_stop();
   AT24C02_delay1(5000); //这个延时一定要足够长，否则会出错。因为24c02在从sda上取得数据后，还需要一定时间的烧录过程。
}

#endif