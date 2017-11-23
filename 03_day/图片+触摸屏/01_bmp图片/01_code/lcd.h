#ifndef __LCD_H__
#define __LCD_H__


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "bmp.h"
#include <sys/mman.h>
#include <errno.h>

int show_color(unsigned int rgb_hex);
int show_bmp(char * bmp_path);
int show_bmp_not_800_480(char * bmp_path,int x,int y);
#endif