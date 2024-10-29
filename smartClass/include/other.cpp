#include <iostream>
#include "./include/Ts.hpp"
#include "./Led.hpp"
#include "./Buzzer.hpp"
#include <thread>

using namespace std;


void handleTouchEvent1(){
    ledBeep();
}

// void createLedBeepScreen(){
    
//     page3 = lv_obj_create(NULL);
//     lv_obj_set_size(page3, LV_HOR_RES, LV_HOR_RES);

//     //lvgl背景
//     lv_obj_t * img = lv_img_create(page3);//创建背景图片对象
//     lv_img_set_src(img, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
//     lv_obj_set_size(img, lv_obj_get_width(page3), lv_obj_get_height(page3));//设置图片的大小为屏幕的大小
//     lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间
    
//     // customDisplayhandler();
    
//     thread touchThread1(handleTouchEvent1);

//     touchThread1.join();//等待线程结束

//      //返回主界面
//     // lv_obj_clean(page3);
//     // create_main_screen(page3);
//     // lv_scr_load(screen);
//     lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);

// }