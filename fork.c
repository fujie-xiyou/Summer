/*************************************************************************
	>    File Name: fork.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月24日 星期一 15时05分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    pid_t pid;
    printf("ppid = %d pid = %d\n",getppid() , getpid());
}

