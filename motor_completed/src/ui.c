#include "ui.h"
#include "serial.h"


enum _ui ui_flag;
enum _dht_opt dht_opt;
int expext=0,exp_speed=0,exp_quan=0;


int init_flag(){
	ui_flag = UI_MAIN;
	dht_opt = DHT_NULL;
	return 0;
}



int pro_ui_main(){
	// printf("pro_ui_main：----\n");
	bmp_800_480("./main1.bmp");
	//show_bmp_not_800_480("./02.bmp",400,240);
	while(ui_flag ==  UI_MAIN);
}

int show_arg_cir(int x,int y, int z){
	switch(z){
		case 0:{
			show_bmp_not_800_480("./0.bmp",x,y,0);
			break;
		}
		case 1:{
			show_bmp_not_800_480("./1.bmp",x,y,1);
			break;
		}
		case 2:{
			show_bmp_not_800_480("./2.bmp",x,y,2);
			break;
		}
		case 3:{
			show_bmp_not_800_480("./3.bmp",x,y,3);
			break;	
		}
		case 4:{
			show_bmp_not_800_480("./4.bmp",x,y,4);
			break;
		}
		case 5:{
			show_bmp_not_800_480("./5.bmp",x,y,5);
			break;
		}
		case 6:{
			show_bmp_not_800_480("./6.bmp",x,y,6);
			break;
		}
		case 7:{
			show_bmp_not_800_480("./7.bmp",x,y,7);
			break;
		}
		case 8:{
			show_bmp_not_800_480("./8.bmp",x,y,8);
			break;
		}
		case 9:{
			show_bmp_not_800_480("./9.bmp",x,y,9);
			break;
		}
	}
	return 0;
}

//电机调速预期值函数，x,y,z,分别对应档位，预期角度，圈数
int expect_speed(int x){
	switch(x){
		case 0:{
			exp_speed=0;
			exp_quan=0;
			break;
		}
		case 1:{
			exp_speed=360;
			exp_quan=1;
			break;
		}
		case 2:{
			exp_speed=720;
			exp_quan=2;
			break;
		}
		case 3:{
			exp_speed=1080;
			exp_quan=3;
			break;
		}
		case 4:{
			exp_speed=1440;
			exp_quan=4;
			break;
		}
		case 5:{
			exp_speed=1800;
			exp_quan=5;
			break;
		}
		case 6:{
			exp_speed=2160;
			exp_quan=6;
			break;
		}
		case 7:{
			exp_speed=2520;
			exp_quan=7;
			break;
		}
		case 8:{
			exp_speed=2880;
			exp_quan=8;
			break;
		}
		case 9:{
			exp_speed=3240;
			exp_quan=9;
			break;
		}
		case 10:{
			exp_speed=3600;
			exp_quan=10;
			break;
		}
	}
}

int pro_ui_dht(){
	// printf("pro_ui_dht:----\n");
	bmp_800_480("./em.bmp");
	show_arg_cir(450,150,exp_quan/10%10);
	show_arg_cir(500,150,exp_quan%10);
	show_arg_cir(200,150,exp_speed/1000%10);
	show_arg_cir(250,150,exp_speed/100%10);
	show_arg_cir(300,150,exp_speed/10%10);
	show_arg_cir(350,150,exp_speed%10);
	while(ui_flag ==  UI_DHT){
		switch(dht_opt){
			case DHT_NULL:{
				continue;
			}
			case DHT_CONTROL_DI:{
				expext--;
				send("10");//-----------------------------send(0);
				speed=2;
				if (expext<0)
					expext=0;
				expect_speed(expext);
				show_arg_cir(450,150,exp_quan/10%10);
				show_arg_cir(500,150,exp_quan%10);
				show_arg_cir(200,150,exp_speed/1000%10);
				show_arg_cir(250,150,exp_speed/100%10);
				show_arg_cir(300,150,exp_speed/10%10);
				show_arg_cir(350,150,exp_speed%10);
				break;
			}
			case DHT_CONTROL_GAO:{
				expext++;
				send("11");//---------------------------------send(1);
				speed=2;
				if (expext>10)
					expext=0;
				expect_speed(expext);
				show_arg_cir(450,150,exp_quan/10%10);
				show_arg_cir(500,150,exp_quan%10);
				show_arg_cir(200,150,exp_speed/1000%10);
				show_arg_cir(250,150,exp_speed/100%10);
				show_arg_cir(300,150,exp_speed/10%10);
				show_arg_cir(350,150,exp_speed%10);
				break;
			}
			case DHT_EXIT:{

				break;
			}
		}
		dht_opt = DHT_NULL;
	}
}