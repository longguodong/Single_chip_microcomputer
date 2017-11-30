#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int  
sbit DQ = P1^4;


void delay(unsigned char i);
void Init_Ds18b20(void);
uchar Read_One_Byte();
void Write_One_Byte(uchar dat);
uint Get_Tmp();

#endif