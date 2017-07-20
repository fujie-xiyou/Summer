/*************************************************************************
	>    File Name: my_ls.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月20日 星期四 16时15分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE 0 //无参数
#define PARAM_A    1 //-a 显示隐藏文件
#define PARAM_L    2 //-l 显示详细信息
#define PARAM_R    3 //-R 递归显示
#define MAXROWLEN  80 //一行最多显示字符


int g_leave_len = MAXROWLEN; //一行剩余长度,用于输出对齐
int g_maxlen; //存放某目录下最长文件名的长度

void my_err(const char * err_string,int line){
    printf("第 %d 行",line);
    perror(err_string);
    exit(0);
}


/*获取文件属性并打印*/
void display_attribute(struct stat buf,char *name){
    char buf_time[32];
    struct passwd *psd;
    struct group *grp;

    /*获取并打印文件类型*/
    if(S_ISLNK(buf.st_mode))
        printf("l");
    else if(S_ISREG(buf.st_mode))
        printf("-");
    else if(S_ISCHR(buf.st_mode))
        printf("c");
    else if(S_ISBLK(buf.st_mode))
        printf("b");
    else if(S_ISSOCK(buf.st_mode))
        printf("s");
}

/*获取并打印文件所有者的权限*/

