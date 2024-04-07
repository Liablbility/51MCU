#include <REGX52.H>
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

void main(){
	while(1){
		P2 = 0x55;
		Delayxms(500);
		P2 = 0xAA;
		Delayxms(500);
	}
}