#include <reg51.h>
#include "delay.h"
#include "display.h"
#include "keybord.h"
#include "ds1302.h"
#include "ds18b20.h"
#include"lcd.h"
sbit KEY4=P3^3;
sbit KEY5=P3^2;
sbit KEY7=P3^0;	 
long tempdate,tem_f_d; //温度
int Tim=0,Ser_com[14]; //串口数据传输
unsigned  int  flag=1;position=1; 
unsigned char  j,pl=0;
unsigned char  disp[14];
unsigned char  bj[6]={0,0,0,0,0,0};
unsigned char  keym1,keym2,keym3,keym4,keym5,keym6;
unsigned char  second,minute,hour,day,month,year;
unsigned char  ds1302_ad_w[6]=
{
   0x80,0x82,0x84,0x86,0x88,0x8c
};



/*****************************************************************
   LCD初始界面的值
****************************************************************/
void Lcdstart()
{	 
	 LcdWriteCom(0X80);
	 LcdWriteData(0X30+2);
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteData('-');
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteData('-');
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 	
	 LcdWriteCom(0X80+0x40);
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteData('-');
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteData('-');
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+0);
	 LcdWriteCom(0xc0); 
}


/*****************************************************************
   初始时钟启动
****************************************************************/
void Star_1302()
{  
	for(j=0;j<6;j++)
   Ds1302_Single_Byte_Write(ds1302_ad_w[j],0x00);

}


 /*****************************************************************
   所有时间的读取
****************************************************************/
 void all_t_read()
 {
    Ds1302_Single_Byte_Write(0x8e,0x00);
	second=Ds1302_Single_Byte_Read(0x81);
	disp[0]=second%16;
	disp[1]=second/16;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	minute=Ds1302_Single_Byte_Read(0x83);
	disp[2]=16;
	disp[3]=minute%16;
	disp[4]=minute/16;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	hour=Ds1302_Single_Byte_Read(0x85);
	disp[5]=16;
	disp[6]=hour%16;
	disp[7]=hour/16;
	 Ds1302_Single_Byte_Write(0x8e,0x00);
     day=Ds1302_Single_Byte_Read(0x87);
	 disp[8]=day%16;
	 disp[9]=day/16;
	 Ds1302_Single_Byte_Write(0x8e,0x00);
	 month=Ds1302_Single_Byte_Read(0x89);
	 disp[10]=month%16;
	 disp[11]=month/16;
	 Ds1302_Single_Byte_Write(0x8e,0x00);
	 year=Ds1302_Single_Byte_Read(0x8d);
	 disp[12]=year%16;
	 disp[13]=year/16;
	 LcdWriteCom(0X80);
//	   LcdWriteCom(0X08);//实现闪烁的效果
//	   Delay1ms(1000);
//	    LcdWriteCom(0X0c);
	 LcdWriteData(0X30+2);
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+disp[13]);
	 LcdWriteData(0X30+disp[12]);
	 LcdWriteData('-');
	 LcdWriteData(0X30+disp[11]);
	 LcdWriteData(0X30+disp[10]);
	 LcdWriteData('-');
	 LcdWriteData(0X30+disp[9]);
	 LcdWriteData(0X30+disp[8]);

	 LcdWriteCom(0X80+0x40);
	 LcdWriteData(0X30+disp[7]);
	 LcdWriteData(0X30+disp[6]);
	 LcdWriteData('-');
	 LcdWriteData(0X30+disp[4]);
	 LcdWriteData(0X30+disp[3]);
	 LcdWriteData('-');
	 LcdWriteData(0X30+disp[1]);
	 LcdWriteData(0X30+disp[0]);

	 LcdWriteCom(0xc0); 

 }



/*****************************************************************
   LCD位选显示
****************************************************************/
 void posi_show()
 {
     LcdWriteCom(0X80);
	 LcdWriteData(0X30+2);
	 LcdWriteData(0X30+0);
	 LcdWriteData(0X30+keym6/10);
	 LcdWriteData(0X30+keym6%10);
	 LcdWriteData('-');
	 LcdWriteData(0X30+keym5/10);
	 LcdWriteData(0X30+keym5%10);
	 LcdWriteData('-');
	 LcdWriteData(0X30+keym4/10);
	 LcdWriteData(0X30+keym4%10);

	 LcdWriteCom(0X80+0x40);
	 LcdWriteData(0X30+keym3/10);
	 LcdWriteData(0X30+keym3%10);
	 LcdWriteData('-');
	 LcdWriteData(0X30+keym2/10);
	 LcdWriteData(0X30+keym2%10);
	 LcdWriteData('-');
	 LcdWriteData(0X30+keym1/10);
	 LcdWriteData(0X30+keym1%10);
	 LcdWriteCom(0xc0);	
	
   
 }

/*****************************************************************
   LCD温度的显示
****************************************************************/
void Temp_show()
{
      tempdate=Get_Tmp();
	  LcdWriteCom(0X80+0x40+0x0b);
	  LcdWriteData(0X30+tempdate/100);
	  LcdWriteData(0X30+(tempdate%100)/10);
	  LcdWriteData('.');
	  LcdWriteData(0X30+tempdate%100%10);
	  LcdWriteData('C');
	  LcdWriteCom(0xc0);	
 
}

 /*****************************************************************
 蜂鸣器和电机的开断
****************************************************************/
void Buz_ele_on()
{
    tem_f_d=Get_Tmp();
  if(((tem_f_d/100)*10+(tem_f_d%100/10))>=25)
	 {
	   P2=(P2&=0x1f)|0xb0; // P2选择Y5锁存器
       P0=0x6f;  //0xaf=0110 1111
	   P2&=0x1f;
	 }
	 else
	 {
	  P2=(P2&=0x1f)|0xb0; // P2选择Y5锁存器
      P0=0x0f;  //0xaf=1010 1111
	  P2&=0x1f; 
	 }

}

 /*****************************************************************
   串行口中断调时间
****************************************************************/
void Seri_Comm()
{  	 
     unsigned char serial[6],sm=1;
	 for(j=0;j<6;j++)
	 { 
	     
	       serial[j]=Ser_com[j+sm]*10+Ser_com[j+sm+1];
	       Ds1302_Single_Byte_Write(ds1302_ad_w[5-j],((serial[j]/10)<<4|(serial[j]%10)));
		   sm++;
		   if(sm==7)
		     sm=1;
	 }
}








/*****************************************************************
   LCD显示的时钟
****************************************************************/
void disp_lcd()
{  	
     if(KEY4==0)
	{
       Delay1ms(40);
	   while(KEY4==0)
	  {
	     while(KEY4==0);
		   flag++;
		 if(flag==3)
		   flag=1; 
	   }
  	 }



//主显示区
 if(flag==1)
 {
   all_t_read();
   if(KEY5==0)
   Seri_Comm();
   position=1;


  }    

 if(flag==2)
 {
	 //调时间位选
	 if(KEY5==0)
	{
       Delay1ms(40);
	   while(KEY5==0)
	  {
	     while(KEY5==0);
		   position++;
		 if(position==8)
		   position=1; 
	   }
  	 }
 //调秒位，位选
   if(position==1)
   { 
	 keym1=key1();
	 bj[0]=keym1;
     posi_show();
	 Delay1ms(30);
	 LcdWriteCom(0X80+0x40+0x06);
  	 LcdWriteData(0X30+0xff);
	 LcdWriteData(0X30+0xff);
	 LcdWriteCom(0Xc0);  
	 
	}
//调分钟位，位选
	if(position==2)
	{ 
	 keym2=key2();
	 bj[1]=keym2;  
     posi_show(); 
	 Delay1ms(30);
	 LcdWriteCom(0X80+0x40+0x03);
  	 LcdWriteData(0X30+0xff);
	 LcdWriteData(0X30+0xff);
	 LcdWriteCom(0Xc0); 
	}

//调小时位，位选
		if(position==3)
	{ 
	 keym3=key3();
	 bj[2]=keym3;  
	 posi_show();
	 Delay1ms(30);
	 LcdWriteCom(0X80+0x40);
  	 LcdWriteData(0X30+0xff);
	 LcdWriteData(0X30+0xff);
	 LcdWriteCom(0Xc0); 
}

	//调日，位选
  if(position==4)
	{
	    keym4=key4();
	    bj[3]=keym4;
     	posi_show(); 
		LcdWriteCom(0X80+0x08);
		LcdWriteData(0X30+0xff);
	    LcdWriteData(0X30+0xff);
		LcdWriteCom(0Xc0);	
	 }  


   //调月，位选
  if(position==5)
	{
	    keym5=key5();
	    bj[4]=keym5;
        posi_show();
		LcdWriteCom(0X80+0x05);
		LcdWriteData(0X30+0xff);
	    LcdWriteData(0X30+0xff);
		LcdWriteCom(0Xc0);	
			 
	 }  

	  //调年，位选
  if(position==6)
	{
	    keym6=key6();
	    bj[5]=keym6;
        posi_show();
		LcdWriteCom(0X80);
		LcdWriteData(0X30+0xff);
	    LcdWriteData(0X30+0xff);
	    LcdWriteData(0X30+0xff);
	    LcdWriteData(0X30+0xff);
		LcdWriteCom(0Xc0);	
	 }

	 //确认时间，并显示
//  if(position==7&&KEY4==0)
    if(position==7&&KEY7==0)
	 {     //	秒，分，时,日，月，年
//	   if(KEY4==0)
//	   {
//	     while(KEY4==0)
//	        { 
//			   Delay1ms(30);
//			   while(KEY4==0);
//			   pl++;
//			   if(pl==2)
//			   pl=1;
//	         }
//	   }
//	   if(pl==1)
//	   {
	      for(j=0;j<6;j++)
         Ds1302_Single_Byte_Write(ds1302_ad_w[j],((bj[j]/10)<<4|(bj[j]%10)));
//	   }
	   }

 }
 }	





 void Serial_Com(void) interrupt 4
{
  if(RI==1)
  {
    RI=0;
	Ser_com[Tim]=SBUF-0x30;
	Tim++;
   if(Tim==13)
   {
	Tim=1;
	}

  }
} 
