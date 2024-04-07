#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0

/**
  * @brief AT24C02写入一个字节
  * @param WordAddress 要写入字节的地址
	* @param Data  要写入的数据
  * @retval
  **/

void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	unsigned char Ack;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	Ack = I2C_ReceiveAck();
	if(Ack == 0)
	{
		I2C_SendByte(WordAddress);
		Ack = I2C_ReceiveAck();
		if(Ack == 0)
			I2C_SendByte(Data);
	}
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
  * @brief AT24C02读取一个字节
  * @param WordAddress 要读出字节的地址
  * @retval Data  读出的数据
  **/

unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data,Ack;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	Ack = I2C_ReceiveAck();
	if(Ack == 0)
	{
		I2C_SendByte(WordAddress);
		Ack = I2C_ReceiveAck();
		if(Ack == 0)
		{
			I2C_Start();
			I2C_SendByte(AT24C02_ADDRESS|0x01);
			//发送读地址
			I2C_ReceiveAck();
			Data = I2C_ReceiveByte();
			I2C_SendAck(1);
		}
	}
	I2C_Stop();
	return Data;
}
