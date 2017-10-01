/*************************************************************************
	>    File Name: thread_mutex.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月15日 星期二 08时05分27秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;
int msg;

void *thread(void * arg){
    while(1){
        printf("辅线程上锁前\n");
        pthread_mutex_lock(&mutex);
        printf("辅线程上锁后\n");
        //getchar();
        msg = 10;
        printf("%d\n",msg);
        printf("辅线程解锁前\n");
        pthread_mutex_unlock(&mutex);
        printf("辅线程解锁后\n");
    }
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex ,NULL);
    pthread_t thid;
    pthread_create(&thid ,NULL ,thread ,NULL);
   // getchar();
    while(1){
        printf("主线程上锁前\n");
        pthread_mutex_lock(&mutex);
        printf("主线程上锁后\n");
        msg = 20;

        printf("%d\n",msg);

        printf("主线程解锁前\n");
        pthread_mutex_unlock(&mutex);
        printf("主线程解锁后\n");
    }
}
