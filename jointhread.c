/*************************************************************************
	>    File Name: jointhread.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月31日 星期一 21时43分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void assisthread(void *arg){
    printf("我是辅助进程.\n");
    sleep(3);
    pthread_exit(0);
}
int main(){
    pthread_t assisthid;
    int status;

    pthread_create(&assisthid , NULL , (void *(*)(void*))assisthread , NULL);
    pthread_join(assisthid , (void*) &status);
    printf("%d\n",status);
} 
