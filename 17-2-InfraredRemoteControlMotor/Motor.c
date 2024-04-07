#include <REGX52.H>
#include "Timer1.h"
#include "Key.h"

sbit M = P1^0;

unsigned char Counter,Compare;

void Motor_Init()
{
	M = 0;
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed * 50;
}

void Timer1_Routine() interrupt 3
{		
		static unsigned int T0Count,T1Count;
		TL1 = 0xA4;				//设置定时初始值
		TH1 = 0xFF;				//设置定时初始值
		Counter++;
		Counter %= 200;
		if(Counter < Compare)
		{
			M = 1;
		}
		else
		{
			M = 0;
		}
		T0Count++;
		if(T0Count >200)
		{
			T0Count= 0;
			KeyLoop();
		}
		T1Count++;
		if(T1Count > 10)
		{
			T1Count= 0;
			DigitalTubeLoop();
		}	
}
