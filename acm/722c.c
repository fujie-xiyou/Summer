/*************************************************************************
	>    File Name: 722c.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月22日 星期六 08时09分06秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int c,v0,v1,a,l;
    int p;//当前读到
    int day = 0 ;
    scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&l);
    getchar();
    for(int i = 0; i<c; 1){
        if(day == 0) i = i + v0;
        else i = i + v0 - l;
        v0 = (v0+a) < v1 ? v0+a : v1;
        day++;
    }
    printf("%d",day);

}
