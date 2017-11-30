#include "stdio.h"
#include "test.h"


int main(int argc, char const *argv[])
{
	test(1);
	printf("cqupt\n");
	return 0;
}


1. 打开lcd的设备文件 /dev/fb0  open();
2. unsigned int buff[800*480] = {0};
3. 构造颜色信息
for (int i = 0; i < 800*480; ++i)
{
	buff[i] = 0xff0000;
}

4. write();
5. close()

