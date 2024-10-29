#ifndef _MENU_HEAD_
#define _MENU_HEAD_

// #include "Bmp.hpp"
// #include "Buzzer.hpp"
// #include "Lcd.hpp"
// #include "Led.hpp"
// #include "Mp3Mp4.hpp"
// #include "Thread.hpp"
// #include "Ts.hpp"

// class Menu{
//     public:
//         Menu():lcd("/dev/fb0"),bmp(" "){}//图片链表
//         ~Menu(){}

//         void appFunc(){
//             int ts_x;
//             int ts_y;
//             int ts_status;
//             lcd.openLcd();
//             ts.openTs();

//             while(1){
//                 bmp.showBmp();
//                 int rt = ts.get_xy(&ts_x, &ts_y, &ts_status);

//                 if((ts_x >= 45 && ts_x <= 125) && (ts_y >= 14 && ts_y <= 35)){
//                     //bmp
//                 }

//                 if((ts_x >= 45 && ts_x <= 125) && (ts_y >= 14 && ts_y <= 35)){
//                     //music
//                 }

//                 if((ts_x >= 45 && ts_x <= 125) && (ts_y >= 14 && ts_y <= 35)){
//                     //movie
//                 }

//                 if((ts_x >= 45 && ts_x <= 125) && (ts_y >= 14 && ts_y <= 35)){
//                     //led/buzzer
//                 }
                
//                 if((ts_x >= 45 && ts_x <= 125) && (ts_y >= 14 && ts_y <= 35)){
//                     //yuyin
//                     clientWavFunc();
//                 }

//             }
//         }
    
//     private:
//         Ts ts;
//         Lcd lcd;
//         Bmp bmp;
//         Led led;
//         Buzzer buzz;
//         Mp3Mp4 m34;
//         SendThread send;
//         ReceiveThread receive;
//         TimerThread timer;

// };

// extern "C" {
//     #include "../../lvgl/lvgl.h"
//     #include "../../clientWav/client_wav.h"
// }

// class MainScreen {
// public:
//     MainScreen() {
//         createMainScreen();
//     }

//     void show() {//显示主屏幕
//         lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);
//     }

// private:
//     lv_obj_t* main_screen;

//     void createMainScreen() {
//         main_screen = lv_obj_create(NULL); // 创建主屏幕对象
//         lv_scr_load(main_screen); // 加载主屏幕

//         // 创建标签并添加到主屏幕
//         lv_obj_t* label = lv_label_create(main_screen); 
//         lv_label_set_text(label, "欢迎来到主界面!");
//         lv_obj_center(label); // 将标签居中


//         // 创建按钮以跳转到设置界面
//         lv_obj_t* settings_btn = lv_btn_create(main_screen);
//         lv_obj_set_event_cb(settings_btn, settingsButtonEventHandler);
//         lv_obj_align(settings_btn, LV_ALIGN_TOP_LEFT, 10, 10);
//         lv_obj_t* settings_label = lv_label_create(settings_btn);
//         lv_label_set_text(settings_label, "设置");

//         // 创建按钮以跳转到音乐界面
//         lv_obj_t* music_btn = lv_btn_create(main_screen);
//         lv_obj_set_event_cb(music_btn, musicButtonEventHandler);
//         lv_obj_align(music_btn, LV_ALIGN_TOP_LEFT, 10, 60);
//         lv_obj_t* music_label = lv_label_create(music_btn);
//         lv_label_set_text(music_label, "音乐");
//     }


//     static void settingsButtonEventHandler(lv_event_t* e) {
//         // 跳转到设置界面
//         SettingsScreen::show();
//     }

//     static void musicButtonEventHandler(lv_event_t* e) {
//         // 跳转到音乐界面
//         MusicScreen::show();
//     }
// };


// class SettingsScreen {
// public:
//     static void show() {
//         lv_scr_load_anim(settings_screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);
//     }

// private:
//     static lv_obj_t* settings_screen;

//     static void createSettingsScreen() {
//         settings_screen = lv_obj_create(NULL); // 创建设置屏幕对象

//         lv_obj_t* label = lv_label_create(settings_screen); 
//         lv_label_set_text(label, "设置界面");
//         lv_obj_center(label); // 将标签居中

//         // 其他设置界面的组件可以在这里创建...
//     }
// };

// lv_obj_t* SettingsScreen::settings_screen = NULL;

// class MusicScreen {
// public:
//     static void show() {
//         lv_scr_load_anim(music_screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);
//     }

// private:
//     static lv_obj_t* music_screen;

//     static void createMusicScreen() {
//         music_screen = lv_obj_create(NULL); // 创建音乐屏幕对象

//         lv_obj_t* label = lv_label_create(music_screen); 
//         lv_label_set_text(label, "音乐界面");
//         lv_obj_center(label); // 将标签居中

//         // 其他音乐界面的组件可以在这里创建...
//     }
// };

// lv_obj_t* MusicScreen::music_screen = NULL;



#endif
