#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"
#include "AT24C02.h"


void main()
{
	unsigned char KeyNum;
	unsigned int Num=0;
	LCD_Init();
	LCD_ShowString(1,1,"Hello");
//	AT24C02_WriteByte(1,66);
//	Delay(10);//要等一下才能读到刚写的数据
//	//最低5ms
//	Data = AT24C02_ReadByte(1);
	
	while(1)
	{
		LCD_ShowNum(1,1,Num,5);
		KeyNum = Key();
		if(KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 3)
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);
			AT24C02_WriteByte(1,Num/256);
			Delay(5);
			LCD_ShowString(2,1,"Write Done");
			Delay(1000);
			LCD_ShowString(2,1,"          ");
		}
		if(KeyNum == 4)
		{
			Num = AT24C02_ReadByte(0);
			Num |= AT24C02_ReadByte(1)<<8;
			LCD_ShowString(2,1,"Read Done");
			Delay(500);
			LCD_ShowString(2,1,"         ");
			LCD_ShowNum(2,1,Num,5);
			Delay(1000);
			LCD_ShowString(2,1,"         ");
		}
	}
}