#include "stdio.h"
#include "lcd.h"


int main(int argc, char const *argv[])
{
	lcd_rgb_mmap(0x00ff);
	printf("cqupt\n");
	return 0;
}
