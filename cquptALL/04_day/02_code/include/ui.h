#ifndef _UI_H_
#define _UI_H_

#include <stdio.h>
#include "lcd.h"
enum _ui{  // 主界面的flag
	UI_MAIN,
	UI_DHT
};

enum _dht_opt{  // 跳转界面 操作位
	DHT_EXIT,
	DHT_NULL,
	DHT_PRINT
};
extern enum _ui ui_flag;
extern enum _dht_opt dht_opt;
int pro_ui_dht();
int pro_ui_main();
int init_flag();



#endif