#include <REGX52.H>
#include <INTRINS.H>
void Delay250ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 2;
	j = 231;
	k = 91;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main(){
	while(1){
		P2 = 0x77;
		Delay250ms();
		P2 = 0xBB;
		Delay250ms();
		P2 = 0xDD;
		Delay250ms();
		P2 = 0xEE;
		Delay250ms();
	}
}