#ifndef _THREAD_HEAD_
#define _THREAD_HEAD_

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <cstring>
#include "Ts.hpp"
#include "login/login.hpp"

extern "C"{
    #include <fcntl.h>
    #include <netinet/in.h>
    #include <pthread.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include "lvgl/examples/lv_examples.h"
    #include <fcntl.h>
}

// 服务器的ip(目前就是自己ubuntu的ip地址)
#define SERVER_IP "192.168.174.12" //ubuntu
// #define SERVER_IP "192.168.61.1" //windows
// 服务器的端口号(1024 - 65535)
#define SERVER_PORT 60000

using namespace std;

char time_str[100];

class Thread{
    public:
        virtual ~Thread(){}
        virtual void start() = 0;
        virtual void run(void *arg) = 0;//纯虚函数,派生类需要实现

        int openSocket();

        void over(){
            pthread_cancel(thread);
        }

        static void* threadFunc(void *obj){
            static_cast<Thread *>(obj)->run(obj); 
            return NULL;
        }

    protected:
        pthread_t thread;
        int socket_fd;
};

int Thread::openSocket(){
            // 创建套接字
    // AF_INET:ipv4 SOCK_STREAM:tcp
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        printf("socket fail\n");
        return -1;
    }

    #if 0
    // 是否绑定本机
     struct sockaddr_in my_addr;
     my_addr.sin_family = AF_INET;                   // IPv地址族
     my_addr.sin_port = htons(60008);          // 本机端口号转网络端口号
     my_addr.sin_addr.s_addr = inet_addr("192.168.61.2"); // 将本机ip转换为网络ip
     // 绑定本机ip和端口bind
     ret = bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
     if (ret < 0)
     {
         printf("bind fail\n");
         return -1;
     }    
     #endif

     // 链接服务器(需要知道服务器的ip和端口)
     // 填充服务器的ip和端口(将服务器的新的结构体进行初始化)
     struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    // htons:host to net short(主机转网络 端口为short类型)
    server_addr.sin_port = htons(SERVER_PORT); // 需要将本机的端口号转换为网络端口号(小端字节序->大端字节序)
    // 将主机IP(本地IP)转换为网络ip(小端字节序->大端字节序)
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    // connect(socket_fd, (struct sockaddr_in *)&server_addr, sizeof(struct sockaddr_in)); //warning注意函数调用参数的时候要用就结构体的类型
    int ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        perror("connect fail");
        return -1;
    }
    printf("connect server success [%d]\n",socket_fd);

     return 0;
}

class SendThread:public Thread{
    public:
        void start() override{
            SendThread SendTask;
            pthread_create(&thread, NULL, SendThread::threadFunc, &SendTask);
        }
        
        void run(void *arg) override{
            //当线程收到取消请求之后，立即响应,不需要遇到取消点
            pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

            int ret=0;
            // int socket_fd=*((int *)arg);
            char *buff = (char *)arg;
            buff = new char[1024];
            
            while(1)
            {
                ret = send(socket_fd, buff, sizeof(buff), 0);
                printf("send = %s,ret = %d\n",buff,ret);

                usleep(1000000);//500ms
            }

        }
};

class ReceiveThread:public Thread{
    public:
        void start() override{
            ReceiveThread ReceiveTask;
            pthread_create(&thread, NULL, ReceiveThread::threadFunc, &ReceiveTask);
        }

        void run(void *arg) override{
            printf("recv_thread-------------\n");
            //当线程收到取消请求之后，立即响应,不需要遇到取消点
            pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
            int ret=0;
            
            // int socket_fd=*((int *)arg);
            int status = fcntl(socket_fd, F_GETFL); // 得到文件描述符的状态
            status |= O_NONBLOCK;            // 在原来的基础上新增非阻塞属性
            fcntl(socket_fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中
    
            while (1)
            {
                //接收文件内容
                char recv_buf[1024] = {0};
                //打开文件,不存在则创建，可读可写
                int file_fd = open("/nfs/projec03/lvgl_arm/lvgl_extre/res/item.txt",O_RDWR|O_CREAT,0666);
                //循环接收内容，并写到文件中/home/gec/project_talk/lv_port_linux_frame_buffer-master/weather.txt
                while(1)
                {
                    ret = recv(socket_fd, recv_buf, sizeof(recv_buf), 0);
                    if(ret < 0){
                        perror("recv error!");     
                        break;
                    }
                    write(file_fd,recv_buf,ret);
                        
                }
                //关闭文件
                close(file_fd);

                usleep(1000000);//1s

                continue;
            }
        }
};

class TimerThread:public Thread{
    public:
        TimerThread(lv_obj_t *label):label(label){}
        void start() override{
            pthread_create(&thread, NULL, TimerThread::threadFunc, this);
        }

        void run(void *arg) override{
            while(true){
                time_t now = time(0);
                tm* local_time = localtime(&now);

                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
                cout << "当前日期和时间为：" << asctime(local_time) <<endl;
                lv_label_set_text(label, time_str);

                lv_task_handler();

                sleep(1);
            }
            
        }
    private:
        lv_obj_t *label;
};

// class TouchThread:public Thread{
//     public:
//         void start() override{
//             TouchThread TouchTask;
//             pthread_create(&thread, NULL, TouchThread::threadFunc, &TouchTask);
//         }

//         void run(void *arg) override{
//             //当线程收到取消请求之后，立即响应,不需要遇到取消点
//             pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

//             int ret=0;
//             // int socket_fd=*((int *)arg);
//             char *buff = (char *)arg;
//             buff = new char[1024];

//             touch.openTS();
//             touch.get_xy();
            
//             while(1)
//             {
//                 ret = send(socket_fd, buff, sizeof(buff), 0);
//                 printf("send = %d,ret = %d\n",buff,ret);

//                 usleep(1000000);//500ms
//             }
//         }
//     private:
//         Ts touch;
// };

extern void lv_time();

#endif