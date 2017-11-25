#include "stdio.h"
#include "lcd.h"
#include "ts.h"

int main(int argc, char const *argv[])
{
	lcd_rgb_mmap(0x00ff);
	bmp_800_480("01.bmp");
	show_bmp_not_800_480("./02.bmp",400,240);
	test();
	printf("cqupt\n");
	return 0;
}
