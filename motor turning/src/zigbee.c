#include "zigbee.h"

char tem_buf[20];

int send_msg(char *cmd_buf)
{
    printf("2222");
    //1. 打开串口设备
    int serial_fd = open("/dev/s3c2410_serial3",O_RDWR);
    if(serial_fd == -1){
        printf("main:open serial error!\n");
        return -1;
    }

    //2.设置串口
    
    //获取串口属性
    struct termios termios_old;//为了在后面进行关闭串口的时候，恢复原来的设置
    struct termios termios_current;//为了在原来的基础上改变串口的设置（属性）

    tcgetattr(serial_fd, &termios_old);
    tcgetattr(serial_fd, &termios_current);


    //设置位raw模式
    cfmakeraw(&termios_current);
    //设置波特率
    cfsetspeed(&termios_current,B115200);

    //设置bit位 8位
    termios_current.c_cflag &= ~CSIZE;//11 0000
    termios_current.c_cflag |= CS8; //11 0000

    //设置停止位
    termios_current.c_cflag &= ~CSTOPB;//

    //关闭奇偶校验
    // termios_current.c_cflag &= ~PARENB;

    // termios_current.c_cflag &= ~CRTSCTS;

    tcflush(serial_fd,TCIOFLUSH);

    tcsetattr(serial_fd,TCSANOW,&termios_current);
    
        printf("adsf");
        write(serial_fd, cmd_buf, 1);

    // write(serial_fd, cmd_buf, 6);

    tcsetattr(serial_fd,TCSANOW,&termios_old);
    close(serial_fd);

    return 0;
}

// int get_tem_hum()
// {

//     //1. 打开串口设备
//     int serial_fd = open("/dev/s3c2410_serial3",O_RDWR);
//     if(serial_fd == -1){
//         printf("main:open serial error!\n");
//         return -1;
//     }

//     //2.设置串口
    
//     //获取串口属性
//     struct termios termios_old;//为了在后面进行关闭串口的时候，恢复原来的设置
//     struct termios termios_current;//为了在原来的基础上改变串口的设置（属性）

//     tcgetattr(serial_fd, &termios_old);
//     tcgetattr(serial_fd, &termios_current);

//     //设置位raw模式
//     cfmakeraw(&termios_current);
//     //设置波特率
//     cfsetspeed(&termios_current,B115200);

//     //设置bit位 8位
//     termios_current.c_cflag &= ~CSIZE;//11 0000
//     termios_current.c_cflag |= CS8; //11 0000

//     //设置停止位
//     termios_current.c_cflag &= ~CSTOPB;//

//     //关闭奇偶校验
//     termios_current.c_cflag &= ~PARENB;

//     termios_current.c_cflag &= ~CRTSCTS;

//     tcflush(serial_fd,TCIOFLUSH);

//     tcsetattr(serial_fd,TCSANOW,&termios_current);

//     while(1){
//         read(serial_fd, tem_buf, 20);
//     }

//     tcsetattr(serial_fd,TCSANOW,&termios_old);
//     close(serial_fd);

//     return 0;
// }

// void * _get_tem_pthread_function(void * arg){

//     get_tem_hum();
//     pthread_exit(NULL);
// }

// int create_tem_pthread(){
//     pthread_t tem_pthread_id = -1;
//     pthread_create(&tem_pthread_id, NULL, _get_tem_pthread_function, NULL);
//     return tem_pthread_id;
// }
