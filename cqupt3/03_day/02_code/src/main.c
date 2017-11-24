#include "stdio.h"
#include "lcd.h"
#include "ts.h"


int main(int argc, char const *argv[])
{
	lcd_rgb_mmap(0x00ff);
	show_800_480("01.bmp");
	printf("cqupt\n");
	return 0;
}
