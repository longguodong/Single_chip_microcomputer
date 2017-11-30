#include "ds18b20.h"
#include <intrins.h>

long temp; 
void delay(unsigned char i)				   //����ʱ
{
	while(--i);
}

void Init_Ds18b20(void)     //DS18B20��ʼ��send reset and initialization command
{

DQ=1;			  //���߶�������
delay(1); 
DQ=0;			  //���������͵�ƽ
delay(250);	//�͵�ƽ����800us���ң����������û�е͵�ƽ,
DQ=1;
delay(100); 	//�ȴ�120us
			               
}

uchar Read_One_Byte()       //��ȡһ���ֽڵ�����read a byte date

{
	uchar i   = 0;
	uchar dat = 0;
	for(i=8;i>0;i--)  //��ȡ8�Σ��ӵ͵���
	{
		DQ = 0;        //��������1us���ͷ�         
		_nop_();                
		dat >>= 1;       //��������      
		DQ = 1;          //�ͷ�����  
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
		DQ = 0;        //��������1us                
		_nop_();           
		DQ = dat&0x01;  //������д������             
		delay(10);      //����60us            
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
	Write_One_Byte(0xcc);     //����������λָ��    
	Write_One_Byte(0x44);     //����ROM 
	Init_Ds18b20();           //�ٴγ�ʼ��    
	Write_One_Byte(0xcc);     //����������λ���������ܴ�������   
	Write_One_Byte(0xbe);      //����ROM   
	a = Read_One_Byte();       //��ȡ��λ   
	b = Read_One_Byte();       //��ȡ��λ   
	temp = b;                  
	temp <<= 8;                 //��λ����8�� 
	temp = temp|a;              //��ȡ��λ  
	tt = temp*0.0625;           
	temp = tt*10+0.5;			//���ݴ�����������	
	return temp;
}