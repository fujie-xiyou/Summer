/*************************************************************************
	>    File Name: creat_thread.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月31日 星期一 15时29分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int * thread(void *arg){
    pthread_t newthid;
    newthid = pthread_self();
    printf("这是一个新线程 , 线程id : %lu\n",newthid);
    return NULL;
}
int main(){
    pthread_t thid;
    printf("主线程id : %lu\n",pthread_self());
    if(pthread_create(&thid,NULL,(void*(*)(void*))thread,NULL) != 0){
        printf("线程创建失败\n");
        exit(0);
    }
    if(pthread_create(&thid,NULL,(void*(*)(void*))thread,NULL) != 0){
        printf("线程创建失败\n");
        exit(0);
    }
    sleep(1);
    exit(0);


}
