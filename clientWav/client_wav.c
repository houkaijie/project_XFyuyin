#include "client_wav.h"

void play_voice()
{
	//创建套接字
	int sock_fd = socket(PF_INET,SOCK_STREAM,0);
	printf("001\n");
	//绑定地址(IP+PORT)
	struct sockaddr_in srvaddr;
	srvaddr.sin_family = PF_INET;
	//端口
	srvaddr.sin_port = htons(66666);		
	//IP地址
	srvaddr.sin_addr.s_addr = inet_addr("192.168.174.12");	
	printf("002\n");
	//发起连接请求
	connect(sock_fd,(struct sockaddr *)&srvaddr,sizeof(srvaddr));
	printf("003\n");
	// int flags = fcntl(sock_fd, F_GETFL, 0);
	// fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);
	// printf("004\n");

	int fd = open("1.wav",O_RDWR);
	if(fd < 0)
	{
		perror("open() failed");
		return;
	}
	//获取文件总字节数
	int file_size = lseek(fd,0,SEEK_END);
	//将文件光标偏移到文件开头
	lseek(fd,0,SEEK_SET);
	send(sock_fd,&file_size,4,0);
	printf("file_size = %d\n",file_size);

	char buf[1024] = {0};
	int ret_rd;

	while(1)
	{
		bzero(buf,1024);
		ret_rd = read(fd,buf,1024);
		printf("ret_rd = %d\n",ret_rd);
		if(ret_rd == 0)	//发送完毕
		{
			printf("发送完毕\n");
			break;
		}
		if(send(sock_fd,buf,ret_rd,0) < 0){
			perror("send() failed");
			break;
		}
		if(ret_rd < 1024)
		{
			printf("send over\n");
			break;
		}
	}

	bzero(buf,100);
	printf("等待接收数据\n");

	fd_set rset;// 声明一个文件描述符集合
	struct timeval timeout;
	int total_wait_time = 0; // 统计总的等待时间
    int wait_duration = 1; // 每次检查时等待1秒

	while(total_wait_time < 20){
		FD_ZERO(&rset);
		FD_SET(sock_fd,&rset);

		timeout.tv_sec = wait_duration;
		timeout.tv_usec = 0;

		int ret = select(sock_fd+1,&rset,NULL,NULL,&timeout);// 使用select进行超时检测
		if(ret == 0)//超时
		{
			total_wait_time += wait_duration;// 累加已等待时间
			printf("等待中，已等待总计 %d 秒\n", total_wait_time);
			continue;
		}
		if(ret < 0)//出错
		{
			printf("select error\n");
			close(sock_fd);
			close(fd);
			lv_obj_del(page3);
			create_main_screen();
			return;
		}

		if(FD_ISSET(sock_fd,&rset)){
			recv(sock_fd,buf,100,0);
			lv_obj_del(page3);
			if(strstr(buf,"相册") != NULL)  //匹配相册成功
			{
				//play_photo();
				printf("play photo\n");
				createBmpScreen(); 
				lv_scr_load(page1); 
				create_main_screen();
			}
			if(strstr(buf,"音乐") != NULL)  //匹配音乐成功
			{
				//play_music();
				printf("play music\n");
				createMediaScreen(); 
				lv_scr_load(page2); 
				create_main_screen();
			}
			if(strstr(buf,"视频") != NULL)  //匹配视频成功
			{
				//play_video();
				printf("play video\n");
				createMediaScreen(); 
				lv_scr_load(page2); 
				create_main_screen();
			}
			if(strstr(buf,"灯") != NULL){
				createLedBeepScreen(); 
				lv_scr_load(page4);
				create_main_screen();
			}
			if(strstr(buf,"蜂鸣器") != NULL){
				createLedBeepScreen(); 
				lv_scr_load(page4);
				create_main_screen();
			}
			if(strstr(buf,"没有识别结果") != NULL)
			{
				printf("没有识别结果");
				create_login(screen);
			}
			break;
		}

	}
	
	// 超时处理
    if (total_wait_time >= 20) {
        printf("接收超时结束，退出\n");
        lv_obj_del(page3);
        create_main_screen();
    }
	
	//关闭套接字
	close(sock_fd);
	close(fd);
}

int client_wav()
{
	printf("开始录音\n");
	system("arecord -d3 -c1 -r16000 -twav -fS16_LE 1.wav");
	play_voice();	
	return 0;
}