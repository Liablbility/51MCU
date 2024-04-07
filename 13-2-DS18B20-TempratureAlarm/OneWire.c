#include <REGX52.H>

sbit OneWire_DQ = P3^7; 

unsigned char OneWire_Init()
{
	unsigned char i,AckBit;
	EA = 0;//屏蔽中断 防止在延时的过程中被中断打断
	OneWire_DQ = 1;
	OneWire_DQ = 0;

	i = 227; while(--i);//延时500微秒
	OneWire_DQ = 1;

	i = 29;while (--i);//延时70微秒
	AckBit = OneWire_DQ;
	i = 227; while(--i);//延时500微秒
	EA = 1;//开启中断
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char data i;
	EA = 0;//屏蔽中断
	
	OneWire_DQ = 0;//在发送1bit之前肯定是初始化
	//所以没先把OneWire_DQ置1
	//这里用了一点技巧，10us之后将Bit送到总线上
	//如果Bit是0则一直是0 如果是1则一直是1，满足0和1的检测条件
	//省去了if判断
	i = 2;while (--i);//延时10微秒
	OneWire_DQ = Bit;
	i = 20;while (--i);//延时50微秒
	OneWire_DQ = 1;
	EA = 1;//开启中断
}

unsigned char OneWire_ReceiveBit()
{
	unsigned char i,Bit;
	EA = 0;//屏蔽中断
	
	OneWire_DQ = 0;
	i = 1;while (--i);//延时5微秒
	OneWire_DQ = 1;
	i = 1;while (--i);//延时5微秒
	Bit = OneWire_DQ;
	i = 20;while (--i);//延时50微秒
	EA = 1;//开启中断
	return Bit;
} 

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
		OneWire_SendBit(Byte&(0x01<<i));
}

unsigned char OneWire_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	for(i = 0; i < 8; i++)
		if(OneWire_ReceiveBit()) 
			Byte |= (0x01<<i);
	return Byte;
}