#include "../../lv_examples.h"
#include "login/login.hpp"
#include <assert.h>

#if LV_USE_BTN && LV_BUILD_EXAMPLES

lv_obj_t * btn1;
lv_obj_t * btn2;
lv_obj_t * btn3;
lv_obj_t * btn4;
   
    void event_handler(lv_event_t * e)//图片显示
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("Clicked");
            // 调用函数进入新界面
            createBmpScreen(screen); 
            lv_scr_load(page1); 
        }
    }

    void event_handler2(lv_event_t * e)//mp3、mp4播放
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("Clicked");
            // 调用函数进入新界面
            // lv_obj_clean(screen);//清除当前屏幕上的所有对象
            
            createMediaScreen(); 
            lv_scr_load(page2); 
        }
    }

    void createXFScreen(){
        page3 = lv_obj_create(screen);

        lv_obj_set_size(page3, LV_HOR_RES, LV_HOR_RES);
        
        //lvgl背景
        lv_obj_t * imgXF = lv_img_create(page3);//创建背景图片对象
        lv_img_set_src(imgXF, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
        lv_obj_set_size(imgXF, LV_HOR_RES, LV_HOR_RES);//设置图片的大小为屏幕的大小
        lv_obj_align(imgXF, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间
        
        // customDisplayhandler();
        client_wav(); //识别声音
        
        // lv_obj_clean(lv_scr_act());//清除当前屏幕上的所有对象
        // while(1){
        //     lv_task_handler();
        //     usleep(1000);
        // }

        // lv_obj_del(page3);

        // create_main_screen();

        // lv_obj_t * imgXF = lv_img_create(page3);//创建背景图片对象
        // lv_img_set_src(imgXF, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
        // lv_obj_set_size(imgXF, lv_obj_get_width(page3), lv_obj_get_height(page3));//设置图片的大小为屏幕的大小
        // lv_obj_align(imgXF, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间
        // client_wav(); //识别声音
    }

    void event_handler3(lv_event_t * e)//语音识别
    {
        lv_event_code_t code = lv_event_get_code(e);
        
        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("Clicked");
            // 调用函数进入新界面bv
            // lv_obj_clean(screen);//清除当前屏幕上的所有对象
            // page3 = lv_obj_create(screen);
            // lv_obj_set_size(page3, LV_HOR_RES, LV_VER_RES); // 设置为全屏

            // lv_obj_t * imgXF = lv_img_create(page3);//创建背景图片对象
            // lv_img_set_src(imgXF, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
            // lv_obj_set_size(imgXF, LV_HOR_RES, LV_VER_RES);//设置图片的大小为屏幕的大小
            // lv_obj_align(imgXF, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间

            // lv_task_handler(); //处理任务
            createXFScreen(); //创建新页面

            lv_scr_load(page3); // 加载新页面
            
            // client_wav(); //识别声音
            
            // createXFScreen(); 
            // lv_scr_load(page3); 
            // LV_LOG_USER("语音识别");
        }
    }

    void event_handler4(lv_event_t * e)//led、beep
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("Clicked");
            // // 调用函数进入新界面
            // lv_example_btn_2();
            createLedBeepScreen(); 
            // lv_scr_load(page4); 
        }
    }



void lv_example_btn_1(lv_obj_t * screen)
{
    // lv_obj_t * label;

    // lv_obj_t * btn1 = lv_btn_create(screen);//意思是将btn1添加到当前屏幕上
    // lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);//添加事件回调
    // lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);//将btn1的位置调整到屏幕中间下方

    // label = lv_label_create(btn1);//创建label并将其添加到btn1中
    // lv_label_set_text(label, "Button");//设置label的文本
    // lv_obj_center(label);//将label的位置调整到btn1的中心

    // lv_obj_t * btn2 = lv_btn_create(screen);//创建btn2并将其添加到当前屏幕上
    // lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);//添加事件回调
    // lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);//将btn2的位置调整到屏幕中间上方
    // lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);//设置btn2为可选按钮
    // lv_obj_set_height(btn2, LV_SIZE_CONTENT);//设置btn2的高度为内容高度

    // label = lv_label_create(btn2);//创建label并将其添加到btn2中
    // lv_label_set_text(label, "Toggle");//设置label的文本
    // lv_obj_center(label);//将label的位置调整到btn2的中心
    
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

    btn1 = lv_btn_create(screen);//创建按钮
    lv_obj_remove_style_all(btn1);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn1, &style, 0);//添加默认样式
    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    // lv_obj_center(btn1);//居中
    lv_obj_set_pos(btn1, 200, 260);//设置位置
    //点了该按钮后，led_status的值为0
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn2 = lv_btn_create(screen);//创建按钮
    lv_obj_remove_style_all(btn2);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn2, &style, 0);//添加默认样式
    lv_obj_add_style(btn2, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn1的下方
    lv_obj_set_pos(btn2, 300, 340);//设置位置
    lv_obj_add_event_cb(btn2, event_handler2, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象


    btn3 = lv_btn_create(screen);//创建按钮
    lv_obj_remove_style_all(btn3);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn3, &style, 0);//添加默认样式
    lv_obj_add_style(btn3, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn3, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn2的下方
    lv_obj_set_pos(btn3, 100, 260);//设置位置
    lv_obj_add_event_cb(btn3, event_handler4, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

    btn4 = lv_btn_create(screen);//创建按钮
    lv_obj_remove_style_all(btn4);//移除默认样式                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn4, &style, 0);//添加默认样式
    lv_obj_add_style(btn4, &style_pr, LV_STATE_PRESSED);//添加按下样式
    lv_obj_set_size(btn4, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//设置大小
    //在btn3的下方
    lv_obj_set_pos(btn4, 50, 340);//设置位置
    lv_obj_add_event_cb(btn4, event_handler3, LV_EVENT_CLICKED, NULL);//添加事件回调,第三个参数意思是回调的绑定对象

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
    static lv_style_t styleFont;
    lv_style_init(&styleFont);
    lv_color_t c = lv_color_hex(0xFFFFFFFF);//定义颜色值
    lv_style_set_text_font(&styleFont, info.font);//设置该样式制定的字体--上面的
    lv_style_set_text_align(&styleFont, LV_TEXT_ALIGN_CENTER);//设置该样式的文本对齐
    lv_style_set_text_color(&styleFont,c);//设置该样式文本颜色

    /*将上面字体添加到下面的lvgl样式对象中*/
    static lv_style_t styleFont1;
    lv_style_init(&styleFont1);
    lv_color_t c1 = lv_color_hex(0xFF0000FF);//定义颜色值
    lv_style_set_text_font(&styleFont1, info1.font);//设置该样式制定的字体--上面的
    lv_style_set_text_align(&styleFont1, LV_TEXT_ALIGN_CENTER);//设置该样式的文本对齐
    lv_style_set_text_color(&styleFont1,c1);//设置该样式文本颜色

    lv_obj_t * label = lv_label_create(btn1);//创建标签
    lv_obj_add_style(label, &styleFont, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label, "图片显示");//设置标签文字
    lv_obj_center(label);//居中
    lv_obj_set_style_text_color(label, lv_color_darken(lv_color_white(), 2), 0);//设置文字颜色

    lv_obj_t * label2 = lv_label_create(btn2);//创建标签
    lv_obj_add_style(label2, &styleFont1, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label2, "MP3/Mp4播放");//设置标签文字
    lv_obj_center(label2);//居中
    lv_obj_set_style_text_color(label2, lv_color_darken(lv_color_black(), 2), 0);//设置文字颜色

    lv_obj_t * label3 = lv_label_create(btn3);//创建标签
    lv_label_set_text(label3, "Led/Beep");//设置标签文字
    lv_obj_center(label3);//居中
    lv_obj_set_style_text_color(label3, lv_color_black(), 0);//设置文字颜色

    lv_obj_t * label4 = lv_label_create(btn4);//创建标签
    lv_obj_add_style(label4, &styleFont1, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(label4, "语音识别");//设置标签文字
    lv_obj_center(label4);//居中
    lv_obj_set_style_text_color(label4, lv_color_black(), 0);//设置文字颜色

}
#endif
