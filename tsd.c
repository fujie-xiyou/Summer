/*************************************************************************
	>    File Name: tsd.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月01日 星期二 08时16分33秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

pthread_key_t key;


void *thread2(void *arg){
    int tsd = 5;
    printf("线程2 id =  %lu 正在运行\n",pthread_self());
    pthread_setspecific(key , (const void *)&tsd);
    printf("线程2 id = %lu 的 key = %d\n",pthread_self(),*(int *)pthread_getspecific(key));

}

void *thread1(void *arg){
    int tsd = 0;
    pthread_t thid2;
    printf("线程1 id =  %lu 正在运行\n",pthread_self());
    pthread_setspecific(key, (const void *)&tsd);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(3);
    printf("线程1 id = %lu 的key = %d\n",pthread_self(),*(int *)pthread_getspecific(key));
}
int main(){
    pthread_t thid1;
    printf("主线程开始运行\n");
    pthread_key_create(&key , NULL);
    pthread_create(&thid1 , NULL , thread1 , NULL);
    sleep(5);
    pthread_key_delete(key);
}
