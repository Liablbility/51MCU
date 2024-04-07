#include <REGX52.H>
#include "Key.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "DigitalTube.h"

unsigned char Min,Sec,MinSec;
unsigned char RunFlag;


void main()
{
	unsigned char KeyNum;
	Timer0_Init();
	
	while(1)
	{
		DigitalTube_SetBuf(1,Min/10);
		DigitalTube_SetBuf(2,Min%10);
		DigitalTube_SetBuf(3,11);//显示杠
		DigitalTube_SetBuf(4,Sec/10);
		DigitalTube_SetBuf(5,Sec%10);
		DigitalTube_SetBuf(6,11);
		DigitalTube_SetBuf(7,MinSec/10);
		DigitalTube_SetBuf(8,MinSec%10);
		KeyNum = Key();
		if(KeyNum == 1)
		{
			RunFlag = !RunFlag;
		}
		if(KeyNum == 2)
		{
			Min = 0;
			Sec = 0;
			MinSec = 0;
		}
		if(KeyNum == 3)
		{
			AT24C02_WriteByte(0,Min);
			Delay(5);
			AT24C02_WriteByte(1,Sec);
			Delay(5);
			AT24C02_WriteByte(2,MinSec);
			Delay(5);
		}
		if(KeyNum == 4)
		{
			Min = AT24C02_ReadByte(0);
			Sec = AT24C02_ReadByte(1);
			MinSec = AT24C02_ReadByte(2);
		}
	}
}

void Sec_Loop()
{
	if(RunFlag)
	{
		MinSec++;
		if(MinSec >=100)
		{
			MinSec = 0;
			Sec++;
			if(Sec >= 60)
			{
				Sec = 0;
				Min++;
				if(Min >= 60)
					Min = 0;
			}
		}
	}
	
}

//中断函数
void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count1,T0Count2,T0Count3;
		TL0 = 0x66;
		TH0 = 0xFC;
		T0Count1++;
		if(T0Count1 >= 20)
		{
			T0Count1 = 0;
			KeyLoop();
		}
		T0Count2++;
		if(T0Count2 >= 2)//数码管扫描
		{
			T0Count2 = 0;
			DigitalTubeLoop();
		}
		T0Count3++;
		if(T0Count3 >= 10)
		{
			T0Count3 = 0;
			Sec_Loop();
		}
}
