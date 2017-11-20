/*
* @Author: hasee
* @Date:   2017-11-20 16:51:18
* @Last Modified by:   hasee
* @Last Modified time: 2017-11-20 16:57:52
*/





#include <stdio.h>
#include <lcd.h>
void main(int argc, char const *argv[])
{
	lcd_rgb(unsigned int _argb)
	{

		int lcd_fb=open("/dev/fb0",O_RDWR);
	
		if (-1==lcd_fb)
		{
			printf("open fb0 error\n");
			return -1;
		}

		unsigned int buff[800*480]={0};
		for (int i = 0; i < 800*480; ++i)
		{
			buff[i]=_argb
		}

		ssize_t ret = write(lcd_fb,buff,800*480*4)；
		if (-1==ret)
		{
			printf("write error\n", );
			return -1;
		}
	return 0;
}

// 1. 打开LED设备文件  /dev/fb0

// 2. unsigned int buff[800*480] = {0};

// 3. 构造颜色信息

// for (int i = 0;i< 800*480; ++i){
//  buff[i] = 0X00ff0000;

// }
// 4. write()
// 4. close()