#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "login/login.hpp"
#include "smartClass/include/Menu.hpp"


/*------------------socket通信部分------------------*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
// #include <sys/socket.h>
// #include <netinet/in.h> //man 3 inet_addr
// #include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// #define TEST_MAGIC 'x'                    //定义幻数

// #define LED1 _IO(TEST_MAGIC, 0)              
// #define LED2 _IO(TEST_MAGIC, 1)
// #define LED3 _IO(TEST_MAGIC, 2)
// #define LED4 _IO(TEST_MAGIC, 3)

// #define LED_ON  	0	//灯亮
// #define LED_OFF		1   //灯灭

extern lv_obj_t * led1;
extern lv_obj_t * led2;
bool video_finished = false;
lv_obj_t *main_screen;

// // 服务器的ip(目前就是自己ubuntu的ip地址)
// #define SERVER_IP "192.168.174.12" //ubuntu
// // #define SERVER_IP "192.168.61.1" //windows
// // 服务器的端口号(1024 - 65535)
// #define SERVER_PORT 60000

void lv_example_png_1(lv_obj_t *);
void lv_example_freetype_1(void);
void lv_time(lv_obj_t *);
// void lv_example_btn_2(void);
void lv_example_btn_1(lv_obj_t *);
void lv_example_led_1(void);
void create_main_screen();

// void create_login(lv_obj_t *parent);


// //子线程用来发送数据
// void *send_thread(void *arg)
// {
//     //当线程收到取消请求之后，立即响应,不需要遇到取消点
//     pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

//     int ret=0;
//     int socket_fd=*((int *)arg);
    
//     int prev_led_status = 2;
//     short prev_beep_status = 2;
//     while(1)
//     {
        
//         if(led_status != 2)
//         {
//             if(led_status != prev_led_status)
//             {
//                 ret = send(socket_fd, &led_status, sizeof(led_status), 0);
//                 printf("send_led_status = %d,ret = %d\n",led_status,ret);
//                 prev_led_status = led_status;
//             }
            
//         }

//         if(beep_status != 2)
//         {
//             if(beep_status != prev_beep_status)
//             {
//                 ret = send(socket_fd, &beep_status, sizeof(beep_status), 0);
//                 printf("send_beep_status = %d,ret = %d\n",beep_status,ret);
//                 prev_beep_status = beep_status;
//             }
            
//         }

//         usleep(1000000);//500ms
        
//     }


// }

// //子线程用来接收数据
// void *recv_thread(void *arg)
// {
//     printf("recv_thread-------------\n");
//     //当线程收到取消请求之后，立即响应,不需要遇到取消点
//     pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
//     int ret=0;
//     int recv_status = 2;
//     // int led_ret=0;
//     // short beep_ret=0;
//     int socket_fd=*((int *)arg);
//     int status = fcntl(socket_fd, F_GETFL); // 得到文件描述符的状态
//     status |= O_NONBLOCK;            // 在原来的基础上新增非阻塞属性
//     fcntl(socket_fd, F_SETFL, status);      // 把变量status的状态设置到文件描述符中
//     pthread_mutex_t mutex;
    
//     // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//静态初始化互斥锁

//     while (1)
//     {
        
//         if(weather_status == 1)
//         {
//             //接收文件内容
//             char recv_buf[1024] = {0};
//             //打开文件,不存在则创建，可读可写
//             int file_fd = open("/nfs/project_talk/lvgl_arm/weather.txt",O_RDWR|O_CREAT,0666);
//             //循环接收内容，并写到文件中/home/gec/project_talk/lv_port_linux_frame_buffer-master/weather.txt
//             while(1)
//             {
//                 ret = recv(socket_fd, recv_buf, sizeof(recv_buf), 0);
//                 if(ret < 0)
//                 {                    
//                     break;
//                 }
//                 write(file_fd,recv_buf,ret);
                
//             }
//             //关闭文件
//             close(file_fd);

//             weather_status = 0; 
//             printf("recv weather success\n");
//             continue;
//         }
//         pthread_mutex_init(&mutex, NULL);//动态初始化互斥锁
//         pthread_mutex_lock(&mutex);//加互斥锁
//         ret = recv(socket_fd, &recv_status, sizeof(recv_status), 0);     
//         if(ret == 4)
//         {
//             if(recv_status == 0)
//             {

//                 lv_led_on(led1);

//             }
//             else if(recv_status == 1 )
//             {

//                 lv_led_off(led1);

//             }
//             recv_led_status = recv_status;
//             led_status = recv_led_status;
//             printf("recv_led_status = %d,led_ret = %d\n",led_status,ret);
//             ioctl(fd_led, LED1, led_status);
//             ioctl(fd_led, LED2, led_status);
//             ioctl(fd_led, LED3, led_status);
//             ioctl(fd_led, LED4, led_status);
            
//         }
//         else if(ret == 2)
//         {   
//             if(recv_status == 0 )
//             {
                
//                 lv_led_on(led2);
                
//             }
//             else if(recv_status == 1 )
//             {
                
//                 lv_led_off(led2);
                
//             }
//             recv_beep_status = recv_status;
//             beep_status = recv_beep_status;
//             printf("recv_beep_status = %d,beep_ret = %d\n",beep_status,ret);
//             ioctl(fd_beep,beep_status,1);
            
//         }
//         pthread_mutex_unlock(&mutex);//解锁互斥锁
        
//         if(ret == 0)
//         {
//             printf("服务器正在维护中下线了\n");
//             exit(0);
//         }

//         usleep(1000000);//1s
//     }


// }
/*------------------socket通信部分-*/

#define DISP_BUF_SIZE (480 * 800)

void play_video(){
    //播放开机视频
    system("mplayer ./smartClass/res/video/openScreen.mp4 -x 800 -y 480 -Zoom  -geometry 0:0  -loop 0  -quiet &");

    sleep(10);

    system("killall -SIGKILL mplayer");
    // 播放开机视频并等待完成
    // FILE* video_process = popen("mplayer ./smartClass/res/video/openScreen.mp4 -x 800 -y 480 -Zoom -geometry 0:0 -loop 0 -quiet", "r");
    // if (video_process) {
    //     sleep(20); // 等待视频播放完毕
    //     pclose(video_process); // 关闭视频进程
    // }
    
    video_finished = true;//播放完毕
}

// void createLedBeepScreen(){
//     //创建指示灯和蜂鸣器界面
//     lv_example_btn_2();

// }

void create_main_screen(){
    
    screen = lv_obj_create(NULL);//创建主界面

    lv_example_png_1(screen);//显示iot主界面
    
    lv_time(screen);//显示时间
    lv_example_btn_1(screen);//按钮

    lv_scr_load(screen);//显示主界面
   
}

int main(void)
{
    /*lvgl初始化*/
    lv_init();


    /*输出设备初始化及注册*/
    fbdev_init();
    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];
    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    //输入设备初始化及注册
    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/

    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /*socket通信部分-----------------------------------------------------------------------------------------*/
    // int fd = open("/dev/Led",O_RDWR);
    // ioctl(fd, LED1, LED_OFF);
    // ioctl(fd, LED2, LED_OFF);
    // ioctl(fd, LED3, LED_OFF);
    // ioctl(fd, LED4, LED_OFF);
    // close(fd);
    // int ret = 0;  

    // 创建套接字
    // AF_INET:ipv4 SOCK_STREAM:tcp
    // int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (socket_fd < 0)
    // {
    //     printf("socket fail\n");
    //     return -1;
    // }

    // #if 0
    // // 是否绑定本机
    // struct sockaddr_in my_addr;
    // my_addr.sin_family = AF_INET;                   // IPv地址族
    // my_addr.sin_port = htons(60008);          // 本机端口号转网络端口号
    // my_addr.sin_addr.s_addr = inet_addr("192.168.61.2"); // 将本机ip转换为网络ip
    // // 绑定本机ip和端口bind
    // ret = bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
    // if (ret < 0)
    // {
    //     printf("bind fail\n");
    //     return -1;
    // }    
    // #endif

    // // 链接服务器(需要知道服务器的ip和端口)
    // // 填充服务器的ip和端口(将服务器的新的结构体进行初始化)
    // struct sockaddr_in server_addr;
    // server_addr.sin_family = AF_INET;
    // // htons:host to net short(主机转网络 端口为short类型)
    // server_addr.sin_port = htons(SERVER_PORT); // 需要将本机的端口号转换为网络端口号(小端字节序->大端字节序)
    // // 将主机IP(本地IP)转换为网络ip(小端字节序->大端字节序)
    // server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    // // connect(socket_fd, (struct sockaddr_in *)&server_addr, sizeof(struct sockaddr_in)); //warning注意函数调用参数的时候要用就结构体的类型
    // ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    // if (ret < 0)
    // {
    //     perror("connect fail");
    //     return -1;
    // }
    // printf("connect server success [%d]\n",socket_fd);

    // // 与服务器建立连接后，开启子线程接收数据
    // pthread_t thread_recv;
    // pthread_create(&thread_recv,NULL,recv_thread,(void *)&socket_fd);
    // if(ret != 0)
    // {
    //     printf("pthread_create fail\n");
    //     return -1;
    // }


    // // 与服务器建立连接后，开启子线程发送数据
    // pthread_t thread_send;
    // pthread_create(&thread_send,NULL,send_thread,(void *)&socket_fd);
    // if(ret != 0)
    // {
    //     printf("pthread_create fail\n");
    //     return -1;
    // }

    // fd_led = open("/dev/Led",O_RDWR);
    // fd_beep = open("/dev/beep", O_RDWR);


    play_video();//播放开机视频

    if(video_finished){
        loginScreen = lv_obj_create(NULL);
        // lv_obj_clean(screen);
        
        create_login(loginScreen);//登录界面
        lv_scr_load(loginScreen);//显示登录界面
        // sleep(10);
    }
    
    // lv_src_load(screen);//显示主界面

    // lv_example_freetype_1();//显示天气
    // lv_example_btn_2();//按钮
    // lv_example_led_1();//指示灯


    /*事物处理及告知lvgl节拍数*/
    while(1) {
        lv_timer_handler();//事务处理
        lv_tick_inc(5);//节拍累计
        usleep(5000);
    }

    /*关闭socket通信部分-*/
    // close(socket_fd);
    // close(fd_led);
    // close(fd_beep);
    return 0;
}


/*用户节拍获取*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
