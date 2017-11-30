#include "ui.h"

enum _ui ui_flag;
enum _dht_opt dht_opt;



int init_flag(){
	ui_flag = UI_MAIN;
	dht_opt = DHT_NULL;
	return 0;
}



int pro_ui_main(){
	// printf("pro_ui_main：----\n");
	bmp_800_480("./main.bmp");
	show_bmp_not_800_480("./02.bmp",400,240);
	while(ui_flag ==  UI_MAIN);
}

int pro_ui_dht(){
	// printf("pro_ui_dht:----\n");
	bmp_800_480("./dht.bmp");
	while(ui_flag ==  UI_DHT){
		switch(dht_opt){
			case DHT_NULL:{
				continue;
			}
			case DHT_PRINT:{
				printf("DHT_PRINT!\n");
				break;
			}
			case DHT_EXIT:{

				break;
			}
		}
		dht_opt = DHT_NULL;
	}
}