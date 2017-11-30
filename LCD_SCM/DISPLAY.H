#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void scanner();
void write_time();
void read_time();
void Lcdstart();        //LCD初始界面的值
void disp_lcd();    // LCD和数码管  显示的时钟
void Star_1302();       //初始时钟启动
void all_t_read();      //所有时间的读取
void posi_show();       //LCD位选显示
void Temp_show();		//时间lcd显示
void Buz_ele_on();   //电机，蜂鸣器开断
void Seri_Comm();	   //串口数据调时间
#endif