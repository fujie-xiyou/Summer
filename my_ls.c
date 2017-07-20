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
#include<limits.h>
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


    /*获取并打印文件所有者的权限*/
    if(buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    /*获取用户组权限*/
    if(buf.st_mode & S_IRGRP)
        printf("r");
    else 
        printf("-");
    if(buf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXGRP)
        printf("x");
    else 
        printf("-");


    /*获取其他权限*/
    if(buf.st_mode & S_IROTH)
        printf("r");
    else 
        printf("-");
    if(buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else 
        printf("-");

    printf("    ");


    /*根据uid与gid获取所有者的用户名与组名*/
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4d ",buf.st_nlink);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);

    printf("%6d",buf.st_size);//打印文件大小
    strcpy(buf_time,ctime(&buf.st_mtime));//获取文件时间
    buf_time[strlen(buf_time)-1] = '\0';
    printf(" %s",buf_time);//打印时间
    }



