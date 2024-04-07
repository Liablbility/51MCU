#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"

float T;
char Tl=-10,Th=20;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();
	Delay(1000);
	Th = AT24C02_ReadByte(0);
	Tl = AT24C02_ReadByte(1);
	if(Th > 125 || Tl < -55 || Th < Tl)
	{
		Th = 20;
		Tl = -10;
	}
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,Th,3);
	LCD_ShowSignedNum(2,12,Tl,3);
	
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		//温度读取及显示
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		LCD_ShowSignedNum(1,3,T,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(T*100)%100,2);
		//阈值判断及显示
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				Th++;
				if(Th > 125)
					Th = 125;
			}
			if(KeyNum == 2)
			{
				Th--;
				if(Th <= Tl)
					Th++;
			}
			if(KeyNum ==3)
			{
				Tl++;
				if(Tl >= Th)
					Tl--;
			}
			if(KeyNum == 4)
			{
				Tl--;
				if(Tl < -55)
					Tl = -55;
			}
			LCD_ShowSignedNum(2,4,Th,3);
			LCD_ShowSignedNum(2,12,Tl,3);
			AT24C02_WriteByte(0,Th);
			Delay(5);
			AT24C02_WriteByte(1,Tl);
		}
		if(T > Th)
			LCD_ShowString(1,13,"Ov-H");
		else if(T < Tl)
			LCD_ShowString(1,13,"Ov-C");
		else
			LCD_ShowString(1,13,"    ");
	}

}

void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count;
		TL0 = 0x66;
		TH0 = 0xFC;
		T0Count++;
		if(T0Count >= 20)
		{
			T0Count = 0;
			KeyLoop();
		}	
}

