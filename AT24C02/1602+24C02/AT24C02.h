#ifndef _AT24C02_H_
#define _AT24C02_H_

#include <intrins.h>

sbit AT24C02_sda=P1^6;                          //IO�ڶ���
sbit AT24C02_scl=P1^7;
				 
void AT24C02_nop()
{
	_nop_();
	_nop_();
}
/////////24C02��д��������////////////////////
void AT24C02_delay1(unsigned int m)
{	unsigned int n;
  	for(n=0;n<m;n++);
}

void AT24C02_Init()  //24c02��ʼ���ӳ���
{
	AT24C02_scl=1;
	AT24C02_nop();
	AT24C02_sda=1;
	AT24C02_nop();
}

void AT24C02_start()        //����I2C����
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

void AT24C02_stop()         //ֹͣI2C����
{
	AT24C02_sda=0;
	AT24C02_nop();
	AT24C02_scl=1;
	AT24C02_nop();
	AT24C02_sda=1;
	AT24C02_nop();
}

void AT24C02_writebyte(unsigned char j)  //дһ���ֽ�
{
	unsigned char i,temp;
   	temp=j;
   	for (i=0;i<8;i++)
   {
	   temp=temp<<1;
	   AT24C02_scl=0;
	   AT24C02_nop();
	   AT24C02_sda=CY;		//temp����ʱ���Ƴ���ֵ������CY��
	   AT24C02_nop();
	   AT24C02_scl=1;		//��sda���ϵ������ȶ��󣬽�scl����
	   AT24C02_nop();
   }
   AT24C02_scl=0;
   AT24C02_nop();
   AT24C02_sda=1;
   AT24C02_nop();
}

unsigned char AT24C02_readbyte()   //��һ���ֽ�
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

void AT24C02_clock()         //I2C����ʱ��
{
   unsigned char i=0;
   AT24C02_scl=1;
   AT24C02_nop();
   while((AT24C02_sda==1)&&(i<255))
   	  i++;
   AT24C02_scl=0;
   AT24C02_nop();
}

////////��24c02�ĵ�ַaddress�ж�ȡһ���ֽ�����/////
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

//////��24c02��address��ַ��д��һ�ֽ�����info/////
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
   AT24C02_delay1(5000); //�����ʱһ��Ҫ�㹻��������������Ϊ24c02�ڴ�sda��ȡ�����ݺ󣬻���Ҫһ��ʱ�����¼���̡�
}

#endif