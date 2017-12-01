#include "ui.h"

enum _ui ui_flag;
enum _dht_opt dht_opt;



int init_flag(){
	// 从ui.h存过来的变量的状态
	ui_flag = UI_MAIN;
	dht_opt = DHT_NULL;
	return 0;
}

/*************** 
 *主界面处理
 *
 **************/

int pro_ui_main(){
	// printf("pro_ui_main：----\n");
	bmp_800_480("./main.bmp");
	show_bmp_not_800_480("./02.bmp",400,240);
	while(ui_flag ==  UI_MAIN);      // 如果在主界面没有其他操作，就一直循环在主界面
}


/*************** 
 *另一界面处理
 *
 **************/
int pro_ui_dht(){
	// printf("pro_ui_dht:----\n");
	bmp_800_480("./dht.bmp");
	while(ui_flag ==  UI_DHT){
		switch(dht_opt){
			case DHT_NULL:{
				continue; // 开始进去之后一直空转
			}
			case DHT_PRINT:{
				printf("DHT_PRINT!\n");
				break;
			}
			case DHT_EXIT:{

				break;
				// 不需要return 0吗？
			}
		}
		dht_opt = DHT_NULL; //点击一下，只能打印一次，所以要
	}
}