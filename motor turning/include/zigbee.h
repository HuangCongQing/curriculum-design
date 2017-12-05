#ifndef __ZIGBEE_H_
#define __ZIGBEE_H_

// 包含头文件
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

extern char tem_buf[20];

int send_msg(char *cmd_buf);

int get_tem_hum();
void * _get_tem_pthread_function(void * arg);
int create_tem_pthread();
#endif