/*************************************************************************
	>    File Name: 721c.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月21日 星期五 08时30分04秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int n,num,sum;
    scanf("%d",&n);
    getchar();
    while(n--){
        sum = 3;
        scanf("%d",&num);
        getchar();
        while(num--){
            sum=(sum-1)*2;
        }
        printf("%d\n",sum);
    }
}
