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


int lcd_rgb_mmap(unsigned int _argb){
	//1. 打开lcd的设备文件 /dev/fb0  open();
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if (-1 == lcd_fd)
	{
		printf("open fb0 error!\n");
		return -1;
	}

	//2. 内存映射
	unsigned int *lcd_buff = (unsigned int *)mmap(NULL,800*480*4, PROT_READ|PROT_WRITE,  MAP_SHARED,lcd_fd,0);
	//3. 构造颜色信息
	for (int i = 0; i < 800*480; ++i)
	{
		lcd_buff[i] = _argb;
	}

	munmap(lcd_buff,800*480*4);
	close(lcd_fd);
	return 0;
}


int bmp_800_480(char * bmp_path){
	//1. 打开lcd的设备文件 /dev/fb0  open();
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if (-1 == lcd_fd)
	{
		printf("open fb0 error!\n");
		return -1;
	}

	//2. 内存映射
	unsigned int *lcd_buff = (unsigned int *)mmap(NULL,800*480*4, PROT_READ|PROT_WRITE,  MAP_SHARED,lcd_fd,0);
	//3. bmp

	int bmp_fd = open(bmp_path,O_RDONLY);
	lseek(bmp_fd, 54, SEEK_SET);

	char bmp_buff[800*480*3] = {0};
	ssize_t ret = read(bmp_fd,bmp_buff, 800*480*3);

	//写入
	for (int i = 0; i < 480; ++i)
	{
		for (int j = 0; j < 800; ++j)
		{
			lcd_buff[(479-i)*800+j] = (unsigned int)(bmp_buff[3*(i*800+j)] |\
								bmp_buff[3*(i*800+j)+1] <<8 |\
								bmp_buff[3*(i*800+j)+2] << 16 );
		}
	}

	close(bmp_fd);
	munmap(lcd_buff,800*480*4);
	close(lcd_fd);
	return 0;

}