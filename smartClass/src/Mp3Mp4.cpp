#include "../include/Mp3Mp4.hpp"
#include <iostream>
#include "../include/Bmp.hpp"
#include "../include/Ts.hpp"
#include <thread>
#include <algorithm>

using namespace std;
bool isMediaFinished = false;
static int state = -1;//上一个的状态
string buff;

int Mp3Mp4::playMediaStart() {
    mp34_fp.open("smartClass/res/text/media.txt", ios::in | ios::out);
    if (!mp34_fp.is_open()) {
        perror("打开文件失败！");
        return -1;
    }
    return 0;
}

void Mp3Mp4::playMusic() {
    
    choi = 0;
    string command = "madplay ./smartClass/res/music/" + mp34Name + " &";
    cout << "播放音乐命令：" << mp34Name << endl;
    std::system(command.c_str());
    state = choi;
}

void Mp3Mp4::playMovie() {

    choi = 1;
    string command = "mplayer ./smartClass/res/video/" + mp34Name + " -x 800 -y 480 -Zoom  -geometry 0:0  -loop 0  -quiet &";
    cout << "播放视频命令：" << mp34Name << endl;
    std::system(command.c_str());
    state = choi;
}

void Mp3Mp4::stop() {
    std::system("killall -SIGSTOP madplay");
}

void Mp3Mp4::conti() {
    std::system("killall -SIGCONT madplay");
}

void Mp3Mp4::musicOut() {
    std::system("killall -SIGKILL madplay"); // 退出播放音乐
    std::cout << "尝试停止音乐播放" << std::endl;
}

void Mp3Mp4::movieOut() {
    std::system("killall -SIGKILL mplayer"); // 退出播放视频
    std::cout << "尝试停止视频播放" << std::endl;
}

void Mp3Mp4::setMp34Name(const string &name) {
    mp34Name = name;
}

void Mp3Mp4::displayFile() {
    while(1){
        if (getline(mp34_fp, buff)) {
            buff.erase(remove(buff.begin(), buff.end(), '\n'), buff.end());
            if (buff.find(".mp3") != string::npos) {
                cout << "播放音乐：" << buff << endl;
                mp34Name = buff;
                choi = 0;
                break;
            } else if (buff.find(".mp4") != string::npos) {
                cout << "播放视频：" << buff << endl;
                mp34Name = buff;
                choi = 1;
                break;
            } else {
                perror("没有找到.mp3或.mp4结尾的字符串！");
            }
        }

        if (mp34_fp.eof()){
            cout << "文件读取完成。" << endl;
            mp34_fp.clear();
            mp34_fp.seekg(0, ios::beg);//
        }
        else if(mp34_fp.fail()){
            perror("读取文件时发生错误！");
            mp34_fp.clear();
            break;
        }
            
    }
    
}

void Mp3Mp4::mp34Screen() {
    Bmp b1("smartClass/res/pic/1.bmp");
    Bmp b2("./smartClass/res/pic/2.bmp");
    Bmp b3("./smartClass/res/pic/3.bmp");
    Bmp b4("./smartClass/res/pic/4.bmp");
    Bmp b5("./smartClass/res/pic/5.bmp");
    Bmp b6("./smartClass/res/pic/6.bmp");
    Bmp b7("./smartClass/res/pic/7.bmp");
    
    mediaBmp.display_bmp_picture_to_framebuffer(0, 0, 1.0);
    if (playMediaStart() != 0)
        return;

    displayFile();
    
    if(choi == 0)
        playMusic();
    else if(choi == 1)
        playMovie();
    
    Ts ts;
    ts.openTS();
    int x = 0, y = 0;
    static int num = 0;
    while(1){
        displayFile();
        static string rbuff = mp34Res;//保存当前播放的音乐
        int status = ts.get_xy(&x, &y);
        if(status == 0){
            if((x > 0 && x < 200 && y > 0 && y < 240) || (x > 600 && x < 800 && y > 0 && y < 240)){
                cout << "out" << choi <<endl;
                if(choi == 0){
                    musicOut();
                    break;
                }else if(choi == 1){
                    movieOut();
                    break;
                }
                break;
            }else if(x > 200 && x < 600 && y > 0 && y < 240){
                static int count = 0;
                if(count == 0){
                    Bmp bpause("smartClass/res/pic/pause.bmp");
                    stop();
                    bpause.display_bmp_picture_to_framebuffer(400, 120 , 0.5);
                    sleep(1);
                    bpause.clearCustomDisplay();
                }else{
                    Bmp bplay("smartClass/res/pic/play.bmp");
                    conti();
                    bplay.display_bmp_picture_to_framebuffer(400, 120, 0.5);
                    sleep(1);
                    bplay.clearCustomDisplay();
                }
            }else if(x > 0 && x < 400 && y > 240 && y < 480){
                if(num > 0 && num < 7)
                    // mp34BmpList[num++].display_bmp_picture_to_framebuffer(200, 120, 0.5);
                    b3.display_bmp_picture_to_framebuffer(200, 120, 0.5);
                else if(num == 7){
                    num = 0;
                    // mp34BmpList[num].display_bmp_picture_to_framebuffer(200, 120, 0.5);
                    b4.display_bmp_picture_to_framebuffer(200, 120, 0.5);
                }
                   
                if(choi == 0)
                    mp34Res = "madplay ./smartClass/res/music/" + buff + " &";
                else
                    mp34Res = "mplayer ./smartClass/res/video/" + buff + " -x 800 -y 480 -Zoom  -geometry 0:0  -loop 0  -quiet &";
                if(state == 0)
                    musicOut();
                else
                    movieOut();
                    
                std::system(mp34Res.c_str());
            }else if(x > 400 && x < 800 && y > 240 && y < 480){
                // if(num > 1  && num < 7)
                //     mp34BmpList[num-2].display_bmp_picture_to_framebuffer(200, 120, 0.5);
                // else if(num == 1)
                //     mp34BmpList[6].display_bmp_picture_to_framebuffer(200, 120, 0.5);
                // else
                //     mp34BmpList[5].display_bmp_picture_to_framebuffer(200, 120, 0.5);
                b3.display_bmp_picture_to_framebuffer(200, 120, 0.5);
                if(state == 0)
                    musicOut();
                else
                    movieOut();
                std::system(rbuff.c_str());
            }
        }
    }
    
    ts.closeTS();
    
    sleep(5);

    b1.clearCustomDisplay();
    b2.clearCustomDisplay();
    b3.clearCustomDisplay();

    mp34_fp.close();
    cout << "播放结束。" << endl;
}

void handleTouchEvent2(){
    Mp3Mp4 mediaPlayer;

    mediaPlayer.mp34Screen();
    
    isMediaFinished = true;
}

void createMediaScreen(){
    
    page2 = lv_obj_create(screen);
    if(page2 != NULL){
        cout << "page2 is created" << endl;
        if(screen != NULL)
            cout << "screen is not null" << endl;
    }else
        cout << "page2 is not created" << endl;
    

    lv_obj_set_size(page2, LV_HOR_RES, LV_HOR_RES);
    
    //lvgl背景
    lv_obj_t * img = lv_img_create(page2);//创建背景图片对象
    lv_img_set_src(img, "S:/nfs/project03/lvgl_arm/smartClass/res/pic/media.bmp");//意思是将图片显示在屏幕中间的左侧
    lv_obj_set_size(img, lv_obj_get_width(page2), lv_obj_get_height(page2));//设置图片的大小为屏幕的大小
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); //将图片对象放置在屏幕中间
    
    // customDisplayhandler();
    thread touchThread(handleTouchEvent2);
    touchThread.join();//等待线程结束
    
    // lv_obj_clean(lv_scr_act());//清除当前屏幕上的所有对象
    while(!isMediaFinished){
        lv_task_handler();
        usleep(1000);
    }

    lv_obj_del(page2);

    create_main_screen();
    // lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);//切换到主界面
    
}