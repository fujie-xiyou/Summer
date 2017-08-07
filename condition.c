/*************************************************************************
	>    File Name: condition.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月01日 星期二 10时50分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread1(void *arg){
    pthread_cleanup_push((void (*)(void*))pthread_mutex_unlock , &mutex);
    while(1){
        printf("线程1正在运行\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("线程1使用条件变量\n");
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
    pthread_cleanup_pop(0);
}

void *thread2(void *arg){
    while(1){
        printf("线程2正在运行\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond , &mutex);
        printf("线程2使用条件变量\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main(){
    pthread_t tid1 , tid2;
    printf("条件变量示例\n");
    pthread_mutex_init(&mutex , NULL);//初始化互斥锁
    pthread_cond_init(&cond , NULL);//初始化条件变量
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);
    do{
        pthread_cond_signal(&cond);
    }while(1);
    sleep(50);
    pthread_exit(0);
}
