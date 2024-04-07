#include <REGX52.H>
#include "Delay.h"
#include "DigitalTube.h"
#include "Key.h"
#include "Timer0.h"

unsigned char Counter,Compare;
unsigned char KeyNum,Speed=0;
unsigned char i;

sbit LED = P2^0;
sbit DA = P2^1;

void main()
{
	Timer0_Init();
	DA = 0;
	while(1)
	{
		for(i = 0; i < 100; i++)
		{
			Compare = i;
			Delay(10);
		}
		for(i = 100; i > 0; i--)
			Compare = i;
		KeyNum = Key();
		if(KeyNum == 1)
		{
			Speed++;
			Speed %= 4;
		}
		Compare = (Speed + 1) * 5;
		DigitalTube_SetBuf(1,(Speed + 1));
	}
	
}
void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count,T1Count;
		TL0 = 0xA4;				//设置定时初始值
		TH0 = 0xFF;				//设置定时初始值
		Counter++;
		Counter %= 20;
		if(Counter < Compare)
		{
			DA = 1;
			LED = 0;
		}
		else
		{
			DA = 0;
			LED = 1;
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