/*************************************************************************
	>    File Name: client.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月07日 星期一 10时24分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<linux/socket.h>
#include<arpa/inet.h>
int main(){
    struct sockaddr_in clie_addr;
    int sock_fd;
    char buf[1024] = "我擦破收到卡卡";
    memset(&clie_addr , 0 ,sizeof(struct sockaddr_in));
    clie_addr.sin_family = AF_INET;
    clie_addr.sin_port = htons(5555);
    clie_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(sock_fd < 0){
        perror("socket");
        exit(0);
    }
    //inet_aton("182.254.141.65",&clie_addr.sin_addr);
    if(connect(sock_fd , (struct sockaddr *)&clie_addr,sizeof(struct sockaddr_in)) < 0){
        perror("connect");
        exit(0);
    }
    int num;
    while(1){
        printf("请输入消息:");
        scanf("%s",buf);
        if((num = send(sock_fd,(void *)buf,strlen(buf)+1,0)) < 0 ){
            perror("send");
            exit(0);
        }

    }
}
