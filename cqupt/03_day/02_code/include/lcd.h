
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
int show_800_480(char * bmp_path);
#endif
