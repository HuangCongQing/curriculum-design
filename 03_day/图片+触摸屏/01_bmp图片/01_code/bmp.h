#ifndef  __BMP_H__
#define __BMP_H__


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int proc_bmp_800_480(char *bmp_path,unsigned int * lcd_buff);
int find_bmp(char * bmp_path);
void test();
#endif