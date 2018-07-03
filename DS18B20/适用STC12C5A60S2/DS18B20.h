#ifndef _DS18B20_H_
#define _DS18B20_H_

sbit DS18B20_DQ = P2^0;

void DS18B20_delay(unsigned int i)
{
while(i--);
}
 
void DS18B20_Init(void)
{
unsigned char x=0;
DS18B20_DQ = 1;          //DQ复位
DS18B20_delay(80); //稍做延时
DS18B20_DQ = 0;          //单片机将DQ拉低
DS18B20_delay(800); //精确延时 大于 480us
DS18B20_DQ = 1;          //拉高总线
DS18B20_delay(140);
x=DS18B20_DQ;  
DS18B20_delay(200);
}
 
unsigned char DS18B20_ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
{
    DS18B20_DQ = 0; // 给脉冲信号
    dat>>=1;
    DS18B20_DQ = 1; // 给脉冲信号
    if(DS18B20_DQ)
    dat|=0x80;
    DS18B20_delay(40);     //40
}
   return(dat);
}
 
void DS18B20_WriteOneChar(unsigned char dat)
{
   unsigned char i=0;
   for (i=8; i>0; i--)
   {
  DS18B20_DQ = 0;
    DS18B20_DQ = dat&0x01;
    DS18B20_delay(50); //50
    DS18B20_DQ = 1;
    dat>>=1;
}
}
 
int DS18B20_GetTmp(void)
{
unsigned char a=0;
unsigned char b=0;
int temp_value=0;
DS18B20_Init();
DS18B20_WriteOneChar(0xCC);    
DS18B20_WriteOneChar(0x44); 
DS18B20_delay(1000);     
DS18B20_Init();
DS18B20_WriteOneChar(0xCC); 
DS18B20_WriteOneChar(0xBE); 
DS18B20_delay(1000);
a=DS18B20_ReadOneChar();    //读取温度值低位
b=DS18B20_ReadOneChar();      //读取温度值高位
temp_value = b<<8;
temp_value |= a;

return temp_value*0.625;
}

#endif