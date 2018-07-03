#ifndef _UART_H_
#define _UART_H_

unsigned char UART_data=0x00;

void UART_Init(void)   //9600bps@11.0592MHz
{
	PCON &= 0x7f;      //波特率不倍速
	SCON = 0x50;       //8位数据,可变波特率
	BRT = 0xDC;		   //设定独立波特率发生器重装值
	AUXR |= 0x15;      //串口1使用独立波特率发生器，不分频
	EA = 1;
	ES = 1;
}
					
void UART_Char(unsigned char c){
	SBUF=c;
	while(!TI);
	TI=0;
}

void UART_String(unsigned char *c){
	while(*c != '\0'){
		UART_Char(*c++);
	}
}

unsigned char UART_GetData(){
	return UART_data;
}

void UART_Interrupt (void) interrupt 4{
	if(RI){
		ES=0;
		RI=0;
		UART_data=SBUF;
		ES=1;
	}
}

#endif