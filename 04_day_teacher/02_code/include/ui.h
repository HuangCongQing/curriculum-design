#ifndef _UI_H_
#define _UI_H_

#include <stdio.h>
#include "lcd.h"
enum _ui{
	UI_MAIN,
	UI_DHT
};

enum _dht_opt{
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