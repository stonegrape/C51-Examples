#ifndef _DS1302_H_
#define _DS1302_H_

unsigned char DS1302_miao=0,DS1302_shi=0,DS1302_fen=0,DS1302_ri=1,DS1302_yue=1,DS1302_nian=0,DS1302_week=1;

sbit DS1302_SCLK=P1^0; 
sbit DS1302_IO=P1^1;   
sbit DS1302_RST=P1^2;   
sbit ACC0=ACC^0;
sbit ACC7=ACC^7;

/********************ds1302****************************/
void DS1302_write_byte(unsigned char dat)
{
	unsigned char a;
	ACC=dat;
	DS1302_RST=1;
	for(a=8;a>0;a--)
	{
		DS1302_IO=ACC0;
		DS1302_SCLK=0;
		DS1302_SCLK=1;
		ACC=ACC>>1;
	}
}
unsigned char DS1302_read_byte()
{
	unsigned char a;
	DS1302_RST=1;
	for(a=8;a>0;a--)
	{
		ACC7=DS1302_IO;
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		ACC=ACC>>1;

	}
	return (ACC);
}
void DS1302_write_1302(unsigned char add,unsigned char dat)
{

	DS1302_RST=0;
	DS1302_SCLK=0;
	DS1302_RST=1;
	DS1302_write_byte(add);
	DS1302_write_byte(dat);
	DS1302_SCLK=1;
	DS1302_RST=0;
}
unsigned char DS1302_read_1302(unsigned char add)
{
	unsigned char temp;
	DS1302_RST=0;
	DS1302_SCLK=0;
	DS1302_RST=1;
	DS1302_write_byte(add);
	temp=DS1302_read_byte();
	DS1302_SCLK=1;
	DS1302_RST=0;
	return(temp);
}


unsigned char DS1302_BCD_Decimal(unsigned char bcd)
{
 unsigned char Decimal;
 Decimal=bcd>>4;
 return(Decimal=Decimal*10+(bcd&=0x0F));
}

unsigned char DS1302_Decimal_BCD(unsigned char Decimal)
{
 unsigned char bcd;
 bcd=Decimal/10;
 bcd=bcd<<4;
 Decimal=Decimal%10;
 Decimal=(bcd&=0xF0)+(Decimal&=0x0F);
 return(Decimal);
} 

void DS1302_GetTime()
{
	DS1302_miao = DS1302_BCD_Decimal(DS1302_read_1302(0x81));
	DS1302_fen  = DS1302_BCD_Decimal(DS1302_read_1302(0x83));
	DS1302_shi  = DS1302_BCD_Decimal(DS1302_read_1302(0x85));
	DS1302_ri   = DS1302_BCD_Decimal(DS1302_read_1302(0x87));
	DS1302_yue  = DS1302_BCD_Decimal(DS1302_read_1302(0x89));
	DS1302_nian = DS1302_BCD_Decimal(DS1302_read_1302(0x8d));
	DS1302_week = DS1302_BCD_Decimal(DS1302_read_1302(0x8b));
}

void DS1302_SetTime(unsigned char nian,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao,unsigned char week)
{
	shi=DS1302_Decimal_BCD(shi);
	fen=DS1302_Decimal_BCD(fen);
	miao=DS1302_Decimal_BCD(miao);
	ri=DS1302_Decimal_BCD(ri);
	yue=DS1302_Decimal_BCD(yue);
	nian=DS1302_Decimal_BCD(nian);
	week=DS1302_Decimal_BCD(week);
	DS1302_write_1302(0x84,shi);
	DS1302_write_1302(0x82,fen);
	DS1302_write_1302(0x80,miao);
	DS1302_write_1302(0x86,ri);
	DS1302_write_1302(0x88,yue);
	DS1302_write_1302(0x8c,nian);
	DS1302_write_1302(0x8a,week);
}

void DS1302_Init()
{
	DS1302_GetTime();
	DS1302_RST=0;
	DS1302_SCLK=0;
	DS1302_write_1302(0x80,0x00);//ÔÊÐíÐ´
	DS1302_SetTime(DS1302_nian,DS1302_yue,DS1302_ri,DS1302_shi,DS1302_fen,DS1302_miao,DS1302_week);
}

#endif