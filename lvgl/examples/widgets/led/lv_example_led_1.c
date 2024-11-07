#include "../../lv_examples.h"
#if LV_USE_LED && LV_BUILD_EXAMPLES

lv_obj_t * led1;
lv_obj_t * led2;

// static void event_status_handler(lv_timer_t * timer)
// {
//     //判断灯的状态
//     if(led_status == 1)
//     {
//         lv_led_off(led1);
//     }
//     if(led_status == 0)
//     {
//         lv_led_on(led1);
//     }
//     //判断蜂鸣器的状态
//     if(beep_status == 1)
//     {
//         lv_led_off(led2);
//     }
//     if(beep_status == 0)
//     {
//         lv_led_on(led2);
//     }
// }

/**
 * Create LED's with different brightness and color
 */
void lv_example_led_1(void)
{
    //创建LED
    led1  = lv_led_create(lv_scr_act());
    //设置位置
    lv_obj_set_pos(led1, 750, 350);
    //设置亮度
    lv_led_set_brightness(led1, 150);
    //设置颜色
    lv_led_set_color(led1, lv_palette_main(LV_PALETTE_BLUE));   

    //表示蜂鸣器的状态
    led2  = lv_led_create(lv_scr_act());
    lv_obj_set_pos(led2, 750, 400);
    lv_led_set_brightness(led2, 150);
    lv_led_set_color(led2, lv_palette_main(LV_PALETTE_RED));

    
}

#endif
