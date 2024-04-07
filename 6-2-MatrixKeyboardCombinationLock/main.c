#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,cnt = 0;

void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Password");
	while(1){
		KeyNum = MatrixKey();
		if(KeyNum){
			if(KeyNum <= 10){
				if(cnt < 4){
					Password *= 10;//先左移一位
					Password += KeyNum%10;//获取一位密码
					//并添加到密码的末尾
					cnt++;}
				LCD_ShowNum(2,1,Password,4);
			}
			if(KeyNum == 11)//s11按键按下->确认
			{
				if(Password == 2345)
					LCD_ShowString(1,10,"Pass");
				else
					LCD_ShowString(1,10,"Error");
				Password = 0;
				cnt = 0;
				LCD_ShowNum(2,1,Password,4);
				Delay(1000);
				LCD_ShowString(1,10,"     ");
			}
			if(KeyNum == 12)//s11按键按下->退格
			{
				Password = 0;
				cnt = 0;
				LCD_ShowNum(2,1,Password,4);
			}
		}
	}
}