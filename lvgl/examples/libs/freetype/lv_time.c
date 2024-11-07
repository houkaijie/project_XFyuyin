#include "../../lv_examples.h"
#if LV_BUILD_EXAMPLES
#if LV_USE_FREETYPE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

lv_obj_t * label;
char time_str[100];
static void event_set_time_handler(lv_obj_t * obj, lv_event_t event)
{
    time_t now;
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    // time_t now = time(0);
    // struct tm* local_time = localtime(&now);
    // // printf("当前日期和时间为：%s\n", asctime(local_time)); //输出当前日期和时间
    // strcpy(time_str, asctime(local_time));
    lv_label_set_text(label, time_str);
    
}

/**
 * Load a font with FreeType
 */
void lv_time(lv_obj_t * screen)
{
   /*创建一个字体*/
    static lv_ft_info_t info;//定义一个记录freetype字体信息的结构体
    /*记录字体文件路径 字号大小-单位借用  字体风格*/
    info.name = "/font/simkai.ttf";//字体文件名---华文楷体--文件已经放在开发板中
    info.weight = 35;//字号
    info.style = FT_FONT_STYLE_NORMAL;//字体风格
    info.mem = NULL;//指向字体数据的指针 一般要显示字体时，就会从上面字体文件中获取对应数据 freetype转换为位图数据 ，而mem指针指向这块数据
    //初始化
    if(!lv_ft_font_init(&info)){ 
        LV_LOG_ERROR("create failed.");
    }

     /*创建另一个字体*/
    static lv_ft_info_t info1;//定义一个记录freetype字体信息的结构体
    /*记录字体文件路径 字号大小-单位借用  字体风格*/
    info1.name = "/font/simfang.ttf";//字体文件名---华文行楷--文件已经放在开发板中
    info1.weight = 48;//字号
    info1.style = FT_FONT_STYLE_NORMAL;//字体风格
    info1.mem = NULL;//指向字体数据的指针 一般要显示字体时，就会从上面字体文件中获取对应数据 freetype转换为位图数据 ，而mem指针指向这块数据
    //初始化
    if(!lv_ft_font_init(&info1)){ 
        LV_LOG_ERROR("create failed.");
    }

    /*将上面字体添加到下面的lvgl样式对象中*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_color_t c = lv_color_hex(0xFFFFFFFF);//定义颜色值
    lv_style_set_text_font(&style, info.font);//设置该样式制定的字体--上面的
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);//设置该样式的文本对齐
    lv_style_set_text_color(&style,c);//设置该样式文本颜色

    /*创建一个文本对象并用上面的样式添加给该对象*/
    
    label = lv_label_create(screen);//创建文本对象
    lv_obj_add_style(label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label, time_str);//设置文本对象的文本内容
    lv_obj_set_pos(label, 0,0);//设置文本对象的位置
    lv_obj_add_event_cb(label, event_set_time_handler, LV_EVENT_VALUE_CHANGED, NULL);//添加事件回调函数

    /*创建一个定时器，每隔600毫秒刷新一次时间*/
    lv_timer_t * timer = lv_timer_create(event_set_time_handler, 600, NULL);
    lv_timer_ready(timer);


    
}

#else

void lv_time(void)
{
    /*TODO
     *fallback for online examples*/

    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "FreeType is not installed");
    lv_obj_center(label);
}

#endif
#endif