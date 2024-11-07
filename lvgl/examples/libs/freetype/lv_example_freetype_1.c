#include "../../lv_examples.h"
#if LV_BUILD_EXAMPLES
#if LV_USE_FREETYPE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char wea_show[100];
/**
 * Load a font with FreeType
 */
void lv_example_freetype_1(void)
{
    
    //打开文件,只读方式打开
    // FILE *fp = fopen("/nfs/project_talk/lvgl_arm/weather.txt", "r");
    // if(fp == NULL){
    //     printf("open file failed.\n");
    //     return;
    // }
    // fseek(fp, 0, SEEK_SET);
    // //定义一个存放三个字符串的数组
    // char str[4][100] = {0};
    // char buf[100];
    // //按行读取文件，将每行内容到str数组中
    // int i = 0;
    // while(i < 4 && fgets(buf, sizeof(buf), fp)!= NULL)
    // {
    //     strcat(str[i], buf);
    //     i++;
    // }
    
    
    // //关闭文件
    // fclose(fp);

    // printf(" %s\n", str[0]);
    // printf(" %s\n", str[1]);
    // printf(" %s\n", str[2]);

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



    // /*创建一个文本对象并用上面的样式添加给该对象*/
    // lv_obj_t * label = lv_label_create(lv_scr_act());//创建文本对象
    // lv_obj_add_style(label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    // lv_label_set_text(label, str[0]);//设置文本对象的文本内容
    // lv_obj_set_pos(label, 500,10);//设置文本对象的位置
    // lv_obj_set_style_text_color(label, lv_color_hex(0x0000FF), 0);//字体颜色

    // lv_obj_t * label1 = lv_label_create(lv_scr_act());//创建文本对象
    // lv_obj_add_style(label1, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    // lv_label_set_text(label1, str[1]);//设置文本对象的文本内容
    // lv_obj_set_pos(label1, 500, 55);//设置文本对象的位置

    // lv_obj_t * label2 = lv_label_create(lv_scr_act());//创建文本对象
    // lv_obj_add_style(label2, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    // lv_label_set_text(label2, str[2]);//设置文本对象的文本内容
    // lv_obj_set_pos(label2, 500, 100);//设置文本对象的位置

    // lv_obj_t * label3 = lv_label_create(lv_scr_act());//创建文本对象
    // lv_obj_add_style(label3, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    // lv_label_set_text(label3, str[3]);//设置文本对象的文本内容
    // lv_obj_set_pos(label3, 500, 145);//设置文本对象的位置

    lv_obj_t * label4 = lv_label_create(lv_scr_act());//创建文本对象
    lv_obj_add_style(label4, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label4, "LED灯");//设置文本对象的文本内容
    lv_obj_set_pos(label4, 580, 340);//设置文本对象的位置
    lv_obj_set_style_text_color(label4, lv_color_hex(0x00FF00), 0);//字体颜色

    lv_obj_t * label5 = lv_label_create(lv_scr_act());//创建文本对象
    lv_obj_add_style(label5, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label5, "蜂鸣器");//设置文本对象的文本内容
    lv_obj_set_pos(label5, 575, 390);//设置文本对象的位置
    lv_obj_set_style_text_color(label5, lv_color_hex(0xFF0000), 0);//字体颜色
    
}

#else

void lv_example_freetype_1(void)
{
    /*TODO
     *fallback for online examples*/

    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "FreeType is not installed");
    lv_obj_center(label);
}

#endif
#endif
