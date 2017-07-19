/*************************************************************************
	>    File Name: 719a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月19日 星期三 08时04分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int num[5],n,sum;
    while(1){
        scanf("%d",&n);
        if(n==0) break;
        memset(num,0,sizeof(num[0])*5);
        num[3]=1;
        while(n-- -1){
            num[3]+=num[2];
            num[2]=num[1];
            num[1]=num[0];
            num[0]=num[3];
        }
        sum=0;
        for(int i=0;i<4;i++){
            sum+=num[i];
        }
        printf("%d\n",sum);
    }
}
