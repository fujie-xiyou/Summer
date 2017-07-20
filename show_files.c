/*************************************************************************
	>    File Name: show_files.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月20日 星期四 15时42分51秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
void my_err(const char * err_string , int line){
    printf("第 %d 行:",line);
    perror(err_string);
    exit(0);
}
int my_readir(const char *path){
    DIR *dir;
    struct dirent *ptr;
    if((dir = opendir(path)) == NULL){
        my_err("opendir",__LINE__);
    }
    while((ptr=readdir(dir)) != NULL){
        printf("%s  ",ptr->d_name);
    }
    closedir(dir);
    return 0;
}
int main(int argc , char ** argv){
    if(argc < 2){
        printf("show_files <路径>\n");
        exit(1);
    }
    my_readir(argv[1]);
    return 0;
}
