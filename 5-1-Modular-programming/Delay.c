
void Delayxms(unsigned int x)	//@12.000MHz
{
	unsigned char data i, j;
	
	while(x>0){
		i = 2;//这两句也要放入循环
		j = 239;
		do{
			while (--j);
		} while (--i);
		x--;
	}
}

