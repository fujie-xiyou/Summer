/*************************************************************************
	>    File Name: t.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月25日 星期二 21时17分32秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<libgen.h>
int main(){
    char name[100] = "make/ss/";
    printf("%s\n",basename(name));
    printf("%s\n" ,name);
}
