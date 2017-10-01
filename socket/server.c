/*************************************************************************
	>   文件名: server.c
	>     作者: fujie
	>     邮箱: fujie.me@qq.com
	> 创建时间: 2017-08-07  10:01:25
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define LISTEN_NUM 12 //定义连接请求队列长度
int main(){
    int sock_fd;
    int client_fd;
    int client_len;
    char buf[1024];
    struct sockaddr_in serv_addr;//位于netinet/in.h
    struct sockaddr_in client_addr;
    client_len = sizeof(struct sockaddr_in);
    memset(&client_addr,0,client_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5555);//设置端口号80
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(serv_addr.sin_zero,0,sizeof(serv_addr.sin_zero));
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    
    if(sock_fd < 0) {
        perror("socket");
        exit(0);
    }
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0){
        perror("bind");
        exit(0);
    }
    if(listen(sock_fd,LISTEN_NUM) < 0){
        perror("listen");
        exit(0);
    }

    client_fd = accept(sock_fd , (struct sockaddr *)&client_addr , (socklen_t *)&client_len);
    if(client_fd < 0){
        perror("accept");
        exit(0);
    }
    while(1){
        getchar();
        if(recv(client_fd,(void *)buf , sizeof(buf),0) < 0){
            perror("recv");
            exit(0);
        }
        printf("%s\n",buf);

    }
}
