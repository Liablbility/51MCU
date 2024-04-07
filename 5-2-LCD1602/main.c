#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

int cnt = 0;

void main(){
	
	LCD_Init();
	
	while(1){
		cnt++;
		Delayxms(1000);
		LCD_ShowNum(1,1,cnt,3);
	}
}