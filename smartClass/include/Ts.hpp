#ifndef _TS_HEAD_
#define _TS_HEAD_

#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstring>

#define TOUCH_COORDINATE_STATUS     0
#define TOUCH_PRESS_STATUS          1
#define TOUCH_RELEASE_STATUS        2
#define TOUCH_ERROR_STATUS          -1

extern "C"
{
	#include <sys/mman.h>	
    #include <linux/input.h> //struct input_event ts的头文件	
}

class Ts
{
public:
	//构造函数+参数列表赋值
	Ts():tsPath("/dev/input/event0")//正确
	{
		// strcpy(tsPath,path);
        openTS();
	}
	~Ts(){
        closeTS();
    }

	int openTS()
	{
		// 打开触摸屏
		fdTs = open(tsPath, O_RDWR);
		if (fdTs < 0)
		{
			printf("open ts fail\n");
			return -1;
		}	
		return 0;
	}
	
	void closeTS()
	{
		close(fdTs);
	}
	
	int getFdTs(){
		return fdTs;
	}

	/*
		获取触摸屏坐标的封装函数
	*/
	int get_xy(int *x,int *y)
	{
		// 读取触摸屏的的x轴和y轴的坐标值
		// 定义一个存储触摸屏信息的结构体
		struct input_event ts;
		
		while(1)
		{
			memset(&ts, 0, sizeof(struct input_event));
			// 将触摸屏的信息读到结构体中（此时是阻塞）
			read(fdTs, &ts, sizeof(struct input_event));

			//获取结构体信息里面的x轴坐标值和Y轴的坐标值
			//获取x轴的坐标
			if(ts.type==EV_ABS && ts.code==ABS_X)
			{
				// printf("x=%d ",ts.value); //蓝色的触摸屏
				// printf("x=%d ",ts.value*800/1024); //黑色的触摸屏

				*x = ts.value * 800 / 1024;
			}
			//获取y轴的坐标
			if(ts.type==EV_ABS && ts.code==ABS_Y)
			{
				// printf("y=%d\n",ts.value);//蓝色的触摸屏
				// printf("y=%d\n",ts.value*480/600);//黑色的触摸屏

				*y = ts.value * 480 / 600;
			}

			//获取按下去的坐标值
			if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1)
			{
				printf("down:x=%d y=%d\n",*x,*y);
				break;
			}
			//获取松手后的坐标值
			if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
			{
			    printf("up:x=%d y=%d\n",*x,*y);
			}
		}
		return 0;
	}	
	
private:
	char tsPath[20]; //触摸屏的路径
	int fdTs;//触摸屏的文件描述符
};

#endif