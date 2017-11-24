#include "ts.h"

//处理主界面的触摸坐标
int pro_ts_ui_main(struct ts_sample ts_xy){

	//判断是否触摸到mp3图标的位置
	if(ts_xy.x > 100 && ts_xy.x < 200 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	{
		ui_status = UI_MUSIC;
		return 0;
	}

	//判断是否触摸到图片播放 图标的位置
	if(ts_xy.x > 300 && ts_xy.x < 400 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	{
		ui_status = UI_PIC;
		return 0;
	}

	//判断是否触摸到xxx图标的位置
	// if(ts_xy.x > 300 && ts_xy.x < 400 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	// {
	// 	ui_status = UI_PIC;
	// 	return 0;
	// }
	
}

//处理图片界面的触摸坐标
int pro_ts_ui_pic(struct ts_sample ts_xy)
{
	if(ts_xy.x > 300 && ts_xy.x < 400 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	{
		pic_status = PIC_SHOW_PRE_PIC;
		return 0;
	}

	if(ts_xy.x > 300 && ts_xy.x < 400 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	{
		pic_status = PIC_SHOW_NEX_PIC;
		return 0;
	}

	if(ts_xy.x > 300 && ts_xy.x < 400 && ts_xy.y > 100 &&ts_xy.y < 200 &&ts_xy.pressure > 0)
	{
		pic_status = PIC_EXIT;
		ui_status =  UI_MAIN;
		return 0;
	}
	
}


int get_ts()
{
	//1.打开触摸屏设备文件  ts_open()
	struct tsdev *ts = ts_open("/dev/event0", 0);
	struct ts_sample sample;

	//2.配置触摸屏 ts_config()
	ts_config(ts);

	//3.读取触摸屏参数 ts_read()
	while(1)
	{
		ts_read(ts, &sample, 1); //这里会有一个阻塞
		printf("x = %d, y = %d, pressure = %d\n", sample.x, sample.y, sample.pressure);

		switch(ui_status){
			case UI_MAIN:
			{
				pro_ts_ui_main(sample);
				break;
			}
			case UI_PIC:
			{
				pro_ts_ui_pic(sample);
				break;
			}
			case UI_MUSIC:
			{
				//pro_ts_ui_music();
				break;
			}
			case UI_REC:
			{
				//pro_ts_ui_rec();
				break;
			}

		}
	}

	//4.关闭触摸屏设备文件 ts_close()
	ts_close(ts);

}

