/*************************************************************************
	>    File Name: diffork.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月24日 星期一 19时08分13秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
//有惊喜???


int globVar = 5;
int main(){
    pid_t pid;
    int var = 1, i;
    //pid = fork();
    pid = vfork();
    switch(pid){
        case 0:
            i = 3;
            while(i-- > 0){
                printf("子进程正在运行\n");
                globVar++;
                var++;
                sleep(1);
            }
            printf("子进程的globVar = %d , var = %d\n",globVar,var);
            break;
        case -1:
            perror("进程创建失败\n");
            exit(0);
        default :
            i = 5;
            while(i-- > 0){
                printf("父进程正在运行\n");
                globVar++;
                var++;
                sleep(1);
            }
            printf("父进程的globVar = %d , var = %d\n",globVar,var);
            exit(0);
    }

}
