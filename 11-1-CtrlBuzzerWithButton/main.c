#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "DigitalTube.h"
#include "Buzzer.h"

unsigned char KeyNum;


void main()
{
	while(1)
	{
		KeyNum = Key();
		Display(1,KeyNum);
		if(KeyNum)
		{
			BuzzerSound(100);
			Display(1,KeyNum);
		}
	}
}