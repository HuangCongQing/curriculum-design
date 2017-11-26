#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#define SERVICE_IP "127.0.0.1"
int main(){

	//1. 创建socket
	int socke_fd = socket(AF_INET,SOCK_STREAM,0);

    //2. 构造服务器地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port =  htons(23333);
	addr.sin_addr.s_addr = inet_addr(SERVICE_IP);

	printf("start to connect %s \n",SERVICE_IP);
	//3. 连接服务器
	int ret = connect(socke_fd, (struct sockaddr *) &addr,sizeof(struct sockaddr));
	if(-1 == ret){
		printf("connect failed!\n");
		return -1;
	}
	printf("connect!\n");



	//4. 获取文件大小
	

	FILE *file_p = fopen("./01.bmp","r");
	if(file_p ==  NULL){
		printf("open file error!\n");
	}

	int file_size = 0;
	fseek(file_p,0,SEEK_END);//将文件指针偏移到文件末尾
	file_size = ftell(file_p);//获取当前的偏移量（偏移量就是文件大小）
	fseek(file_p,0,SEEK_SET);//将文件指针偏移到文件开头

	

	//5. 发送文件大小
	char send_buff[2048] = {0};
	int len = 0;
	sprintf(send_buff, "%d\n", file_size);
	len = send(socke_fd,send_buff,2048,0);

	//6. 读取文件内容
	//7. 发送文件内容
	
	bzero(send_buff,sizeof(send_buff));
	int total = 0;
	while((len = fread(send_buff, sizeof(char),sizeof(send_buff),file_p)) > 0)
	{

		int ret = send(socke_fd,send_buff,len,0);
		total += ret;
		printf("send:%d/%d/%d\n",len,total,file_size );
		bzero(send_buff,sizeof(send_buff));
	}


	//8. 关闭socket，关闭文件
	close(socket);
	fclose(file_p);
	// while(1){
	// 	//获取输入的消息
	// 	gets(send_buff);
	// 	len = send(socke_fd,send_buff,2048,0);
	// 	if(-1 == len){
	// 		printf("send error!\n");
	// 		return -1;
	// 	}
	// 	printf("msg send = %d\n",len);
	// 	bzero(send_buff,2048);
	
	// }
	// return 0;
}



