#ifndef _HCSR04_H_
#define _HCSR04_H_

#define speed 3453

sbit HCSR04_INPUT  = P1^3;                //回声接收端口Echo
sbit HCSR04_OUTPUT = P1^4;                //超声触发端口Trig

long int distance=0;               
unsigned char HCSR04_count;
	
void HCSR04_delayt(unsigned int x)
{
    unsigned char j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 125;j++)
        {
            ;
        }
    }
}

void HCSR04_Init(void)
{
	TMOD = 0x01;	  //定时器0初始化,设置为16位自动重装模式
 	TL0 = 0x66;
	TH0 = 0xfc;	      //1ms
    ET0 = 1;	      //开定时器0
	EA = 1;		      //总中断使能
	HCSR04_OUTPUT =1;
	HCSR04_INPUT = 1;
	HCSR04_count = 0;
	distance = 0;
}
					
void HCSR04_GetDistance(void)
{
	unsigned char l;
	unsigned int h,y;
	HCSR04_Init();
	HCSR04_OUTPUT = 1;
	HCSR04_delayt(1);
	HCSR04_OUTPUT = 0;         //触发超声波发射
	while(HCSR04_INPUT == 0);          //等待回声
	TR0 = 1;
	while(HCSR04_INPUT);	
	TR0 = 0;
	l = TL0;
	h = TH0;
	y = (h << 8) + l;
	y = y - 0xfc66;//us部分
	distance = y + 1000 * HCSR04_count;//计算总时间
	TL0 = 0x66;
	TH0 = 0xfc;
	HCSR04_delayt(30);
	distance = speed * distance / 20000;        //计算脉宽并转换为距离
	HCSR04_delayt(100);               //延时，两次发射之间要至少有10ms间隔
}
/******************************************************************************/
/* 函数名称  : timer0                                                         */
/* 函数描述  : T0中断处理函数                                                 */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void HCSR04_timer0 (void) interrupt 1
{
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xfc;
	HCSR04_count++;
	if(HCSR04_count == 18)//超声波回声脉宽最多18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		HCSR04_count = 0;
	}
}
/******************************************************************************/

#endif