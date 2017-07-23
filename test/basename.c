/*************************************************************************
	>    File Name: basename.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月22日 星期六 22时35分53秒
 ************************************************************************/

#include<stdio.h>
#include<libgen.h>
int main(){
    char str[50] = "./test/";
    printf("--%s\n",basename(str));
    printf("__%s\n",str);
    //printf("==%s\n",dirname(str));
    if( 1 || 2 || 3 ) printf("恩\n");
}
