#include <REGX52.H>
#include "Delay.h"

unsigned char KeyNumTmp;

/**
  * @brief 获取独立按键键码
  * @param 无
  * @retval 所按按键的键码 范围0~4 无按键按下时返回值为0
  **/
unsigned char Key(){
	unsigned char Tmp;
	Tmp = KeyNumTmp;
	KeyNumTmp = 0;
	return Tmp;
}

unsigned char GetKeyState(){
	
	unsigned char KeyNumber = 0;
	
	if(P3_1 == 0)
		KeyNumber=1;
	if(P3_0 == 0)
		KeyNumber=2;
	if(P3_2 == 0)
		KeyNumber=3;
	if(P3_3 == 0)
		KeyNumber=4;
	
	return KeyNumber;
}

void KeyLoop()
{
	static unsigned char NowState,LastState;
	LastState = NowState;
	NowState = GetKeyState();
	if(LastState == 0 && NowState == 1)
	{//按下就立即执行
		KeyNumTmp = 1;
	}
	if(LastState == 2 && NowState == 0)
	{
		KeyNumTmp = 2;
	}
	if(LastState == 3 && NowState == 0)
	{
		KeyNumTmp = 3;
	}
	if(LastState == 4 && NowState == 0)
	{
		KeyNumTmp = 4;
	}
}

