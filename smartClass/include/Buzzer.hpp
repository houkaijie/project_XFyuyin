#ifndef _BUZZER_HEAD_
#define _BUZZER_HEAD_

#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>

extern "C"{
    #include <sys/ioctl.h>
}

using namespace std;

#define ON  0
#define OFF 1

class Buzzer{
    public:
        Buzzer():isOpen(false),fdBuzzer(-1),BuzzerPath("/dev/beep"){}
        ~Buzzer(){
            closeBuzzer();
        }

    bool openBuzzer(){
        if(!isOpen){
            fdBuzzer = open(BuzzerPath ,O_RDWR);
            if(fdBuzzer == -1){
                printf("open error!");
                return false;
            }else{
                isOpen = true;
                return true;
            }
        }
        return true;
    }

    void closeBuzzer(){
        if(isOpen){
            close(fdBuzzer);
            fdBuzzer = -1;
            isOpen = false;
        }
    }

    bool isBuzzerOpen() const{
        return isOpen;
    }

    void ioctStatus(){
        static bool status = false;
        ioctl(fdBuzzer, status? OFF : ON, 1);
        status = !status;//切换
    }

        bool isOpen;
        int fdBuzzer;
        char BuzzerPath[20];
};

// extern void run(Buzzer& buzzer);
// extern void signalHandler(int sigBuzz);
// extern void buzzerStart();
extern short beep_status;

#endif