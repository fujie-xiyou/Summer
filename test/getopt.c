/*************************************************************************
	>    File Name: getopt.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月21日 星期五 14时50分41秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc , char ** argv){
    int oc;
    char ec;
    while((oc = getopt(argc,argv,"laR")) != -1){
//        printf("选项: %d\n",optind);
        //printf("%c ",oc);
        switch(oc){
            case 'l':
                printf("有l选项\n");
                break;
            case 'a' :
                printf("有a选项\n");
                break;
            case 'R' :
                printf("有R选项\n");
                break;
            case '?' :
                printf("这是啥?\n");
                break;
        }
    }
}
