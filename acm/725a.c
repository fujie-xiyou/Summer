/*************************************************************************
	>    File Name: 725a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月25日 星期二 08时32分32秒
 ************************************************************************/

#include<stdio.h>
int gcd(int a , int b){
    return (b > 0) ? gcd(b,a%b) : a;
}
int main(){
    int n;
    int a,b,i;
    scanf("%d",&n);
    getchar();
    while(n--){
        scanf("%d%d",&a,&b);
        getchar();
        for(i = b+1; 1; i++){
            if(gcd(a,i) == b) break;
        }
        printf("%d\n",i);
    }
}
