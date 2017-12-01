#include "ts.h"

static struct tsdev * ts_dev = NULL;
int init_ts(){
	//struct tsdev *ts_open(const char *dev_name, int nonblock);
	//1.  打开触摸屏设备，ts_open
	ts_dev = ts_open("/dev/event0",0); 
	// 配置触摸屏 ts_config
	ts_config(ts_dev);
	return 0;
}

int read_ts(struct ts_sample  *ts_p){
	if(ts_dev == NULL){
		init_ts();
	}
	printf("111\n");
	// 读取触摸屏参数 ts_read
	int ret = ts_read(ts_dev, ts_p,1); // 这里会有一个阻塞
	printf("tttt\n");

	printf("x=%d,y=%d,p=%d\n", ts_p->x,ts_p->y,ts_p->pressure);
	return ret;
}

int close_ts(){
	ts_close(ts_dev);
	ts_dev = NULL;
	return 0;
}
	
	

