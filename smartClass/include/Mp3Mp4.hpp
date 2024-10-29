#ifndef _MP3MP4_HEAD_
#define _MP3MP4_HEAD_

#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Bmp.hpp"
#include "Ts.hpp"
#include "login/login.hpp"

using namespace std;

// int mp34Choice;
string mp34Res;
static int choi = -1;

class Mp3Mp4{
    public:
        Mp3Mp4(const char name[20] = "smartClass/res/pic/media.bmp"):mediaBmp(name),mediaTs(),mp34_fp(NULL){}
        ~Mp3Mp4(){
            if(mp34_fp.is_open()){
                mp34_fp.close();
            }
        }

        int playMediaStart();
        void playMusic();

        void playMovie();

        void stop();

        void conti();

        void musicOut();

        void movieOut();

        void setMp34Name(const string &name);

        void displayFile();

        void mp34Screen();

        Bmp mediaBmp; // 处理屏幕显示  
        Ts mediaTs; // 处理触摸事件
        string mp34Name; // 音乐或视频文件名
        ifstream mp34_fp; // 文件流
        vector<Bmp> mp34BmpList; // 音乐或视频图片列表
        // int choi; // 选择播放音乐0或视频1
        // list<string> mp34List; // 音乐或视频列表
        
};

void handleTouchEvent2();

#endif