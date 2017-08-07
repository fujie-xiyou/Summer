/*************************************************************************
	>   文件名: test.c
	>     作者: fujie
	>     邮箱: fujie.me@qq.com
	> 创建时间: 2017-08-07  10:01:25
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
    struct sockaddr_in serv_addr;//位于netinet/in.h
    int sock_fd;
    serc_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);//设置端口号80
    serv_addr.s_addr = htonl(INADDR_ANY);
    memset(serv_addr.sin_zero,0.sizeof(serv_addr.sin_zero));
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    
    if(sock_fd < 0) {
        perror("socket");
        exit(0);
    }
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0){
        perror("bind");
        exit(0);
    }
}
