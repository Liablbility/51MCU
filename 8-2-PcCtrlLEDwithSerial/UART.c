#include <REGX52.H>

/**
  * @brief  串口初始化 2400 @11.0592MHz
  * @param  无
  * @retval 无
  **/

void UART_Init(){
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//工作方式1且 REN接受位置1
	TMOD = TMOD&0x0F;//高4位清零 配置定时器1
	TMOD = TMOD|0x20;//0010 0000
	TL1 = 0xF4;//设置定时初始值
	TH1 = 0xF4;//设置定时重载值
	ET1 = 0;
	TR1 = 1;//定时器1开始计时
	EA = 1;//启动所有中断
	ES = 1;//启动串口中断
}

/**
  * @brief  串口发送一个字节数据 2400 @11.0592MHz
  * @param  char Byte 待发送的数据
  * @retval 无
  **/

void UART_SendByte(unsigned char Byte){
	SBUF=Byte;
	while(TI == 0);
	TI = 0;
}