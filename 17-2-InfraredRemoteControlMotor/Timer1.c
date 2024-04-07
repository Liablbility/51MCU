#include <REGX52.H>

void Timer1_Init(){
	TMOD = TMOD&0x0F;
	TMOD = TMOD|0x10;
	TF1 = 0;
	TR1 = 1;
	TL1 = 0x66;
	TH1 = 0xFC;
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}
/*
//中断函数
void Timer1_Routine() interrupt 3
{		
		static unsigned int T1Count;
		TL1 = 0x66;
		TH1 = 0xFC;
		T1Count++;
		if(T1Count >= 1000)
		{
			T1Count = 0;
			P2_0 = ~P2_0;
		}	
}
*/
