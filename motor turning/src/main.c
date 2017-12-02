/*
 * @Author: HCQ 
 * @Date: 2017-11-26 19:43:23 
 * @Last Modified by: HCQ
 * @Last Modified time: 2017-11-30 21:10:59
 * 
 * 
 * 缩写介绍
 *  ts    touchscreen 触摸屏设备
 *  LCD   液晶显示屏（liquid crystal display）
 * ui.h   定义每个界面的一些变量
 */
#include "stdio.h"
#include "lcd.h"
#include "ts.h"
#include <pthread.h>
#include <unistd.h>
#include "ui.h"

// 处理主界面的触摸坐标
int pro_ts_main(struct ts_sample  *ts_p){
	// printf("pro_ts_main:----\n");
	// 判断是否触摸到此区域
	if(ts_p->x > 111 && ts_p->x < 282 && ts_p->y > 172 && ts_p->y < 314 && ts_p->pressure >0){
		ui_flag = UI_DHT;  // 设置flag跳转界面
	}

	return 0;

}

int pro_ts_dht(struct ts_sample  *ts_p){

	// printf("pro_ts_dht:----\n");
	if (ts_p->x >0 && ts_p->x < 200 && ts_p->y > 0 && ts_p->y < 100 && ts_p->pressure >0)
	{
		ui_flag = UI_MAIN;
	}
	if (ts_p->x >400 && ts_p->x < 800 && ts_p->y > 240 && ts_p->y < 480 && ts_p->pressure >0)
	{
		dht_opt = DHT_PRINT; 
	}
}

void * start_routine (void * arg){
	

	struct ts_sample  ts_p;
	while(1){
		read_ts(&ts_p);  //阻塞，等待点击，调用ts.c中函数
		switch(ui_flag){
			case UI_MAIN:{
				// 处理主界面的任务
				pro_ts_main(&ts_p);// 把坐标传进去
				break;  // ui.c中这个函数循环终止，break跳出，然后在while(1)又循环一次
			}
			case UI_DHT:{
				pro_ts_dht(&ts_p);
				break;
			}

		}
	}

	return NULL;

}


// 主函数主函数主函数主函数主函数主函数主函数主函数主函数主函数主函数
int main(int argc, char const *argv[])
{
	init_flag();// ui.c
	pthread_t thread_ts;
	// 创建主线程
	pthread_create(&thread_ts, NULL,start_routine,NULL);
	
	while(1){
		switch(ui_flag){
			case UI_MAIN:{
				pro_ui_main(); // 去主界面
				break;
			}
			case UI_DHT:{
				pro_ui_dht(); // 去另一界面
				break;
			}
		}
		
	}
	return 0;
}
