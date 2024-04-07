#include <REGX52.H>
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
	unsigned char LEDNum = 0;
	P2 = ~(0x55);
	while(1){
		if(P3_1 == 0){
			Delayxms(20);
			while(P3_1 == 0);
			Delayxms(20);
			
			LEDNum++;
			if(LEDNum >= 4)
				LEDNum = 0;
			P2 = ~(0x55<<LEDNum);
		}
		if(P3_0 == 0){
			Delayxms(20);
			while(P3_0 == 0);
			Delayxms(20);
			
			LEDNum--;
			if(LEDNum < 0)
				LEDNum = 3;
			P2 = ~(0x55<<LEDNum);
		}
	}
}
