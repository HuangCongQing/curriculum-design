#ifndef _UI_H_
#define _UI_H_

#include <stdio.h>
#include "lcd.h"
enum _ui{  // 主界面的flag
	UI_MAIN,
	UI_DHT,
	UI_MOT //电机
};

enum _dht_opt{  // 跳转界面 操作位
	DHT_EXIT,
	DHT_NULL,
	DHT_PRINT
};
enum _mot_opt{  // 反转电机
	MOT_EXIT,
	MOT_NULL,
	MOT_PRINT
};
extern enum _ui ui_flag;
extern enum _dht_opt dht_opt;
extern enum _mot_opt mot_opt;// 电机
int pro_ui_dht();
int pro_ui_mot(); // 反转电机
int pro_ui_main();
int init_flag();



#endif