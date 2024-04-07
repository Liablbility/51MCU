#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;

void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Matrix Key");
	while(1){
		KeyNum = MatrixKey();//，没有按键按下返回值等于0
		if(KeyNum){//如果有新的按键按下更新显示的值
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}