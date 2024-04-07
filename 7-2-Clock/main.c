#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"

unsigned int Sec,Min=54,Hr=10;

void main(){
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock");
	while(1)
	{
		LCD_ShowNum(2,1,Hr,2);
		LCD_ShowString(2,3,":");
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowString(2,6,":");
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count;
		TL0 = 0x66;	
		TH0 = 0xFC;	

		T0Count++;
		if(T0Count >= 1000)
		{
			T0Count = 0;
			Sec++;
			if(Sec >= 60)
			{
				Sec = 0;
				Min++;
				if(Min >= 60)
				{
					Min = 0;
					Hr++;
					if(Hr >= 24)
						Hr = 0;
				}
			}
		}
}
