# curriculum-design
课程设计，课程代码

2017.12
###

* [第1次test](./cqupt3/03_day_2)
* [第2次刷红绿蓝三种颜色](./02_day/02_code)
* [第3次图片触摸屏](./cqupt3/03_day_2)
* [第4次点击切换界面](./cquptALL/03_day)


### 项目目录(cmd : tree/F：递归显示目录结构)

motor_completed
│  makefile    // 编译命令文件，运行此命令，输出编译文件，把编译文件放到arm32中（）
│           arm-linux-gcc -o **./bin/cqupt1** ./src/*.c -I ./include/ -std=c99 -L ./lib -l ts -l pthread
├─bin
│      0.bmp
│      2.bmp
│      3.bmp
│      4.bmp
│      5.bmp
│      6.bmp
│      7.bmp
│      8.bmp
│      9.bmp
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