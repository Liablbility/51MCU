#include <REGX52.H>
#include "Delay.h"
#include "DigitalTube.h"
#include "Motor.h"
#include "IR.h"

unsigned char Speed = 0;

void main()
{
	Motor_Init();
	IR_Init();
	while(1)
	{
		
		if(IR_GetDataFlag())
		{
			if(IR_GetCommand() == IR_VOL_MINUS)
				Speed--;
			if(IR_GetCommand() == IR_VOL_ADD)
				Speed++;
			Speed %= 5;
		}
		Motor_SetSpeed(Speed);
		DigitalTube_SetBuf(1,Speed);
	}
	
}
