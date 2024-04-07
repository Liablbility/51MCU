#include <REGX52.H>
unsigned char NumCode[] = {
0x3F,0x06,0x5B,0x4F,0x66,
0x6D,0x7D,0x07,0x7F,0x6F,
};
#include <INTRINS.H>
void Delayxms(unsigned int x)	//@12.000MHz
{
	unsigned char data i, j;
	
	while(x>0){
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		x--;
	}
}
void Display(unsigned char Location,int Number){
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
	Delayxms(1);
	P0 = 0x00;
}
void main(){
	
	while(1){
		Display(1,1);
		Display(2,2);
		Display(3,3);
		Display(4,4);
		Display(5,5);
		Display(6,6);
		Display(7,7);
		Display(8,8);
	}
}