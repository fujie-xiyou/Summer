/*************************************************************************
	>    File Name: my_chmod.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月17日 星期一 17时13分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char **argv){
    int mode;
    int mode_u , mode_g , mode_o;
    //  拥有者   组       其他
    char *path;
    if(argc < 3){
        //用法提示
        printf("%s <权限> <文件名>\n",argv[0]);
        exit(0);
    }
    mode=atoi(argv[1]);
    if(mode > 777 || mode < 0){
        printf("权限不合法!\n");
        exit(0);
    }
    mode_u = mode / 100;
    mode_g = (mode % 100) / 10;
    mode_o = mode % 10;
    //上述操作讲拿到用十进制表示的权限数  原因是atoi()函数转换的结果是10进制

    mode= mode_u * 8 * 8 + mode_g * 8 + mode_o; 
    //将十进制的权限数转换成八进制
    path = argv[2];
    if(chmod(path,mode) == -1){
        perror("修改权限失败!");
        exit(1);
    }
    return 0;
}
