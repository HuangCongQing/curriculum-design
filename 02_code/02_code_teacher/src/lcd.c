#include "lcd.h"

/*
功能:将屏幕的颜色改为_argb的颜色
_argb：ARGB格式的颜色信息。
*/
int lcd_rgb(unsigned int _argb){
	//1. 打开lcd的设备文件 /dev/fb0  open();
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if (-1 == lcd_fd)
	{
		printf("open fb0 error!\n");
		return -1;
	}

	unsigned int buff[800*480] = {0};
	//3. 构造颜色信息
	for (int i = 0; i < 800*480; ++i)
	{
		buff[i] = _argb;
	}

	ssize_t ret = write(lcd_fd, buff, 800*480*4);
	if(-1 == ret){
		printf("write error\n");
		return -1;
	}

	close(lcd_fd);
	return 0;
}

