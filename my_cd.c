/*************************************************************************
	>    File Name: my_cd.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月20日 星期四 14时51分08秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//#include<Linux/limits.h>
void my_err(const char * err_string,int line){
    fprintf(stderr,"第 %d 行:",line);
    perror(err_string);
    exit(0);
}
int main(int argc,char ** argv){
    char buf[512 + 1];
    if(argc < 2){
        printf("my_cd <目录>\n");
        exit(1);
    }
    if(chdir(argv[1]) < 0){
        my_err("chdir",__LINE__);
    }
    if(getcwd(buf,512) < 0){
        my_err("getcwd",__LINE__);
    }
    printf("%s\n",buf);
    return 0;
}
