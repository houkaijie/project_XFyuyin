#include <iostream>
#include "../include/Button.hpp"

using namespace std;


//显示按键被按下
void display_button_press(Button *bt, unsigned int *fb_addr)
{
    display_bmp_picture_to_framebuffer(bt->getBtPImage(), bt->getBtPosX(), bt->getBtPosY());
}

//显示按键被松开
void display_button_release(Button *bt, unsigned int *fb_addr)
{
    display_bmp_picture_to_framebuffer(bt->getBtRImage(), bt->getBtPosX(), bt->getBtPosY());
}

//显示所有的按键集合
void display_button_set(Button *bt[], int len, unsigned int *fb_addr)
{
    int i;

    for(i=0; i<len; i++)
    {
        display_button_release(bt[i], fb_addr);
    }
}