#ifndef _HCSR04_H_
#define _HCSR04_H_

#define speed 3453

sbit HCSR04_INPUT  = P1^3;                //�������ն˿�Echo
sbit HCSR04_OUTPUT = P1^4;                //���������˿�Trig

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
	TMOD = 0x01;	  //��ʱ��0��ʼ��,����Ϊ16λ�Զ���װģʽ
 	TL0 = 0x66;
	TH0 = 0xfc;	      //1ms
    ET0 = 1;	      //����ʱ��0
	EA = 1;		      //���ж�ʹ��
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
	HCSR04_OUTPUT = 0;         //��������������
	while(HCSR04_INPUT == 0);          //�ȴ�����
	TR0 = 1;
	while(HCSR04_INPUT);	
	TR0 = 0;
	l = TL0;
	h = TH0;
	y = (h << 8) + l;
	y = y - 0xfc66;//us����
	distance = y + 1000 * HCSR04_count;//������ʱ��
	TL0 = 0x66;
	TH0 = 0xfc;
	HCSR04_delayt(30);
	distance = speed * distance / 20000;        //��������ת��Ϊ����
	HCSR04_delayt(100);               //��ʱ�����η���֮��Ҫ������10ms���
}
/******************************************************************************/
/* ��������  : timer0                                                         */
/* ��������  : T0�жϴ�����                                                 */
/* �������  : ��                                                             */
/* ��������  : ��                                                             */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void HCSR04_timer0 (void) interrupt 1
{
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xfc;
	HCSR04_count++;
	if(HCSR04_count == 18)//�����������������18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		HCSR04_count = 0;
	}
}
/******************************************************************************/

#endif