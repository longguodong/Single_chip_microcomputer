#include <reg51.h>
#include <intrins.h>
#include "scq.h"
#include "delay.h"
#include "display.h"
#include "keybord.h"
#include "ds18b20.h"
#include "iic.h"
#include "ds1302.h"
#include"lcd.h"


 /*T1ɨ������,���Բ���*/
#define count_M2 250 //T1��Mode2��ֵ0.25ms
#define TH_M2 (256-count_M2)
#define TL_M2 (256-count_M2)
int  count_T1=0;

/*T0��ʱ����*/
#define count_M1 50000 //T0��Mode1��ֵ50ms
#define TH_M1 (65536-count_M1)/256
#define TL_M1 (65536-count_M1)%256
int  count_T0=0;
int tem_T=0,tt;//�¶�3���ʱ




main()
{

 	 IE=0x92;	//1001 0010,����ES���У�TF0�ж�
     TMOD=0X21;//0010 0001 T0����Mode1,T1����Mode2
	 TH0=TH_M1;
     TL0=TL_M1;
      TR0=1;   //����T0
	/*****************************
	����ͨ���������
	***************************/
	  TH1=0XFD;//������9600
      TL1=0XFD;
      REN=1;
      SM0=0;
      SM1=1;
	  TR1=1;
	 Close_LED();
	 Close_SEG();	
     No_buzzrelay();  //�رշ�����
	 LcdInit();
	 Lcdstart();
	 Star_1302();
	 

	 while(1)
  {	  	 
  
     Buz_ele_on();
     disp_lcd();
    if(tt==3)
	 {
	 Temp_show();
	 }
	
   }	

}

 
 void T_0(void) interrupt 1  
{
   TH0=TH_M1;
   TL0=TL_M1;
   if(++count_T0==20)
   {
     tem_T++;
	 if(tem_T==4)
	   { 
	     tem_T=0;
	   }
	   count_T0=0;
   }
   tt=tem_T;
}




