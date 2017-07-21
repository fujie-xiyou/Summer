/*************************************************************************
	>    File Name: 721a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月21日 星期五 08时05分08秒
 ************************************************************************/

#include<stdio.h>
int main(){
    double num,sum;
    int i = 12;
    while(i--){
        scanf("%lf",&num);
        sum += num;
    }
    printf("$%0.2lf",sum/12);
}
