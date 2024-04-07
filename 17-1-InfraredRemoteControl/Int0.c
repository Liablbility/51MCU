#include <REGX52.H>

void Int0_Init()	
{
	IT0 = 1;
	IE0 = 0;
	EX0 = 1;
	PX0 = 1;//由于红外对时延的要求较高
	EA = 1;
}
/*
void Int0_Rountine() interrupt 0
{

}
*/
