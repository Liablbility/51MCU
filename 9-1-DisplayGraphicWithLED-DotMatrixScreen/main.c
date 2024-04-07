#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5;//RCLK
sbit SCK = P3^6;//SCLK
sbit SER = P3^4;

#define MATRIX_LED_PORT P0

/**
  * @brief  74HC595写入一个字节
  * @param	要写入的字节
  * @retval 无
  **/
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{//初始状态Byte与1000 0000相与 如果最高位不是1 则结果为0 
	 //随后便是Byte的第二高位 。。。一直循环直到全部写入
		SER = Byte&(0x80>>i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

/**
* @brief	LED点阵屏显示一列数据
  * @param 所选择的列  0-7  0在最左边
  * @param 该列所要显示的数据  0x00-0xFF 高位在上 1为亮 0为灭
  * @retval 无
  **/
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	P0 = ~(0x80>>Column);
	//段选 位选 延时 位清零
	Delay(1);
	P0 = 0xFF;
}

void main(){
	SCK = 0;
	RCK = 0;
	
	while(1)
	{
		MatrixLED_ShowColumn(0,0x80);
		MatrixLED_ShowColumn(1,0x40);
		MatrixLED_ShowColumn(2,0x20);
		MatrixLED_ShowColumn(3,0x10);
	}
	
}