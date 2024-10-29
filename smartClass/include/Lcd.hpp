#ifndef _LCD_HEAD_
#define _LCD_HEAD_

#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstring>

extern "C"
{
	#include <sys/mman.h>	
}

//Lcd类
class Lcd
{
public: //公有方法
	//Lcd(){}
    // Lcd(const char *path):lcdPath("/dev/fb0")//构造函数
	Lcd(const char *path){
		memset(lcdPath,0,sizeof(lcdPath));
		strcpy(this->lcdPath,path);
        // openLcd();
	} 
    ~Lcd()
	{
		//lcd的释放
		munmap(addr,800*480*4);
        // closeLcd();
	} //析构函数

    //系统默认的拷贝构造函数
    Lcd(const Lcd &other){};
    
	int openLcd()
	{
		// 打开lcd
		fdLcd = open(lcdPath, O_RDWR);
		if (fdLcd < 0)
		{
			printf("open lcd fail\n");
			return -1;
		}

		// lcd的映射(返回了lcd屏幕的第0个像素点的地址)
		addr = (int *)mmap(NULL, //If  addr is NULL, then the kernel chooses the address
						 800*480*4, //lcd的大小
						 PROT_READ|PROT_WRITE, //lcd的权限
						 MAP_SHARED,//lcd的标志量
						 fdLcd,//文件描述符
						 0); //lcd的偏移量
		if(addr == NULL)
		{
			perror("mmap fail");
			close(fdLcd);
			return -1;
		}		
		
		return 0;
	}
	void closeLcd()
	{
		// 关闭lcd
		close(fdLcd);
	}	
	char *getLcdPath() //获取lcd的路径
	{
		return lcdPath;
	}
	int *getAddr()//获取lcd的映射地址
	{
		return addr;
	}

	
private://私有属性
	char lcdPath[256]; //lcd的路径
	int fdLcd; //lcd的文件描述符
	int *addr;//lcd的映射地址
};


#endif