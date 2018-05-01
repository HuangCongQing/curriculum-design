# curriculum-design
课程设计，课程代码

2017.12
### 学习过程

* [第1次test](./cqupt3/03_day_2)
* [第2次刷红绿蓝三种颜色](./02_day/02_code)
* [第3次图片触摸屏](./cqupt3/03_day_2)
* [第4次点击切换界面](./cquptALL/03_day)

### 硬件所需
* ARM开发板（GEC210是一款高性能的Cortex A8核心板）
* Zigbee协调器和节点（ Z-Stack是符合Zigbee协议栈规范的一个硬件和软件平台）
* 步进电机

### 思路分析过程

首先ARM开发板通过串口发送数据字符串“11”“10”到协调器，协调器自动发送数据到节点，节点通过函数处理将字符串转化为数组，通过数组内容判断，来决定电机正转或者是反转。

![原理过程](https://upload-images.jianshu.io/upload_images/4340772-47c6685733e8c2a7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![数据流程图](https://upload-images.jianshu.io/upload_images/4340772-83a0284e2f85c27d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 项目目录(cmd : tree/F：递归显示目录结构)
```
motor_completed
│  makefile    // 编译命令文件，运行此命令，输出编译文件，把编译文件放到arm32中（）
│           arm-linux-gcc -o **./bin/cqupt1** ./src/*.c -I ./include/ -std=c99 -L ./lib -l ts -l pthread
├─bin
│      0.bmp  //图片放置此文件夹
│      cqupt
│      cqupt1
│      em.bmp
│      main1.bmp
│
├─include
│      lcd.h     
│      serial.h  //串口通信
│      ts.h
│      tslib.h
│      ui.h
│
├─lib
│      libts.so
│
└─src
        lcd.c       // LCD
        main.c      // 主函数执行
        serial.c    //串口通信
        ts.c        //触摸屏控制
        ui.c        //图片切换

```

### 实现效果


![](https://upload-images.jianshu.io/upload_images/4340772-39e1b0991dafb853.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
