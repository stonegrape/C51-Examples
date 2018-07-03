#ifndef _UART_H_
#define _UART_H_

unsigned char UART_data=0x00;

void UART_Init(void)   //9600bps@11.0592MHz
{
	PCON &= 0x7f;      //�����ʲ�����
	SCON = 0x50;       //8λ����,�ɱ䲨����
	BRT = 0xDC;		   //�趨���������ʷ�������װֵ
	AUXR |= 0x15;      //����1ʹ�ö��������ʷ�����������Ƶ
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