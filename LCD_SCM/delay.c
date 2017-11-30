#include <intrins.h>
#include "delay.h"

void Delay1ms(int x)
{  int i,j;
   for(i=0;i<x;i++)
      for(j=0;j<120;j++);
}


 void Delayms(int y)
{  int i,j;
   for(i=0;i<y;i++)
      for(j=0;j<12;j++);
}
