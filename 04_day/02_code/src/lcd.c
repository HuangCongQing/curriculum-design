#include "lcd.h"
#define BMP_W_800 800
#define BMP_H_480 480
#define BMP_PIX_SIZE 3
//bmp 解析相关的代码
#define BMP_H_INFO 54
#define BMP_LIST_SIZE 10
#define BMP_FILE_NAME_LEN 255
static char bmp_list[BMP_LIST_SIZE][BMP_FILE_NAME_LEN] = {0};
static int bmp_list_num = 0;

#define LCD_W 800
#define LCD_H 480
#define LCD_RED 0x00ff0000
#define LCD_PIX_SIZE 4

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

int get_bmp_w_h(char * bmp_info_buff,unsigned int *w,unsigned int *h){

	//1. 检查传入的指针是否为空
	if(bmp_info_buff == NULL || w == NULL || h == NULL){
		printf("pos NULL\n");
		return -1;
	}
	//2. 偏移到图片的宽度信息(14+4 字节)
	//3. 偏移到图片的高度信息
	//获取宽度信息,转换大小端（bmp格式是大端，linux是小端）
	unsigned int _bmp_w = *(unsigned int *)(bmp_info_buff + 18);   //18 偏移到图片的宽度信息的偏移量
	unsigned int _bmp_h = *(unsigned int *)(bmp_info_buff + 18 + 4); //4 偏移过bmp的宽度信息
	
	printf("get_bmp_w_h: w = %d, h = %d\n",_bmp_w, _bmp_h);
	
	//4. 赋值给*w，以及*h
	*w = _bmp_w;
	*h = _bmp_h;

	return 0;
}

int proc_bmp_not_800_480(char *bmp_path,unsigned int * lcd_buff,unsigned int x,unsigned int y)
{

	//1. 打开图片
	int fd_bmp = open(bmp_path,O_RDONLY);
	if(-1 == fd_bmp)
	{
		printf("open %s error\n",bmp_path);
		return -1;
	}



	//2. 获取图片的长宽
	char bmp_info_buff[BMP_H_INFO] = {0};
	read(fd_bmp, bmp_info_buff,BMP_H_INFO);
	
	unsigned int bmp_w = 0; 
	unsigned int bmp_h = 0;
	get_bmp_w_h(bmp_info_buff,&bmp_w,&bmp_h);

	//3. 偏移过bmp头信息
	int ret = lseek(fd_bmp,54,SEEK_SET);
	if(-1 == ret)
	{
		printf("lseek error!\n");
		return -1;
	}

	//读取图片信息
	
	int fill_zero_per_line = 4 - ((bmp_w*BMP_PIX_SIZE)%4);//计算bmp每行进行4字节对其后 对每行信息进行填充的0的字节数。
	if(fill_zero_per_line == 4){
		fill_zero_per_line =0;
	}
	char buff[BMP_W_800 * BMP_H_480 * BMP_PIX_SIZE] = {0};
	read(fd_bmp, buff,bmp_w * bmp_h * BMP_PIX_SIZE +  bmp_h * fill_zero_per_line);

	unsigned int _bmp_w = 0;
	unsigned int _bmp_h = 0;
	if(bmp_h + y > BMP_H_480){
		_bmp_h = BMP_H_480 - y;
	}else{
		_bmp_h = bmp_h;
	}

	if(bmp_w + x > BMP_W_800){
		_bmp_w = BMP_W_800 - x;
	}else{
		_bmp_w = bmp_w;
	}
	//4. 在对应的x，y坐标上刷入图片信息
	
	int i = 0;
	int j = 0;
	for(i = 0 ;i < _bmp_h; i++) 
	{
		for(j = 0 ;j < _bmp_w; j++)
		{
			lcd_buff[(_bmp_h - i+y)*BMP_W_800 + (j+x)] = 0x0 <<24 |buff[(i*bmp_w+j)*BMP_PIX_SIZE + i*fill_zero_per_line  ] << 0 | \
										buff[(i*bmp_w+j)*BMP_PIX_SIZE + i*fill_zero_per_line + 1] <<8 | \
										buff[(i*bmp_w+j)*BMP_PIX_SIZE + i*fill_zero_per_line + 2] << 16;
			
		}
	}
	printf("fill_zero_per_line = %d\n", fill_zero_per_line);
	//5. 关闭图片
	close(fd_bmp);

	return 0;
}




int show_bmp_not_800_480(char * bmp_path,int x,int y){
	//打开设备文件/dev/fb0
	int fd_lcd = open("/dev/fb0",O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open /dev/fb0 error!\n");
		return -1;
	}
	//映射为内存mmap
	unsigned int * buff_lcd = NULL;
	buff_lcd  = (unsigned int *)mmap(NULL,LCD_W * LCD_H * LCD_PIX_SIZE, PROT_WRITE, MAP_SHARED,\
			fd_lcd, 0);
	if(buff_lcd == MAP_FAILED)
	{
		printf("mmap error \n");
		return -1;
	}
	//读取图片信息并写入
	//unsigned int buff_lcd[LCD_W * LCD_H] = {0};
	proc_bmp_not_800_480("02.bmp",buff_lcd,x,y);//刷入小图信息
	

	//关闭/dev/fb0
	munmap(buff_lcd,LCD_W * LCD_H * LCD_PIX_SIZE);
	if(close(fd_lcd))
	{
		printf("close fd_lcd error！\n");
		return -1;
	}
	return 0;
	
}
