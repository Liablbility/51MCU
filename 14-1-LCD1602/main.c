#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

#define Right 1
#define Left  0

void main()
{ 
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,2,"Hello");
	LCD_ShowNum(2,1,66,2);
	LCD_ShowSignedNum(2,3,-66,2);
	LCD_ShowHexNum(2,6,0xA5,2);
	LCD_ShowBinNum(1,7,0xA5,8);
	LCD_ShowChar(2,8,0xDF);
	while(1)
	{

	}
}