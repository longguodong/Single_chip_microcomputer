#include <reg51.h>
#include "scq.h"
#include "delay.h"


void Close_LED()
{
   P2=(P2&=0x1f)|0x90;    //0x1f=0001 1111   //0x9f=1001 1111 P2ѡ��Y4������
   P0=0xff;
   P2&=0x1f;    //0x1f=0001 1111
}
				  
void No_buzzrelay()
{
   P2=(P2&=0x1f)|0xb0;  //0x1f=0001 1111 ;0xbf=1011 1111  P2ѡ��Y5������
   P0=0xaf;  //0xaf=1010 1111  �رռ̵����ͷ�����
   Delay1ms(2);
   P2&=0x1f;  //0x1f=0001 1111	P2�������ر�

}

void Close_SEG()
{
   P2=(P2&=0x1f)|0xd0;//Y6	ɨ�� 
   P2=0xFf; 
   Delay1ms(2);
   P2&=0x1f;  

}


