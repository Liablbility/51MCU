#include <REGX52.H>
#include "Int0.h"
#include "Timer0.h"

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;
unsigned char IR_ReSentFlag;
unsigned char IR_Address,IR_Command;

void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag()
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetReSentFlag()
{
	if(IR_ReSentFlag)
	{
		IR_ReSentFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress()
{
	return IR_Address;
}

unsigned char IR_GetCommand()
{
	return IR_Command;
}

void Int0_Rountine() interrupt 0
{
	if(IR_State == 0)
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > (13500-500)/1.085 && IR_Time < (13500+500)/1.085)
			IR_State = 2;
		else if(IR_Time > (11250-500)/1.085 && IR_Time < (11250+500)/1.085)
		{
			IR_ReSentFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}else//如果重发信号也出错了，还是回到起始状态
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)//开始解码
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > 1120-500 && IR_Time < 1120+500)
		{//逻辑0
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
			IR_pData++;
		}
		else if(IR_Time > 2250-500 && IR_Time < 2250+500)
		{//逻辑1
			IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			IR_pData++;
		}
		else//如果接收信号出错
		{//直接开始接受信号
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)
		{
			IR_pData = 0;
			if(IR_Data[0] == ~IR_Data[1] && IR_Data[2] == ~IR_Data[3])
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
				Timer0_Run(1);//停止计时器
				IR_State = 0;//切回空闲状态
			}
		}
	}
}



