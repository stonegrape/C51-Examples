#include<intrins.h>
#include<stdlib.h>
sbit LCD_RS = P2^5;   //����˿� 
sbit LCD_RW = P2^6;
sbit LCD_E = P2^7;


#define LCD_RS_CLR LCD_RS=0 
#define LCD_RS_SET LCD_RS=1

#define LCD_RW_CLR LCD_RW=0 
#define LCD_RW_SET LCD_RW=1 

#define LCD_EN_CLR LCD_E=0
#define LCD_EN_SET LCD_E=1

#define LCD_DataPort P0

/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/
void LCD_DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void LCD_DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     LCD_DelayUs2x(245);
	 LCD_DelayUs2x(245);
 }
}

/*------------------------------------------------
              ��æ����
------------------------------------------------*/
 bit LCD_Check_Busy(void) 
 { 
 LCD_DataPort= 0xFF; 
 LCD_RS_CLR; 
 LCD_RW_SET; 
 LCD_EN_CLR; 
 _nop_(); 
 LCD_EN_SET;
 return (bit)(LCD_DataPort & 0x80);
 }
 
 /*------------------------------------------------
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
 while(LCD_Check_Busy()); //æ��ȴ�
 LCD_RS_CLR; 
 LCD_RW_CLR; 
 LCD_EN_SET; 
 LCD_DataPort= com; 
 _nop_(); 
 LCD_EN_CLR;
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
 while(LCD_Check_Busy()); //æ��ȴ�
 LCD_RS_SET; 
 LCD_RW_CLR; 
 LCD_EN_SET;
 LCD_DataPort= Data; 
 _nop_();
 LCD_EN_CLR;
 }
/*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 LCD_DelayMs(5);
 }
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     //��ʾ��һ��
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
 /*------------------------------------------------
              д���ַ�����(�����)
------------------------------------------------*
 void LCD_Write_Char(unsigned char x,unsigned char y,int DATA) 
 { 
	unsigned int i=0,j=0;
	unsigned int LCD_DATA[5];
	
	if(DATA<0){
		DATA=-DATA;
		LCD_Write_String(x,y,"-");
		x++;
	}
	LCD_DATA[0]=(DATA/10000)%10+48;
	LCD_DATA[1]=(DATA/1000)%10+48;
 	LCD_DATA[2]=(DATA/100)%10+48;
 	LCD_DATA[3]=(DATA/10)%10+48;
 	LCD_DATA[4]=DATA%10+48;
 	while(LCD_DATA[i]-48==0&&i<4){
		i++;
		j++;
 	 }
	 for(i=x+j;i<x+5;i++){	
	  	if (y == 0) 
 	{     
 		LCD_Write_Com(0x80 + i - j);     
 	}    
 	else 
 	{     
 		LCD_Write_Com(0xC0 + i - j);     
 	}
	LCD_Write_Data(LCD_DATA[i-x]);
	}  
 }
  /*------------------------------------------------
              д���ַ�����(��λ����ǰ��0)
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,int DATA) 
 { 
	unsigned int i=0;
	unsigned int LCD_DATA[2];
	
 	LCD_DATA[0]=(DATA/10)%10+48;
 	LCD_DATA[1]=DATA%10+48;
	for(i=0;i<2;i++){	
	  	if (y == 0) 
 	{     
 		LCD_Write_Com(0x80 + x + i);
		LCD_Write_Data(LCD_DATA[i]);
 	}    
 	else 
 	{     
 		LCD_Write_Com(0xC0 + x + i);
		LCD_Write_Data(LCD_DATA[i]);     
 	}
	}  
 }
 /*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   LCD_DelayMs(5); 
   LCD_Write_Com(0x38); 
   LCD_DelayMs(5); 
   LCD_Write_Com(0x38); 
   LCD_DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   LCD_DelayMs(5); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
   }
   
