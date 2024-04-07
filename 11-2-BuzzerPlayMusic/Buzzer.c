#include <REGX52.H>
#include <INTRINS.H>

sbit Buzzer = P2^5;//新版地址 旧版地址在P1^5

/**
  * @brief 蜂鸣器私有延时函数  延时500us
  * @param 无
  * @retval 无
  **/
void BuzzerDelay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief 蜂鸣器发声
  * @param 发声的时长 ms
  * @retval 无
  **/
void BuzzerSound(unsigned int ms)//@12.000MHz
{
	unsigned int i;
	for(i = 0; i < ms*2; i++)
	{
		Buzzer = !Buzzer;
		BuzzerDelay500us();
	}
}

