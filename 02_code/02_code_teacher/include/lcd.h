
#ifndef _LCD_H_
#define _LCD_H_


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int lcd_rgb(unsigned int _argb);
#endif


 // #include <sys/mman.h>

 //       void *mmap(void *addr, size_t length, int prot, int flags,
 //                  int fd, off_t offset);
 //       int munmap(void *addr, size_t length);
