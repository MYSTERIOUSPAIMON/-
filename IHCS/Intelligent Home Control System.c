#include "__STC15_H__.h"                     //ͷ�ļ�
#include <intrins.h>
#define u8 unsigned char                     //����һ��ȫ�ֳ���

u8 code smgduan[]={0xff,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xc0};//2P0
u8 code smgwei[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//P2
u8 Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8;  //�����λ�洢����
u8 k = 0;                                    //����ȫ�ֱ���

void Delay1ms();                             //��ʱ����
void Delay20ms();

/*�������ʾ����*/
void smg_display()	
{
	if(k<=8)
  {
	Num1 = P1&0x0f;		                         //��ȡ�������ֵ�����Ѹ���λ��Ϊ0
    if(k >= 1 &&k<10)  
	{
	P0 = smgduan[Num1]; P2 = smgwei[0]; Delay1ms(); P0 = 0xff;  
    }
	if(k >= 2 &&k<10)  
	{
	P0 = smgduan[Num2]; P2 = smgwei[1]; Delay1ms(); P0 = 0xff;
    }
	if(k >= 3 &&k<10)  
	{
	P0 = smgduan[Num3]; P2 = smgwei[2]; Delay1ms(); P0 = 0xff;
    }
	if(k >= 4 &&k<10)  
	{
	P0 = smgduan[Num4]; P2 = smgwei[3]; Delay1ms(); P0 = 0xff;
    }
	if(k >= 5 &&k<10)  
	{
	P0 = smgduan[Num5]; P2 = smgwei[4]; Delay1ms(); P0 = 0xff;
    }
	if(k >= 6 &&k<10)  
	{
	P0 = smgduan[Num6]; P2 = smgwei[5]; Delay1ms(); P0 = 0xff;
	}
	if(k >= 7 &&k<10)  
	{
	P0 = smgduan[Num7]; P2 = smgwei[6]; Delay1ms(); P0 = 0xff;
	}
	if(k >= 8 &&k<10)  
	{
	P0 = smgduan[Num8]; P2 = smgwei[7]; Delay1ms(); P0 = 0xff;
	}
  	if(k == 9) 
	P0 = 0x0c; P2 = 0x3f; Delay1ms(); P0 = 0xff;
  }
}

/*������*/
void main()
{						  
	EA =1;
	EX0 = 1;
  IT0 = 1; 
	 
	while(1)		
	{
		smg_display();		                      //ѭ���������ʾ�ĺ���
	}
}

/*�ⲿ�ж�0�ĺ���*/
void exint0() interrupt 0		
{
	
	if(!P32)					                        //����ж�����
	{
		Delay20ms();	                          //����
		if(!P32)				
		{
			k++;				                          //�Լ�
			if(k<=8)
			{
				Num8=Num7;
				Num7=Num6;
				Num6=Num5;
				Num5=Num4;
				Num4=Num3;  
				Num3=Num2;
				Num2=Num1; 
      }
			if(k >9)
			{
				k = 1;		 	                        //����K
			}	
		}
		while(!P32);	                          //ֱ�������ɿ�
	}
}

/*��ʱ����*/
void Delay1ms()		//@12.000MHz ��ʱ����1ms
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void Delay20ms()		//@12.000MHz ��ʱ����20ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 234;
	k = 113;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
