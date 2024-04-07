#include <REGX52.H>
#include "Delay.h"

unsigned char DigitalTubeBuf[9]={
0,10,10,10,10,10,10,10,10
};
unsigned char NumCode[] = {
0x3F,0x06,0x5B,0x4F,0x66,
0x6D,0x7D,0x07,0x7F,0x6F,
0x00,0x40//横杠
};

void DigitalTube_SetBuf(unsigned char Location,int Number)
{
	DigitalTubeBuf[Location] = Number;
}

void DigitalTube(unsigned char Location,int Number)
{
	P0 = 0x00;
	switch(Location){
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0 = NumCode[Number];
}

void DigitalTubeLoop()//定时器扫描数码管
{
	static unsigned char i=1;
	DigitalTube(i,DigitalTubeBuf[i]);
	i++;
	if(i >= 9)
		i = 1;
}
