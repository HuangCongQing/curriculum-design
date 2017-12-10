
#ifndef _LCD_H_
#define _LCD_H_


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
int lcd_rgb(unsigned int _argb);
int lcd_rgb_mmap(unsigned int _argb);
int bmp_800_480(char * bmp_path);
int show_bmp_not_800_480(char * bmp_path,int x,int y,int z);
int speed;
#endif
