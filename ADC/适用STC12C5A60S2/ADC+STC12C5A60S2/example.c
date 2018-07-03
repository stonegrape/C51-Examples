#include <STC12C5A.h>
#include <ADC.h>
#include <12864.h>

#define uchar unsigned char
#define uint unsigned int

void delay(unsigned int x){
 	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}

void main()
{
	unsigned int distance[5];
	int i;
	LCD12864_Init();
	while(1){
		ADC_Get(0);
		distance[4]=ADC_value%10;
		distance[3]=ADC_value/10%10;
		distance[2]=ADC_value/100%10;
		distance[1]=ADC_value/1000%10;
		distance[0]=ADC_value/10000%10;
		LCD12864_Clear();
		LCD12864_String(0,0,"µçÑ¹£º");
		for(i=0;i<5;i++){
			switch(distance[i]){
				case 0:{
					LCD12864_String(0,3+i,"0 ");
					break;
				}
				case 1:{
					LCD12864_String(0,3+i,"1 ");
					break;
				}
				case 2:{
					LCD12864_String(0,3+i,"2 ");
					break;
				}
				case 3:{
					LCD12864_String(0,3+i,"3 ");
					break;
				}
				case 4:{
					LCD12864_String(0,3+i,"4 ");
					break;
				}
				case 5:{
					LCD12864_String(0,3+i,"5 ");
					break;
				}
				case 6:{
					LCD12864_String(0,3+i,"6 ");
					break;
				}
				case 7:{
					LCD12864_String(0,3+i,"7 ");
					break;
				}
				case 8:{
					LCD12864_String(0,3+i,"8 ");
					break;
				}
				case 9:{
					LCD12864_String(0,3+i,"9 ");
					break;
				}
				default:{
					LCD12864_String(0,3+i,"0 ");
					break;
				}
			}	
		}
		delay(2000);
	}
}