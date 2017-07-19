/*************************************************************************
	>    File Name: 719b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月19日 星期三 08时31分11秒
 ************************************************************************/

#include<stdio.h>
#define N 100
int main(){
    int n,num[N],flag,s;
    while(scanf("%d",&n)!=EOF){
        for(int i= 0 ; i<n ; i++ )
            scanf("%d",&num[i]);
        s=num[0];
        while(1){
            flag = 1;
            for(int i=0 ; i<n ; i++){
                if(s%num[i] != 0) flag = 0;
            }
            if(flag) break;
            s++;
        }
        printf("%d\n",s);
    }
}
