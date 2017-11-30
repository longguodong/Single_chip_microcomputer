#include <reg51.h>
#include "scq.h"
#include "delay.h"


void Close_LED()
{
   P2=(P2&=0x1f)|0x90;    //0x1f=0001 1111   //0x9f=1001 1111 P2Ñ¡ÔñY4Ëø´æÆ÷
   P0=0xff;
   P2&=0x1f;    //0x1f=0001 1111
}
				  
void No_buzzrelay()
{
   P2=(P2&=0x1f)|0xb0;  //0x1f=0001 1111 ;0xbf=1011 1111  P2Ñ¡ÔñY5Ëø´æÆ÷
   P0=0xaf;  //0xaf=1010 1111  ¹Ø±Õ¼ÌµçÆ÷ºÍ·äÃùÆ÷
   Delay1ms(2);
   P2&=0x1f;  //0x1f=0001 1111	P2Ëø´æÆ÷¹Ø±Õ

}

void Close_SEG()
{
   P2=(P2&=0x1f)|0xd0;//Y6	É¨Ãè 
   P2=0xFf; 
   Delay1ms(2);
   P2&=0x1f;  

}


