#include "../include/Led.hpp"
#include "../include/Buzzer.hpp"
#include <iostream>
#include <assert.h>

using namespace std;

int led_status = 2;
short beep_status = 2;
lv_obj_t * led1;
lv_obj_t * led2;
//引用全局变量

lv_obj_t * btn1;
lv_obj_t * btn2;
lv_obj_t * btn3;
lv_obj_t * btn4;
lv_obj_t * btn5;

pthread_mutex_t mutex;//初始化互斥锁

Led led;
Buzzer buzzer;

// void run(Led& l) {
//     // 定时器设置
//     struct timeval tv;
//     while (true) {
//         tv.tv_sec = 1; // 1秒
//         tv.tv_usec = 0;

//         // 等待时间到达或者中断信号
//         if (select(0, NULL, NULL, NULL, &tv) == -1) {
//             perror("select error");
//             break;
//         }

//         l.ioctStatus(); // 切换蜂鸣器状态
//     }
//     l.closeLed(); // 关闭蜂鸣器
// }

// static void signalHandler(int signum) {
//     if (signum == SIGINT) {
//         printf("Interrupt signal received, exiting...\n");
//         exit(0);
//     }
// }

// void run(Buzzer& b) {
//     // 定时器设置
//     struct timeval tv;
//     while (true) {
//         tv.tv_sec = 1; // 1秒
//         tv.tv_usec = 0;

//         // 等待时间到达或者中断信号
//         if (select(0, NULL, NULL, NULL, &tv) == -1) {
//             perror("select error");
//             break;
//         }

//         b.ioctStatus(); // 切换蜂鸣器状态
//     }
//     b.closeBuzzer(); // 关闭蜂鸣器
// }

// static void signalHandler(int signum) {
//     if (signum == SIGINT) {
//         printf("Interrupt signal received, exiting...\n");
//         exit(0);
//     }
// }

// void buzzerStart(){
//     cout << "Buzzer started" << endl;
//     Buzzer b;
//     b.openBuzzer();
//     signal(SIGINT, signalHandler);
//     run(b);
//     return;
// }


// void ledStart(){
//     cout << "LED started" << endl;
//     Led l;
//     l.openLed();
//     signal(SIGINT, signalHandler);
//     run(l);

//     return;
// }

//开灯
static void event_handler(lv_event_t *e)
{
    // pthread_mutex_t mutex;//初始化互斥锁

    // pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
            //如果点了开灯按钮 
        led_status = 0;
        pthread_mutex_lock(&mutex);
        // lv_led_on(led1);
        if(led.openLed())
            led.ioctStatus();
        
        // //打开LED
        // ioctl(led.fdLed, LED1, led_status);
        // ioctl(led.fdLed, LED2, led_status);
        // ioctl(led.fdLed, LED3, led_status);
        // ioctl(led.fdLed, LED4, led_status);
        pthread_mutex_unlock(&mutex);
        
    }

}

//关灯
static void event_handler2(lv_event_t *e)
{
    // pthread_mutex_t mutex;//初始化互斥锁

    // pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
                //如果点了关灯按钮
        led_status = 1;
        //关闭LED
        pthread_mutex_lock(&mutex);

        if(led.openLed())
            led.ioctStatus();
        
        pthread_mutex_unlock(&mutex);
        // ioctl(fd_led, LED1, led_status);
        // ioctl(fd_led, LED2, led_status);
        // ioctl(fd_led, LED3, led_status);
        // ioctl(fd_led, LED4, led_status);
    }
    
}

//开蜂鸣器
static void event_handler3(lv_event_t *e)
{
    //如果点了开蜂鸣器按钮
    // beep_status = 0;
    // //打开蜂鸣器
    // pthread_mutex_t mutex;//初始化互斥锁

    pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        pthread_mutex_lock(&mutex);
        // lv_led_on(led2);
        if(buzzer.openBuzzer())
            buzzer.ioctStatus();
        pthread_mutex_unlock(&mutex);
        // ioctl(fd_beep,beep_status,1);
    }
    
}

//关蜂鸣器
static void event_handler4(lv_event_t *e)
{
    //如果点了关蜂鸣器按钮
    beep_status = 1;
    //关闭蜂鸣器
    // pthread_mutex_t mutex;//初始化互斥锁

    // pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        pthread_mutex_lock(&mutex);
        // lv_led_off(led2);
        if(buzzer.openBuzzer())
            buzzer.ioctStatus();
        pthread_mutex_unlock(&mutex);
        // ioctl(fd_beep,beep_status,1);
    }
    
}

static void event_handler5(lv_event_t *e){
    //回到主界面
    lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("back");
            assert(page4);
            led.closeLed();
            buzzer.closeBuzzer();
            
            // lv_obj_del(page4);
            create_main_screen();
        }
}

void createLedBeepScreen(void)
{
    page4 = lv_obj_create(screen);
                
    lv_obj_set_size(page4, LV_HOR_RES, LV_VER_RES); // 设置为全屏

    led.openLed();
    buzzer.openBuzzer();
    pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁

    lv_obj_t * imgLB = lv_img_create(page4);//创建背景图片对象
    lv_img_set_src(imgLB, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
    lv_obj_set_size(imgLB, LV_HOR_RES, LV_VER_RES);//设置图片的大小为屏幕的大小
    lv_obj_align(imgLB, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间

    static lv_style_t style;
    lv_style_init(&style);//初始化样式

    lv_style_set_radius(&style, 3);//圆角半径

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));//背景颜色
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));//背景颜色渐变色
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);//背景颜色渐变方向

    lv_style_set_border_opa(&style, LV_OPA_40);//边框透明度
    lv_style_set_border_width(&style, 2);//边框宽度
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));//边框颜色

    lv_style_set_shadow_width(&style, 8);//阴影宽度
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));//意思是阴影颜色
    lv_style_set_shadow_ofs_y(&style, 8);//阴影偏移

    lv_style_set_outline_opa(&style, LV_OPA_COVER);//边框透明度
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));//边框颜色

    lv_style_set_text_color(&style, lv_color_white());//文字颜色
    lv_style_set_pad_all(&style, 10);//内边距

    /*Init the pressed style*/
    static lv_style_t style_pr;//
    lv_style_init(&style_pr);//初始化样式

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 30);//边框宽度
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);//边框透明度

    lv_style_set_translate_y(&style_pr, 5);//移动位置
    lv_style_set_shadow_ofs_y(&style_pr, 3);//阴影偏移
    lv_style_set_bg_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 2));//背景颜色
    lv_style_set_bg_grad_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 4));//背景颜色渐变色

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;//意思是样式过渡
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};//意思是样式属性
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);//初始化样式过渡

    lv_style_set_transition(&style_pr, &trans);//设置样式过渡

    btn1 = lv_btn_create(page4);//创建按钮
    lv_obj_remove_style_all(btn1);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn1, &style, 0);//添加默认样式
    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    // lv_obj_center(btn1);//居中
    lv_obj_set_pos(btn1, 200, 260);//设置位置
    //点了该按钮后，led_status的值为0
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn2 = lv_btn_create(page4);//创建按钮
    lv_obj_remove_style_all(btn2);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn2, &style, 0);//添加默认样式
    lv_obj_add_style(btn2, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn1的下方
    lv_obj_set_pos(btn2, 200, 340);//设置位置
    lv_obj_add_event_cb(btn2, event_handler2, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn3 = lv_btn_create(page4);//创建按钮
    lv_obj_remove_style_all(btn3);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn3, &style, 0);//添加默认样式
    lv_obj_add_style(btn3, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn3, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn2的下方
    lv_obj_set_pos(btn3, 50, 260);//设置位置
    lv_obj_add_event_cb(btn3, event_handler3, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn4 = lv_btn_create(page4);//创建按钮
    lv_obj_remove_style_all(btn4);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn4, &style, 0);//添加默认样式
    lv_obj_add_style(btn4, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn4, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn3的下方
    lv_obj_set_pos(btn4, 50, 340);//设置位置
    lv_obj_add_event_cb(btn4, event_handler4, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn5 = lv_btn_create(page4);//创建按钮
    lv_obj_remove_style_all(btn5);//移除默认样式                         
    lv_obj_add_style(btn5, &style, 0);//添加默认样式
    lv_obj_add_style(btn5, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn5, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在左上角
    lv_obj_set_pos(btn5, 600, 0);
    lv_obj_add_event_cb(btn5, event_handler5, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    lv_obj_t * label = lv_label_create(btn1);//创建标签
    lv_label_set_text(label, "open led");//设置标签文字
    lv_obj_center(label);//居中
    lv_obj_set_style_text_color(label, lv_color_darken(lv_color_white(), 2), 0);//设置文字颜色

    lv_obj_t * label2 = lv_label_create(btn2);//创建标签
    lv_label_set_text(label2, "close led");//设置标签文字
    lv_obj_center(label2);//居中
    lv_obj_set_style_text_color(label2, lv_color_darken(lv_color_black(), 2), 0);//设置文字颜色

    lv_obj_t * label3 = lv_label_create(btn3);//创建标签
    lv_label_set_text(label3, "open beep");//设置标签文字
    lv_obj_center(label3);//居中
    lv_obj_set_style_text_color(label3, lv_color_black(), 0);//设置文字颜色

    lv_obj_t * label4 = lv_label_create(btn4);//创建标签
    lv_label_set_text(label4, "close beep");//设置标签文字
    lv_obj_center(label4);//居中
    lv_obj_set_style_text_color(label4, lv_color_black(), 0);//设置文字颜色

    lv_obj_t * label5 = lv_label_create(btn5);//创建标签
    lv_label_set_text(label5, "back");//设置标签文字
    lv_obj_center(label5);//居中
    lv_obj_set_style_text_color(label5, lv_color_black(), 0);//设置文字颜色
    

}

