#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
float T;

void main()
{
	DS18B20_ConvertT();
	//P2_0 = 0;
	Delay(1000);//给设备一点时间让它完成转换
	//P2_0 = 1;
	LCD_Init();
	LCD_ShowString(1,1,"Temperature");
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T<0)
			LCD_ShowChar(2,1,'-');
		else if(T == 0)
			LCD_ShowChar(2,1,' ');
		else
			LCD_ShowChar(2,1,'+');
		LCD_ShowNum(2,2,T,2);
		LCD_ShowChar(2,4,'.');
		LCD_ShowNum(2,5,(unsigned long)(T*10)%10,1);
	}
	
}