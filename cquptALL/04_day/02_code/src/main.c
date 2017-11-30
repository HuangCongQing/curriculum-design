#include "stdio.h"
#include "lcd.h"
#include "ts.h"
#include <pthread.h>
#include <unistd.h>
#include "ui.h"


int pro_ts_main(struct ts_sample  *ts_p){
	// printf("pro_ts_main:----\n");
	if(ts_p->x > 111 && ts_p->x < 282 && ts_p->y > 172 && ts_p->y < 314 && ts_p->pressure >0){
		ui_flag = UI_DHT;
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
		read_ts(&ts_p);
		switch(ui_flag){
			case UI_MAIN:{
				pro_ts_main(&ts_p);
				break;
			}
			case UI_DHT:{
				pro_ts_dht(&ts_p);
				break;
			}

		}
	}

	return NULL;

}



int main(int argc, char const *argv[])
{
	init_flag();
	pthread_t thread_ts;
	pthread_create(&thread_ts, NULL,start_routine,NULL);
	// printf("%d\n",ui_flag);
	printf("114444441\n");
	while(1){
		switch(ui_flag){
			case UI_MAIN:{
				pro_ui_main();
				break;
			}
			case UI_DHT:{
				pro_ui_dht();
				break;
			}
		}
		
	}
	return 0;
}
