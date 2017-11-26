#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int main(){
	
	//1. 创建socket
	int socked_fd = socket(AF_INET,SOCK_STREAM,0);

	//2. 构造绑定的地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port =  htons(23333);
	addr.sin_addr.s_addr =INADDR_ANY;// inet_addr("127.0.0.1");//这里有坑

	//3. 绑定地址
    bind(socked_fd, (struct sockaddr *) &addr,sizeof(struct sockaddr));

	//4. 监听
	listen(socked_fd,5);

	//5. accept
	struct sockaddr addr_recv;
	socklen_t addrlen = 0;
	int con_fd =  accept(socked_fd,&addr_recv,&addrlen);
	printf("client connect\n");

	//6. 收文件的大小
	char msg_buff[2048] = {0};
	ssize_t msg_len = 0;
	msg_len = recv(con_fd, msg_buff, 2048, 0);

	//7. 转换收到的文件大小为整形
	int file_size = 0;
	sscanf(msg_buff,"%d",&file_size);
	printf("file_size = %d\n", file_size);

	//8. 开始接收文件内容
	//创建一个文件
	FILE *file_p = fopen("./recv.bmp","w+");

	bzero(msg_buff,sizeof(msg_buff));
	int total_len = 0;
	while((msg_len = recv(con_fd,msg_buff,2048,0)) > 0)
	{
		
		fwrite(msg_buff, sizeof(char),msg_len,file_p);
		total_len += msg_len;
		printf("recv:%d/%d\n", total_len,file_size);
		if(total_len == file_size)
		{
			break;
		}
			
		bzero(msg_buff,sizeof(msg_buff));
		msg_len = 0;
	}
	// while((msg_len =  recv(con_fd, msg_buff, 2048, 0)) > 0){
	// 	printf("recv: %s\n", msg_buff);
	// }

	close(con_fd);
	close(socked_fd);


	
}
