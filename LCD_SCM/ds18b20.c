#include "ds18b20.h"
#include <intrins.h>

long temp; 
void delay(unsigned char i)				   //短延时
{
	while(--i);
}

void Init_Ds18b20(void)     //DS18B20初始化send reset and initialization command
{

DQ=1;			  //总线短暂拉高
delay(1); 
DQ=0;			  //主机发出低电平
delay(250);	//低电平持续800us左右，检测总线有没有低电平,
DQ=1;
delay(100); 	//等待120us
			               
}

uchar Read_One_Byte()       //读取一个字节的数据read a byte date

{
	uchar i   = 0;
	uchar dat = 0;
	for(i=8;i>0;i--)  //读取8次，从低到高
	{
		DQ = 0;        //拉高总线1us后释放         
		_nop_();                
		dat >>= 1;       //依次右移      
		DQ = 1;          //释放总线  
		delay(1);               
		if(DQ)                  
		{
			dat |= 0x80;        
		}
		delay(10);             
	}
	return (dat);
}

void Write_One_Byte(uchar dat)
{
	uchar i = 0;
	for(i=8;i>0;i--)
	{
		DQ = 0;        //拉低总线1us                
		_nop_();           
		DQ = dat&0x01;  //将数据写到总线             
		delay(10);      //采样60us            
		DQ = 1;                        
		dat >>= 1;
	delay(1);
	}
}

uint Get_Tmp()                   
{
	float tt;
	uchar a,b;
	Init_Ds18b20();                
	Write_One_Byte(0xcc);     //主机发出复位指令    
	Write_One_Byte(0x44);     //跳过ROM 
	Init_Ds18b20();           //再次初始化    
	Write_One_Byte(0xcc);     //主机发出复位操作并接受存在脉冲   
	Write_One_Byte(0xbe);      //跳过ROM   
	a = Read_One_Byte();       //读取低位   
	b = Read_One_Byte();       //读取高位   
	temp = b;                  
	temp <<= 8;                 //高位左移8次 
	temp = temp|a;              //读取低位  
	tt = temp*0.0625;           
	temp = tt*10+0.5;			//数据处理，四舍五入	
	return temp;
}