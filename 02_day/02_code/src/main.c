#include "stdio.h"
#include "lcd.h"


// int main(int argc, char const *argv[])
// {
// 	lcd_rgb_mmap(0x00ff);
// 	printf("cqupt\n");
// 	return 0;
// }


// 每隔一秒变换一种颜色 ----------执行文件loop
int main(int argc, char const *argv[])
{
	// 一种方法   sleep(),linux函数，默认就有
	// while(1){
	// 	lcd_rgb_mmap(0x0000ff);
	// 	sleep(1);
	// 	lcd_rgb_mmap(0x00ff00);
	// 	sleep(1);
	// 	lcd_rgb_mmap(0xff0000);
	// 	sleep(1);
	// }

	// 直接显示三行颜色
	
	lcd_rgb_mmap3(0x0000ff,0x00ff00,(0xff0000);
}

