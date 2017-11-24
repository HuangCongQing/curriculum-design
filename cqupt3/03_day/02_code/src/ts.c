#include "ts.h"


int test(){

	struct tsdev * ts_dev = ts_open("/dev/event0",0);

	ts_config(ts_dev);

	struct ts_sample ts_p;
	while(1){

			ts_read(ts_dev, &ts_p, 1);
			printf("x=%d,y=%d,p=%d\n",ts_p.x,ts_p.y,ts_p.pressure);
	}

}