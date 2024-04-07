#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum,LEDMode;

//主函数
void main(){
	P2=0xFE;//1111 1110
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
				if(KeyNum == 1)
				{
					LEDMode++;
					if(LEDMode >= 2)
						LEDMode = 0;
				}
		}
	}
}

//中断函数
void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count;
		TL0 = 0x66;
		TH0 = 0xFC;
		T0Count++;
		if(T0Count >= 500)
		{
			T0Count = 0;
			if(LEDMode == 0)
				P2 = _crol_(P2,1);
			else if(LEDMode == 1)
				P2 = _cror_(P2,1);
		} 
		
}