#include <reg51.h>
#include "delay.h"
#include "keybord.h"
#include "ds1302.h"
//sbit KEY4=P3^3;
//sbit KEY5=P3^2;
sbit KEY6=P3^1;
sbit KEY7=P3^0;	    
int s=0,h=0,m=0;
int d=0,mo=0,y=0;	  
	
unsigned char key1()  //秒钟加减
 {	
 //加时间 
 if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 s++;
		 if(s==60)
		 s=0; 
	   }
  	 }

 if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 s--;
		 if(s<0)
		 s=59; 
	   }
  	 }

	 
    return s; 
 }


 unsigned char key2()  //分钟加减
 {	
 //加时间 
  if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 m++;
		 if(m==60)
		 m=0; 
	   }
  	 }

  if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 m--;
		 if(m<0)
		 m=59; 
	   }
  	 }

	 
    return m; 
}




 unsigned char key3() //小时加减
 {	
 //加时间 
  if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 h++;
		 if(h==24)
		 h=0; 
	   }
  	 }

  if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 h--;
		 if(h<0)
		 h=23; 
	   }
  	 }

	 
    return h; 
 }



 unsigned char key4() //日加减
 {	
 //加时间 
  if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 d++;
		 if(d==32)
		 d=0; 
	   }
  	 }

  if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 d--;
		 if(d<0)
		 d=31; 
	   }
  	 }

	 
    return d; 
 }


unsigned char key5() //月加减
 {	
 //加时间 
  if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 mo++;
		 if(mo==13)
		 mo=0; 
	   }
  	 }

  if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 mo--;
		 if(mo<0)
		 mo=12; 
	   }
  	 }

	 
    return mo; 
}


unsigned char key6() //年加减
 {	
 //加时间 
  if(KEY6==0)
	{
       Delay1ms(20);
	   while(KEY6==0)
	  {
	     while(KEY6==0);
		 y++;
		 if(y==51)
		 y=0; 
	   }
  	 }

  if(KEY7==0)
	{
	  //减时间
       Delay1ms(20);
	   while(KEY7==0)
	  {
	     while(KEY7==0);
		 y--;
		 if(y<0)
		 y=49; 
	   }
  	 }

	 
    return y; 
}
//struct Time
//{
//   unsigned char second;
//   unsigned char minute;
//   unsigned char hour;
//   unsigned char day;
//   unsigned char month;
//   unsigned char year;
//}  ctime;
