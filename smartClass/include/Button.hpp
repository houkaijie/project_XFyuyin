#ifndef _BUTTON_HEAD_
#define _BUTTON_HEAD_

#include <string>

using namespace std;

class Button{
    public:
        Button(int x, int y, int width, int hight, string btInfo, string btImageP, string btImageR):pos_x(x),pos_y(y),width(width),height(hight),btInfo(btInfo),btPImage(btImageP),btRImage(btImageR){}
        ~Button(){}

        int getBtPosX(){
            return pos_x;
        }

        int getBtPosY(){
            return pos_y;
        }
        
        string getBtPImage(){
            return btPImage;
        }

        string getBtRImage(){
            return btRImage;
        }

    private:
        int pos_x;
        int pos_y;
        int width;
        int height;
        string btInfo;
        string btPImage;
        string btRImage;
};

//显示按键被按下
extern void display_button_press(Button *bt, unsigned int *fb_addr);
//显示按键被松开
extern void display_button_release(Button *bt, unsigned int *fb_addr);
//显示所有的按键集合
extern void display_button_set(Button *bt[], int len, unsigned int *fb_addr);


#endif