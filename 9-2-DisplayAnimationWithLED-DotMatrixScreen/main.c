#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"

unsigned char Animation[]={
0x3C,0x42,0x81,0x81,0x85,0x42,0x3D,0x00,0x1E,0x01,0x01,0x01,0x1E,0x00,0x0E,0x15,
0x15,0x15,0x0C,0x00,0x0E,0x15,0x15,0x15,0x0C,0x00,0x1F,0x08,0x10,0x10,0x0F,0x00,
0x17,0x17,0x00,0x0E,0x15,0x15,0x15,0x0C
};//定义时还可以在数组名之前加上关键字 code 
//code的作用是 把数据写入rom这样会减少程序对ram的占用
//缺点是不能再进行写入的操作了

void main(){
	unsigned char i,offset=0,count=0;
	MatrixLED_Init();
	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			MatrixLED_ShowColumn(i,Animation[(i+offset)%40]);
		}
		count++;
		if(count >= 10)
		{
			count=0;
			offset++;
			if(offset >= 39)
				offset = 0;
		}
	}
	
}