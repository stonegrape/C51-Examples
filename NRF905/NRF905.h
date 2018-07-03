#ifndef _NRF905_H_
#define _NRF905_H_

//---------------------------------------NRF905 数据交换端口------------------------------------------------
sbit	NRF905_TXEN=P3^3;
sbit	NRF905_TRX_CE=P2^4;
sbit	NRF905_MISO=P2^2;
sbit	NRF905_MOSI=P3^7;														 	
sbit	NRF905_SCK=P2^1;
sbit	NRF905_CSN=P2^0;

sbit	NRF905_PWR=P3^4;
sbit	NRF905_AM=P2^3;
sbit	NRF905_DR=P3^6;
sbit	NRF905_CD=P3^5;
//----------------------------------------------------------------------------------------------------------
#define NRF905_BYTE_BIT0	0x01
#define NRF905_BYTE_BIT1	0x02
#define NRF905_BYTE_BIT2	0x04
#define NRF905_BYTE_BIT3	0x08
#define NRF905_BYTE_BIT4	0x10
#define NRF905_BYTE_BIT5	0x20
#define NRF905_BYTE_BIT6	0x40
#define NRF905_BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------
bdata unsigned  char NRF905_DATA_BUF;
#define NRF905_DATA7	((NRF905_DATA_BUF&NRF905_BYTE_BIT7) != 0)
#define NRF905_DATA0    ((NRF905_DATA_BUF&NRF905_BYTE_BIT0) != 0)
sbit	NRF905_flag   	= NRF905_DATA_BUF^7;
sbit	NRF905_flag1	= NRF905_DATA_BUF^0;
//-------------------------------------------nrf905控制指令-------------------------------------------------
#define NRF905_WC		0x00
#define NRF905_RC		0x10
#define NRF905_WTP		0x20
#define NRF905_RTP		0x21
#define NRF905_WTA		0x22
#define NRF905_RTA		0x23
#define NRF905_RRP		0x24
//------------------------------------------------NRF905寄存器配置------------------------------------------
unsigned char idata NRF905_RFConf[11]=
{
  0x00,                             //配置命令
  0x4c,                             //CH_NO,配置频段在430MHZ
  0x0c,                             //输出功率为10db,不重发，节电为正常模式
  0x44,                             //地址宽度设置，为4字节
  0x04,0x04,                        //接收发送有效数据长度为32字节
  0x11,0x22,0x33,0x44,              //接收地址
  0x58,                             //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
};
code NRF905_TxAddress[4]={0x11,0x22,0x33,0x44};
unsigned char NRF905_data[4]={0x00,0x00,0x00,0x00};
//------------------------------------------------延时-------------------------------------------------------
static void NRF905_Delay(unsigned char n)
{
	unsigned int i;
	while(n--)
	for(i=0;i<80;i++);
}
//-------------------------------------------------SPI写函数--------------------------------------------------
void NRF905_SpiWrite(unsigned char send)
{
	unsigned char i;
	NRF905_DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (NRF905_DATA7)	
		{
			NRF905_MOSI=1;
		}
		else
		{
			NRF905_MOSI=0;
		}
		NRF905_SCK=1;
		NRF905_DATA_BUF=NRF905_DATA_BUF<<1;
		NRF905_SCK=0;
	}
}
//---------------------------------------------------SPI读函数-----------------------------------------------------
unsigned char NRF905_SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
    NRF905_DATA_BUF=NRF905_DATA_BUF<<1;
		NRF905_SCK=1;
		if (NRF905_MISO)	
		{
			NRF905_DATA_BUF|=NRF905_BYTE_BIT0;
		}
		else
		{
			NRF905_DATA_BUF&=~NRF905_BYTE_BIT0;
		}
		NRF905_SCK=0;
	 }
	 return NRF905_DATA_BUF;
}
//------------------------------------------------------初始化nRF905-------------------------------------------
void NRF905_Init(void)
{
	unsigned char i;
  NRF905_CSN=1;						
	NRF905_SCK=0;						
	NRF905_DR=0;						
	NRF905_AM=0;						
	NRF905_CD=0;						
	NRF905_PWR=1;					
	NRF905_TRX_CE=0;					
	NRF905_TXEN=0;	
	NRF905_Delay(1);
	NRF905_CSN=0;									
	for (i=0;i<11;i++)	
	{
	  NRF905_SpiWrite(NRF905_RFConf[i]);
	}
	NRF905_CSN=1;
}
//-----------------------------------------------------发送数据打包----------------------------------------------
void NRF905_Tx(unsigned char Buf0,unsigned char Buf1,unsigned char Buf2,unsigned char Buf3)
{
	unsigned char i;
	unsigned char NRF905_TxBuf[4]={0x08,0x08,0x08,0x08};
	NRF905_TxBuf[0]=Buf0;
	NRF905_TxBuf[1]=Buf1;
	NRF905_TxBuf[2]=Buf2;
	NRF905_TxBuf[3]=Buf3;
	NRF905_TRX_CE=0;
	NRF905_TXEN=1;
	NRF905_Delay(1); 
	NRF905_CSN=0;
	NRF905_SpiWrite(NRF905_WTP);
	for (i=0;i<4;i++)
	{
		NRF905_SpiWrite(NRF905_TxBuf[i]);		
	}
	NRF905_CSN=1;
	NRF905_Delay(1);						
	NRF905_CSN=0;						
	NRF905_SpiWrite(NRF905_WTA);				
	for (i=0;i<4;i++)			
	{
		NRF905_SpiWrite(NRF905_TxAddress[i]);
	}
	NRF905_CSN=1;						
	NRF905_TRX_CE=1;					
	NRF905_Delay(1);					
	NRF905_TRX_CE=0;					
}
//----------------------------------------------------读NRF905接收数据-------------------------------------------------
void NRF905_Rx(void)						
{
	unsigned char i;
  NRF905_Delay(1);
	NRF905_TXEN=0;
	NRF905_TRX_CE=1;
  NRF905_Delay(100);
  NRF905_TRX_CE=0;
	NRF905_CSN=0;						
  NRF905_Delay(1);
	NRF905_SpiWrite(NRF905_RRP);
	for (i = 0 ;i < 4 ;i++)
	{ 
		NRF905_data[i]=NRF905_SpiRead();		    
	}
	NRF905_CSN=1;
  NRF905_Delay(10);
	NRF905_TRX_CE=1;							
}

#endif