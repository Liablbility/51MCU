#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"
#include "Delay.h"

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlash;
char DS1302_TimeBoundry[]={99,12,31,23,59,59,7};
unsigned char WeekDay[7][4] = 
	{"Mon","Tue","Wen","Tur","Fri","Sat","Sun"}; 
//要判断小于0所以用了有符号的
void TimeShow()
{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowString(1,3,"-");
		LCD_ShowString(1,6,"-");
		LCD_ShowString(1,10,WeekDay[DS1302_Time[6]-1]);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);
		LCD_ShowString(2,3,":");
		LCD_ShowString(2,6,":");
}

void DateJudge()//判断每月应该有多少天
{
	if(DS1302_Time[1]== 1||DS1302_Time[1]== 3 ||
		 DS1302_Time[1]== 5||DS1302_Time[1]== 7 ||
		 DS1302_Time[1]== 8||DS1302_Time[1]== 10||
		 DS1302_Time[1]== 12)
		DS1302_TimeBoundry[2] = 31;
	else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 ||
					DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
					DS1302_TimeBoundry[2] = 30;
	else //二月
	{
		if(DS1302_Time[0] % 4 == 0)//闰年
			//四年一润，百年不润，四百年再润
			DS1302_TimeBoundry[2] = 29;
		else
			DS1302_TimeBoundry[2] = 28;
	}
}
void TimeSet()
{
	if(KeyNum == 2)
	{
		TimeSetSelect++;
		TimeSetSelect %= 7;
		//LCD_ShowNum(2,10,TimeSetSelect,2);
	}
	if(KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect]++;
		if(TimeSetSelect == 1 || TimeSetSelect == 2||TimeSetSelect == 6)
		{//月和日没有0
			DateJudge();
			if(DS1302_Time[TimeSetSelect] > DS1302_TimeBoundry[TimeSetSelect])
				DS1302_Time[TimeSetSelect] = 1;//月和日 星期 没有0
			if(TimeSetSelect == 1)//如果在调月
				{
					DateJudge();
					if(DS1302_Time[2] > DS1302_TimeBoundry[2])
						//判断当前 日 在修改后的月里有没有超出边界
						DS1302_Time[2] = DS1302_TimeBoundry[2];
				}
		}
		else
		{
			if(DS1302_Time[TimeSetSelect] > DS1302_TimeBoundry[TimeSetSelect])
				DS1302_Time[TimeSetSelect] = 0;
		}
	}
	if(KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect]--;
		if(TimeSetSelect == 1 || TimeSetSelect == 2||TimeSetSelect == 6)
		{//月和日没有0
			DateJudge();
			if(DS1302_Time[TimeSetSelect] < 1)//月和日没有0
				DS1302_Time[TimeSetSelect] = DS1302_TimeBoundry[TimeSetSelect];
			if(TimeSetSelect == 1)//如果在调月
			{
				DateJudge();
				if(DS1302_Time[2] > DS1302_TimeBoundry[2])
					//判断当前 日 在修改后的月里有没有超出边界
					DS1302_Time[2] = DS1302_TimeBoundry[2];
			}
		}
		else
		{
			if(DS1302_Time[TimeSetSelect] < 0)
					DS1302_Time[TimeSetSelect] = DS1302_TimeBoundry[TimeSetSelect];
		 }
	}	
	//显示所修改的时间并且让所调的位置进行闪烁
	if(TimeSetSelect == 0 && TimeSetFlash == 1)
		LCD_ShowString(1,1,"  ");//空字符应该在if里否则会只显示当前调的那一位
	else
		LCD_ShowNum(1,1,DS1302_Time[0],2);
	if(TimeSetSelect == 1 && TimeSetFlash == 1)
		LCD_ShowString(1,4,"  ");
	else
		LCD_ShowNum(1,4,DS1302_Time[1],2);
	if(TimeSetSelect == 2 && TimeSetFlash == 1)
		LCD_ShowString(1,7,"  ");
	else
		LCD_ShowNum(1,7,DS1302_Time[2],2);
	if(TimeSetSelect == 3 && TimeSetFlash == 1)
		LCD_ShowString(2,1,"  ");
	else
		LCD_ShowNum(2,1,DS1302_Time[3],2);	
	if(TimeSetSelect == 4 && TimeSetFlash == 1)
		LCD_ShowString(2,4,"  ");
	else
		LCD_ShowNum(2,4,DS1302_Time[4],2);
	if(TimeSetSelect == 5 && TimeSetFlash == 1)
		LCD_ShowString(2,7,"  ");
	else
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	if(TimeSetSelect == 6 && TimeSetFlash == 1)
		LCD_ShowString(1,10,"   ");
	else
		{
			LCD_ShowString(1,10,WeekDay[DS1302_Time[6]-1]);
		}
		
}
void main(){
	
	
	Delay(2000);
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	DS1302_SetTime();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			if(MODE == 0) MODE = 1;
			else if(MODE == 1) 
			{
				DS1302_SetTime();
				//不建议DS1302_SetTime()写在TimeSet()里面
				//因为这样操作太过于频繁，没必要
				MODE = 0;
			}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	}
}
void Timer0_Routine() interrupt 1
{		
		static unsigned int T0Count;
		TL0 = 0x66;
		TH0 = 0xFC;
		T0Count++;
		if(T0Count >= 500)
		{
			T0Count = 0;
			//P2_0 = ~P2_0;//按位取反
			TimeSetFlash = !TimeSetFlash;//逻辑取反
		}
}