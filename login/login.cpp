#include <fstream>
#include "login.hpp"

using namespace std;

lv_obj_t * username_textbox;//全局文本框
lv_obj_t * password_textbox;
lv_obj_t *status_label;//全局状态标签

lv_obj_t *screen;
lv_obj_t *loginScreen;
lv_obj_t *page1;
lv_obj_t *page2;
lv_obj_t *page3; 
lv_obj_t *page4; 

ofstream create_file(const char *filename){
    ofstream file(filename, ios::out | ios::trunc); // 以输出模式打开文件，并清空文件内容
    if (file.is_open()) {
        return file; // 返回成功打开的文件流对象
    } else {
        LV_LOG_ERROR("无法创建文件");
        return ofstream(); // 返回一个默认的ofstream对象表示失败
    }
}

// 键盘输入事件处理函数
void textarea_event_handler(lv_event_t * e) {
    static lv_obj_t * keyboard; // 定义一个全局变量来保存键盘对象
    lv_obj_t * textarea = lv_event_get_target(e); // 获取触发事件的文本框对象
    
    if(lv_event_get_code(e) == LV_EVENT_FOCUSED) {//focused焦点事件
        if(keyboard == NULL){
            keyboard = lv_keyboard_create(lv_scr_act());
            lv_keyboard_set_textarea(keyboard, textarea); // 设置键盘关联的文本框
        }else{
            lv_obj_del(keyboard); // 删除旧的键盘对象
            keyboard = NULL;
        }
    }

    const char *text = lv_textarea_get_text(textarea); // 获取当前文本框中的文本

    LV_LOG_INFO("Textarea Pointer: %p", textarea); // 打印指针信息
    LV_LOG_INFO("Text Pointer: %p", text); // 打印文本指针信息

    if(text != NULL && strlen(text) > 0)
        LV_LOG_INFO("当前输入: %s", text);
    else if(lv_event_get_code(e) == LV_EVENT_DEFOCUSED)
        LV_LOG_WARN("当前输入为空");
}

bool compareLogin(const char *username, const char *password) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        LV_LOG_ERROR("open file failed.");
        return false;
    }
    
    file.seekg(0, ios::beg);
    string line;
    while (getline(file, line)) {
        string::size_type pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string passwd = line.substr(pos+1);
            if (name == username && passwd == password) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

// 登录按钮的事件处理函数
void login_event_handler(lv_event_t * e) {
    // 获取用户名和密码 
    const char *username = lv_textarea_get_text(username_textbox);
    const char *password = lv_textarea_get_text(password_textbox);
    
    // 添加这里实际的验证逻辑，例如：
    if (compareLogin(username, password)) {
        // 登录成功逻辑
        LV_LOG_INFO("登录成功");
        lv_label_set_text(status_label, "登录成功");

            // 跳转到主界面
        create_main_screen();
        lv_scr_load(screen);
    } else {
        // 登录失败逻辑
        LV_LOG_WARN("登录失败");
        lv_label_set_text(status_label, "登录失败");
    }   
}

bool is_user_exist(const char *username) {
    ifstream file("users.txt", ios::in);
    if (!file.is_open()) {
        LV_LOG_ERROR("open file failed.");
        return false;
    }

    string line;
    while (getline(file, line)) {
        string::size_type pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            if (name == username) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

// 注册按钮的事件处理函数
void register_event_handler(lv_event_t * e) {
    const char *username = lv_textarea_get_text(username_textbox);
    const char *password = lv_textarea_get_text(password_textbox);
    
    // 检查用户是否已存在
    if (is_user_exist(username)) {
        LV_LOG_WARN("用户已存在");
        return; // 提示用户已存在
    }

    // 注册用户/home/gec/project03/lvgl_arm/smartClass/res/text/./users.txt
    ofstream file("users.txt", ios::app); // 以追加模式打开文件
    if (file.is_open()) {
        file << username << "," << password << "\n"; // 写入新用户
        file.close();
        LV_LOG_INFO("注册成功");
    } else {
        LV_LOG_ERROR("无法打开用户文件进行注册");
        file = create_file("users.txt"); // 创建文件
        if (!file.is_open()) {
           LV_LOG_ERROR("无法创建文件");
           return;
        }
    }
}

void create_login(lv_obj_t *loginScreen) {
    // lv_obj_t *loginScreen
    // lv_obj_clean(); // 清空父对象

    //背景图片
    lv_obj_t * img = lv_img_create(loginScreen);//创建背景图片对象
    lv_img_set_src(img, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/login.jpg");//意思是将图片显示在屏幕中间的左侧
    lv_obj_set_size(img, lv_obj_get_width(loginScreen), lv_obj_get_height(loginScreen));//设置图片的大小为屏幕的大小
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间

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

    //  /*创建另一个字体*/
    // static lv_ft_info_t info1;//定义一个记录freetype字体信息的结构体
    // /*记录字体文件路径 字号大小-单位借用  字体风格*/
    // info1.name = "/font/simfang.ttf";//字体文件名---华文行楷--文件已经放在开发板中
    // info1.weight = 48;//字号
    // info1.style = FT_FONT_STYLE_NORMAL;//字体风格
    // info1.mem = NULL;//指向字体数据的指针 一般要显示字体时，就会从上面字体文件中获取对应数据 freetype转换为位图数据 ，而mem指针指向这块数据
    // //初始化
    // if(!lv_ft_font_init(&info1)){ 
    //     LV_LOG_ERROR("create failed.");
    // }

    /*将上面字体添加到下面的lvgl样式对象中*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_color_t c = lv_color_hex(0xFFFFFFFF);//定义颜色值
    lv_style_set_text_font(&style, info.font);//设置该样式制定的字体--上面的
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);//设置该样式的文本对齐
    lv_style_set_text_color(&style,c);//设置该样式文本颜色

    /*将上面字体添加到下面的lvgl样式对象中*/
    // static lv_style_t style1;
    // lv_style_init(&style1);
    // lv_color_t c1 = lv_color_hex(0xFF000FFF);//定义颜色值
    // lv_style_set_text_font(&style1, info1.font);//设置该样式制定的字体--上面的
    // lv_style_set_text_align(&style1, LV_TEXT_ALIGN_CENTER);//设置该样式的文本对齐
    // lv_style_set_text_color(&style1,c1);//设置该样式文本颜色

    // // 创建标题标签
    // lv_obj_t *label = lv_label_create(loginScreen);
    // lv_obj_add_style(label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    // lv_obj_set_pos(label, 50, 50);
    // lv_label_set_text(label, "登录");

    // 创建用户名标签
    lv_obj_t *username_label = lv_label_create(loginScreen);
    lv_obj_add_style(username_label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(username_label, "用户名:");
    lv_obj_align(username_label, LV_ALIGN_CENTER, -150, -20);

    // 创建用户名文本框
    username_textbox = lv_textarea_create(loginScreen);
    lv_obj_set_size(username_textbox, 200, 30);
    lv_obj_align(username_textbox, LV_ALIGN_CENTER, 0, -20);
    lv_textarea_set_one_line(username_textbox, true); // 设置为单行模式
    lv_obj_add_event_cb(username_textbox, textarea_event_handler, LV_EVENT_FOCUSED, NULL);// 添加文本框事件回调
    // lv_label_set_text(username_label, str[0]);

    // 创建密码标签
    lv_obj_t *password_label = lv_label_create(loginScreen);
    lv_obj_add_style(password_label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(password_label, "密码:");
    lv_obj_align(password_label, LV_ALIGN_CENTER, -150, 20);

    // 创建密码文本框
    password_textbox = lv_textarea_create(loginScreen);
    lv_obj_set_size(password_textbox, 200, 30);
    lv_textarea_set_password_mode(password_textbox, true); // 设置为密码模式
    lv_obj_align(password_textbox, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(password_textbox, textarea_event_handler, LV_EVENT_FOCUSED, NULL);// 添加文本框事件回调
    // lv_label_set_text(password_label, str[1]);

    // 创建登录按钮
    lv_obj_t *login_button = lv_btn_create(loginScreen);
    lv_obj_align(login_button, LV_ALIGN_CENTER, -60, 80);
    lv_obj_set_size(login_button, 100, 40);

    lv_obj_t* login_label = lv_label_create(login_button);
    lv_obj_add_style(login_label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(login_label, "登录");
    lv_obj_center(login_label);

    // 创建注册按钮
    lv_obj_t *register_button = lv_btn_create(loginScreen);
    lv_obj_align(register_button, LV_ALIGN_CENTER, 60, 80);
    lv_obj_set_size(register_button, 100, 40);

    lv_obj_t* register_label = lv_label_create(register_button);
    lv_obj_add_style(register_label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_label_set_text(register_label, "注册");
    lv_obj_center(register_label);

    // 创建状态标签
    status_label = lv_label_create(loginScreen);
    lv_obj_add_style(status_label, &style, 0);//添加上面的style对象给label对象  参数3为0代表该样式是默认样式，不需要某个事件触发
    lv_obj_set_pos(status_label, 50, 300);
    lv_label_set_text(status_label, "请登录");

    // 添加按钮回调函数
    lv_obj_add_event_cb(login_button, login_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(register_button, register_event_handler, LV_EVENT_CLICKED, NULL);
}
