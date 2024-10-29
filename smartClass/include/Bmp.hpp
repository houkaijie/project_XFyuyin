#ifndef _BMP_HEAD_
#define _BMP_HEAD_

#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstring>
#include <list>
#include <string>
#include "Lcd.hpp"
#include <iostream>

using namespace std;

extern "C"
{
	#include <sys/mman.h>	
}

//Bmp类
class Bmp
{
	friend ostream& operator<<(ostream &out, Bmp &b);
	
public: //公有方法
    Bmp(const char *path):lcd("/dev/fb0"),fdBmp(-1),bmpName(NULL)
	{	
		memset(bmpPath,0,sizeof(bmpPath));//初始化bmpPath
		// openBmp();
		strcpy(this->bmpPath,path);	//把参数列表中的path赋值给bmpPath

		getBmpName();

		if(openBmp() == 0){
			getWidthHeight(); //获取宽度和高度
		}
	} 
    ~Bmp(){
        closeBmp();
    } //析构函数

	bool operator<(const Bmp& other) const {
		return this->bmpName < other.bmpName; //按名字排序
	}

	Bmp& operator=(const Bmp& other){
		if(this == &other){
			closeBmp();
			
			if(bmpName != NULL){
				delete[] bmpName;
				bmpName = NULL;
			}

			memset(bmpPath,0,sizeof(bmpPath));
			strcpy(this->bmpPath,other.bmpPath);
			
			getBmpName();

			lcd = other.lcd;
			fdBmp = -1;
			width = other.width;
			height = other.height;
			offset_x = other.offset_x;
			offset_y = other.offset_y;

			if(openBmp() == 0)
				getWidthHeight(); //获取宽度和高度
		}
			
		return *this;
	}

	void clearCustomDisplay(); //清除自定义显示

    //系统默认的拷贝构造函数
    //Bmp(const Bmp &other){};
	int openBmp()
	{
		lcd.openLcd();//打开lcd的对象(给lcd的fd和addr赋值)
		fdBmp = open(bmpPath, O_RDWR);
		if (fdBmp == -1)
		{
			printf("open %s bmp fail\n",bmpPath);
			return -1;
		}  
		return 0;
	}
	void closeBmp()
	{
		// 关闭bmp
		if (bmpName != NULL) { // 确保指针不为空 
			delete[] bmpName;
			bmpName = NULL; 
		}

		if (fdBmp != -1) {
			close(fdBmp);
			fdBmp = -1; // 重置 fdBmp
		}
	}
	//显示800*480的bmp图片
	int showBmp()
	{
		//去除头54个字节
		lseek(fdBmp,54,SEEK_SET);

		//读bmp图片的数据
		char buf[800*480*3];
        memset(buf, 0, sizeof(buf));
		read(fdBmp,buf,800*480*3);

		int x = 0; //横轴
		int y = 0; //纵轴
		for(y=0;y<480;y++)
		{
			for(x=0;x<800;x++)
				//通过指针addr描述lcd上的每一个像素点
				// *(addr + y*800 +x) = 鸡哥图片的数据;
				//最后一行479  = 0 | 1<<8 |2<<16
				//478行 = 2400 | 2401<<8 | 2402<<16 
				*(lcd.getAddr() + (479-y)*800 +x) = buf[(y*800+x)*3] |
									   buf[(y*800+x)*3+1]<<8 |
									   buf[(y*800+x)*3+2]<<16; 
		}	
		return 0;
	}
    
	//获取宽度和高度
	void getWidthHeight()
	{
		lseek(fdBmp,18,SEEK_SET);
		read(fdBmp,&width,4); //读4个字节的宽度
		read(fdBmp,&height,4); //读4个字节的高度		
	}

	//设置bmp显示的起始地址(offset_x,offset_y)
	void setOffsetxy(int offset_x,int offset_y)
	{
		this->offset_x = offset_x;
		this->offset_y = offset_y;		
	}
	
	//显示任意大小的bmp
	void showBmpSize(float size)
	{
		 //去除头54个字节
		lseek(fdBmp,54,SEEK_SET);

		//读bmp图片的数据
		char buf[width*height*3];
		memset(buf,0,sizeof(buf));
		read(fdBmp,buf,width*height*3);

		//任意bmp图片的起始坐标(offset_x,offset_y)
		// int offset_x = 100;
		// int offset_y = 100;

		int newWidth = static_cast<int>(width * size);  // 缩放后的宽度
    	int newHeight = static_cast<int>(height * size); // 缩放后的高度

		int x = 0; //横轴
		int y = 0; //纵轴
		for(y=0;y<newHeight;y++) //整个bmp buffer的大小是width*height
		{
			int originalY = static_cast<int>(y / size); // 原始Y位置
        	if (originalY >= height) 
				continue; // 超过了原始高度则跳过
			
			for(x=0;x<newWidth;x++){
				int originalX = static_cast<int>(x / size); // 原始X位置
            	if (originalX >= width) 
					continue; // 超过了原始宽度则跳过
				int pixelPos = (originalY * width + originalX) * 3;
				// *(addr + (479-y)*800 +x) = buf[(y*800+x)*3] 
				//将上面的479替换成(offset_y+height-1) 将上面的x替换成offset_x+x
				*(lcd.getAddr() + ((offset_y+newHeight-1)-y)*800 +offset_x+x) = buf[pixelPos] |
																	buf[pixelPos+1]<<8 |
																	buf[pixelPos+2]<<16; 
			}
		}
		
	}

	void getBmpName(){
		int lastPos = -1;
        for(int i = 0; bmpPath[i] != '\0'; i++){
            if(bmpPath[i] == '/'){
                lastPos = i;//最後的杠
            }
        }

        if(lastPos != -1){//有
            bmpName = new char[strlen(bmpPath) - lastPos];
            strcpy(bmpName, bmpPath + lastPos + 1);
        }else{
            bmpName = new char[strlen(bmpPath) + 1];//真实大小，少一个\0
            strcpy(bmpName, bmpPath);
        }
	}
	
	int display_bmp_picture_to_framebuffer(int x, int y, float size);

// private://私有属性
	Lcd lcd; //lcd的对象(lcd作为bmp的内嵌对象较合适)
	char bmpPath[256]; //bmp的路径
	int fdBmp;//bmp的文件描述符
	char* bmpName; //bmp名字
	//图片的宽度和高度
    int width; //宽度  
    int height ; //高度	
	//图片显示的起始位置(offset_x,offset_y)
	int offset_x;
	int offset_y;
};

ostream& operator<<(ostream &out, const Bmp &b);

class BmpList{
    public:
        BmpList(){}
        ~BmpList(){
            dataList.clear();
        }
		
        void insertHead(const Bmp &data){
            dataList.push_front(data);
        } 
        
        void insertTail(const Bmp &data){
            dataList.push_back(data);
        }
           
        void deleteHead(){
            if(!dataList.empty())
                dataList.pop_front();
        }

        void deleteTail(){
            if(!dataList.empty())
                dataList.pop_back();
        }

        // Bmp findNode(string findName){
        //     for(const Bmp &val: dataList){
        //         if(val.bmpName == findName){
        //             cout << "find out " << findName <<endl;
        //             return val;
        //         }
        //     }
        //     cout << "find error!" <<endl;
    	// 	return Bmp(""); 
        // }

        // void changeNode(string oldName, Bmp newData){
        //     for(Bmp &val: dataList){
        //         if(val.bmpName == oldName){
        //             val = newData;
        //             cout << "find out " << oldName << "convert to " << newData <<endl;
        //             return;
        //         }
        //     }
        //     cout << "find error ,no change!" <<endl;
        // }

        void display() const{
            if(!dataList.empty()){
                for(const Bmp &val: dataList)
                    cout << val << " ";
                cout <<endl;
            }else
                cout << "链表为空！" <<endl;
        }

        void deList(){
            if(!dataList.empty())
                dataList.clear();
            else    
                cout << "链表已为空！" <<endl;
        }

		void displayImageFont(int curIndex);
		void displayImageBack(int curIndex);

        void listSort(){
            dataList.sort();
        }

		void displayImages();

        list<Bmp> dataList;
};

// #ifdef __cplusplus
// extern "C" {
// #endif


// extern void createBmpScreen();


// #ifdef __cplusplus
// }
// #endif

#endif
