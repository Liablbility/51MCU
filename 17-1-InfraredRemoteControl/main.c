#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

char Num;
unsigned int Address,Command;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Quennie");
	
	IR_Init();
	
	while(1)
	{
		LCD_ShowSignedNum(1,10,Num,3);
		if(IR_GetDataFlag() || IR_GetReSentFlag())
		{//IR_GetReSentFlag() 加入 实现连发功能
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			LCD_ShowHexNum(2,1,Address,2);
			LCD_ShowHexNum(2,4,Command,2);
			if(Command == IR_VOL_MINUS)
				Num--;
			if(Command == IR_VOL_ADD)
				Num++;
		}
	}
}

