#include "../../lv_examples.h"
#include "../../../lvgl.h"
#include "login/login.hpp"

#if LV_USE_PNG && LV_USE_IMG && LV_BUILD_EXAMPLES

/**
 * Open a PNG image from a file and a variable
 */
void lv_example_png_1(lv_obj_t * screen)
{
    // LV_IMG_DECLARE(img_wink_png);//声明一个png图片变量
    
    lv_obj_t * img;

    // img = lv_img_create(lv_scr_act());//创建第一个图片对象
    // lv_img_set_src(img, &img_wink_png);//设置图片源为img_wink_png变量
    // lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);//将图片显示在屏幕中间的左侧

    img = lv_img_create(screen);//创建第二个图片对象
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_img_set_src(img, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/desktop.jpg");//意思是将图片显示在屏幕中间的左侧
    //lv_obj_align(img, LV_ALIGN_RIGHT_MID, -20, 0);//意思是将图片显示在屏幕中间的右侧
}

#endif
