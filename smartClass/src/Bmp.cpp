#include <iostream>
#include "../include/Bmp.hpp"
#include "../../login/login.hpp"
#include "../include/Ts.hpp"
#include <thread>

using namespace std;
bool returnMainPage = false;
// lv_obj_t *page1;

int currentIndex = 0;//当前图片的索引
Bmp b1("./smartClass/res/pic/1.bmp");
Bmp b2("./smartClass/res/pic/2.bmp");
Bmp b3("./smartClass/res/pic/3.bmp");
Bmp b4("./smartClass/res/pic/4.bmp");
Bmp b5("./smartClass/res/pic/5.bmp");
Bmp b6("./smartClass/res/pic/6.bmp");
Bmp b7("./smartClass/res/pic/7.bmp");

ostream& operator<<(ostream &out, const Bmp &b){
    out << "图片名：" << b.bmpName
        << "图片大小：" << b.width << "*" << b.height
        << "起始点：" << "(" << b.offset_x << "." << b.offset_y << ")";
    return out;
}

void BmpList::displayImages(){
    if(!dataList.empty()){
        for(Bmp &bmp: dataList){
            bmp.openBmp();
            bmp.showBmp();
            bmp.closeBmp();
        }
    }else
        cout << "dataList is empty" << endl;
}

void BmpList::displayImageFont(int currentIndex){
    if(currentIndex > 0 && static_cast<size_t>(currentIndex) < dataList.size()){
        auto at = next(dataList.begin(), currentIndex - 1);//迭代器指向当前图片
        Bmp &bmp = *at;
        bmp.openBmp();
        //指向前一个图片的指针
        bmp.showBmp();
        bmp.closeBmp();
    }
}

void BmpList::displayImageBack(int currentIndex){
    if(static_cast<size_t>(currentIndex) < dataList.size() - 1){
        auto at = next(dataList.begin(), currentIndex + 1);
        Bmp &bmp = *at;
        bmp.openBmp();
        bmp.showBmp(); 
        bmp.closeBmp();
    }
}

int Bmp::display_bmp_picture_to_framebuffer(int x, int y, float size){
    // Bmp b(bmpPath);
    
    if(openBmp() == -1){
        cout << "open bmp file failed" << endl;
        return -1;
    }

    setOffsetxy(x, y);
    getWidthHeight();

    showBmpSize(size);
    closeBmp();

    return 0;
}

void Bmp::clearCustomDisplay() {//清除自定义显示
    int width = 800, height = 480;

    volatile unsigned int* framebuffer = reinterpret_cast<volatile unsigned int*>(lcd.getAddr());
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            framebuffer[y * width + x] = 0; // 设置为黑色或其他背景色
        }
    }
}

void eventPic(void){
    b5.display_bmp_picture_to_framebuffer(0, 0, 1.0);
    sleep(2);
    b6.display_bmp_picture_to_framebuffer(0, 0, 1.0);
    sleep(2);
    b7.display_bmp_picture_to_framebuffer(0, 0, 1.0);
    sleep(2);   
}

void customDisplayhandler(){//响应函数与lvgl主函数分离
    //自定义显示
    // if(b1.openBmp() != 0)
    //   return;
    // b1.showBmp();
    // b1.closeBmp();

    b1.display_bmp_picture_to_framebuffer(0, 0, 0.5);
    b2.display_bmp_picture_to_framebuffer(400, 0, 0.5);
    b3.display_bmp_picture_to_framebuffer(0, 240, 0.5);
    b4.display_bmp_picture_to_framebuffer(400, 240, 0.5);
}

void handleTouchEvent(){
    customDisplayhandler();

    Ts ts;
    ts.openTS();
    int x = 0, y = 0;
    int status = ts.get_xy(&x, &y);
    if(status == 0){
        if(x > 0 && x < 400 && y > 0 && y < 240){
            currentIndex = 0;
            b1.display_bmp_picture_to_framebuffer(0, 0, 1.0);
        }else if(x > 400 && x < 800 && y > 0 && y < 240){
            currentIndex = 1;
            b2.display_bmp_picture_to_framebuffer(400, 0, 1.0);
        }else if(x > 0 && x < 400 && y > 240 && y < 480){
            currentIndex = 2;
            b3.display_bmp_picture_to_framebuffer(0, 240, 1.0);
        }else if(x > 400 && x < 800 && y > 240 && y < 480){
            currentIndex = 3;
            b4.display_bmp_picture_to_framebuffer(400, 240, 1.0);
        }
    }

    BmpList list;
    list.insertHead(b1);
    list.insertTail(b2);
    list.insertTail(b3);
    list.insertTail(b4);
    list.insertTail(b5);
    list.insertTail(b6);
    list.insertTail(b7);

    list.listSort();

    list.displayImages();
    
    // while(status == 0){//循环读取触摸屏的坐标
    //     status = ts.get_xy(&x, &y);

    //     if(x > 0 && x < 400 && y > 0 && y < 240){
    //         list.displayImageFont(currentIndex);
    //         currentIndex = (currentIndex > 0)? currentIndex - 1 : 0;
    //     }else if(x > 400 && x < 800 && y > 0 && y < 240){
    //         list.displayImageBack(currentIndex);
    //         currentIndex = (static_cast<size_t>(currentIndex) < list.dataList.size() - 1)? currentIndex + 1 : list.dataList.size() - 1;
    //     }else
    //         break;
    // }
    eventPic();

    returnMainPage = true;

    list.deList();
    ts.closeTS();

    sleep(2);

}

void createBmpScreen(){
    
    page1 = lv_obj_create(screen);
    lv_obj_set_size(page1, LV_HOR_RES, LV_HOR_RES);

    //lvgl背景
    lv_obj_t * img = lv_img_create(page1);//创建背景图片对象
    lv_img_set_src(img, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
    lv_obj_set_size(img, lv_obj_get_width(page1), lv_obj_get_height(page1));//设置图片的大小为屏幕的大小
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间
    
    thread touchThread(handleTouchEvent);
    
    // customDisplayhandler();
    touchThread.join();//等待线程结束

     //返回主界面
    // lv_obj_clean(page1);
    // create_main_screen(page1);
    // lv_scr_load(screen);
    
    // lv_obj_clean(lv_scr_act());//清除当前屏幕上的所有对象
    while(!returnMainPage){
        lv_task_handler();
        usleep(5000);
    }

    lv_obj_del(page1);

    create_main_screen();
   
    // lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);//切换到主界面
    
}