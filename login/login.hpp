#ifndef LOGIN_HPP
#define LOGIN_HPP

// #include "../smartClass/include/Bmp.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "lvgl/src/widgets/keyboard/lv_keyboard.h"
#include "clientWav/client_wav.h"

// #include "lvgl/src/core/lv_disp.h"
extern lv_obj_t *loginScreen;
extern lv_obj_t *screen;
extern lv_obj_t *page1;
extern lv_obj_t *page2;
extern lv_obj_t *page3;
extern lv_obj_t *page4;

void create_login(lv_obj_t *parent);
void create_main_screen();
void createBmpScreen();
void createMediaScreen();
// void createXFScreen();
void createLedBeepScreen();

#ifdef __cplusplus
}
#endif



#endif
