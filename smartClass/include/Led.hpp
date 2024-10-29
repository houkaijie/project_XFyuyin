#ifndef _LED_HEAD_
#define _LED_HEAD_

#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstdio>
#include "login/login.hpp"

extern "C"{
    #include <sys/ioctl.h>
    #include "lvgl/lvgl.h"
    #include "lvgl/demos/lv_demos.h"
    #include "lvgl/examples/lv_examples.h"
    #include "../lvgl/examples/widgets/lv_example_widgets.h"

    void ledBeep(){
        lv_example_btn_2();
    }
}

#define TEST_MAGIC 'x'                    //定义幻数

#define LED1 _IO(TEST_MAGIC, 0)              
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3) 

#define LED_ON  	0	//灯亮
#define LED_OFF		1   //灯灭


class Led{
    public:
        Led():isOpen(false),fdLed(-1),LedPath("/dev/Led"){}
        ~Led(){
            closeLed();
        }

    bool openLed(){
        if(!isOpen){
            fdLed = open(LedPath ,O_RDWR);
            if(fdLed == -1){
                printf("open error!");
                return false;
            }else{
                isOpen = true;
                return true;
            }
        }
        return true;

    }

    void closeLed(){
        if(isOpen){
            close(fdLed);
            fdLed = -1;
            isOpen = false;
        }
    }

    bool isLedOpen() const{
        return isOpen;
    }

    void ioctStatus(){
        static bool status = false;
        if(!status){
            ioctl(fdLed, LED1, LED_ON);
            ioctl(fdLed, LED2, LED_ON);
            ioctl(fdLed, LED3, LED_ON);
            ioctl(fdLed, LED4, LED_ON);
        }else{
            ioctl(fdLed,LED1,LED_OFF);
            ioctl(fdLed,LED2,LED_OFF);
            ioctl(fdLed,LED3,LED_OFF);
            ioctl(fdLed,LED4,LED_OFF);
        }
        status = !status;
    }

        bool isOpen;
        int fdLed;
        char LedPath[20];
};

// extern void run(Led& led);
// extern void signalHandler(int sigLed);
// extern void ledStart();

extern lv_obj_t * led1;
extern lv_obj_t * led2;
extern int led_status;

#endif