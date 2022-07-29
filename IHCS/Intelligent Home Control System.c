#include "__STC15_H__.h"                     //头文件
#include <intrins.h>
#define u8 unsigned char                     //定义一个全局常量

u8 code smgduan[]={0xff,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xc0};//2P0
u8 code smgwei[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//P2
u8 Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8;  //定义八位存储号码
u8 k = 0;                                    //定义全局变量

void Delay1ms();                             //延时函数
void Delay20ms();

/*数码管显示函数*/
void smg_display()	
{
	if(k<=8)
  {
	Num1 = P1&0x0f;		                         //读取输入的数值，并把高四位设为0
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

/*主函数*/
void main()
{						  
	EA =1;
	EX0 = 1;
  IT0 = 1; 
	 
	while(1)		
	{
		smg_display();		                      //循环数码管显示的函数
	}
}

/*外部中断0的函数*/
void exint0() interrupt 0		
{
	
	if(!P32)					                        //检测中断请求
	{
		Delay20ms();	                          //消抖
		if(!P32)				
		{
			k++;				                          //自加
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
				k = 1;		 	                        //重置K
			}	
		}
		while(!P32);	                          //直至按键松开
	}
}

/*延时函数*/
void Delay1ms()		//@12.000MHz 延时程序1ms
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void Delay20ms()		//@12.000MHz 延时程序20ms
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
