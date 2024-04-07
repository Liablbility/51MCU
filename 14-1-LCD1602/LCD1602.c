#include <REGX52.H>

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_E = P2^7;
#define LCD_DataPort P0

void LCD_Delay(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}


void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_Init()
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char row,unsigned char col)
{
	if(row == 1)
		LCD_WriteCommand(0x80|(col - 1));
	else
		LCD_WriteCommand(0x80|(col - 1)+0x40);
}

void LCD_MoveCursor(unsigned char direction)
{
	if(direction > 0)
		LCD_WriteCommand(0x18);//右移
	else
		LCD_WriteCommand(0x1C);//左移
}

void LCD_ShowChar(unsigned char row,unsigned char col,unsigned char C)
{
	LCD_SetCursor(row,col);
	LCD_WriteData(C);
}	

void LCD_ShowString(unsigned char row,unsigned char col,unsigned char* Str)
{
	unsigned char i;
	LCD_SetCursor(row,col);
	for(i = 0; Str[i] != '\0';i++)
		LCD_WriteData(Str[i]);
}

int LCD_Pow(int X,unsigned int Y)
{
	unsigned char i;
	int result = 1;
	for(i = 0; i < Y; i++)
		result *= X;
	return result;
}

void LCD_ShowNum(unsigned char row,unsigned char col,unsigned int num,unsigned char len)
{
	unsigned char i;
	LCD_SetCursor(row,col);
	for(i = len; i > 0; i--)
		LCD_WriteData('0'+(num / LCD_Pow(10,i-1))	% 10);

}
void LCD_ShowSignedNum(unsigned char row,unsigned char col,int num,unsigned char len)
{
	unsigned char i;
	unsigned int numTmp;//为了防止-32768显示不出来
	LCD_SetCursor(row,col);
	if(num >= 0)
	{
		LCD_WriteData('+');
		numTmp = num;
	}
	else
	{
		LCD_WriteData('-');
		numTmp = -num;
	}
	for(i = len; i > 0; i--)
		LCD_WriteData('0'+(numTmp/ LCD_Pow(10,i-1))	% 10);
	
}

void LCD_ShowHexNum(unsigned char row,unsigned char col,unsigned char num,unsigned char len)
{
	unsigned char i;
	unsigned char SingleNum;
	LCD_SetCursor(row,col);
	for(i = len; i > 0; i--)
	{
		SingleNum = (num / LCD_Pow(16,i-1))	% 16;
		if(SingleNum < 10)
			LCD_WriteData('0'+ SingleNum);
		else
			LCD_WriteData('A'+ SingleNum - 10);
	
	}
}

void LCD_ShowBinNum(unsigned char row,unsigned char col,unsigned char num,unsigned char len)
{
	unsigned char i;
	unsigned char SingleNum;
	LCD_SetCursor(row,col);
	for(i = len; i > 0; i--)
		LCD_WriteData('0'+(num / LCD_Pow(2,i-1))	% 2);
}