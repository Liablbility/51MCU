#include <REGX52.H>
#include "Int0.h"

void Timer0_Init(){
	TMOD = TMOD&0xF0;
	TMOD = TMOD|0x01;
	TF0 = 0;
	TR0 = 0;
}

void Timer0_SetCounter(unsigned int Value){
	TH0 = Value / 256;
	TL0 = Value % 256;
}

unsigned int Timer0_GetCounter()
{
	return (TH0<<8)|TL0;
}

void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;
}

/*
//中断函数
void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count;
		TL0 = 0x66;
		TH0 = 0xFC;
		T0Count++;
		if(T0Count >= 1000)
		{
			T0Count = 0;
			P2_0 = ~P2_0;
		}	
}
*/
