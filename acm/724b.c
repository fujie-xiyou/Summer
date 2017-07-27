/*************************************************************************
	>    File Name: 724b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月24日 星期一 09时46分52秒
 ************************************************************************/
//未完成!!!!
#include<stdio.h>
long gcd(long a,long b){
    long r = a % b;
    if(r == 0) return b;
    else return gcd(b,r);
}
int main(){
    int n;
    long rr , b , r[2],d[2];
    scanf("%d",&n);
    getchar();
    while(n--){
        scanf("%ld/%ld %ld/%ld",&r[0],&d[0],&r[1],&d[1]);
        b = d[0] * d[1] /gcd(d[0],d[1]);
        rr = r[0] * b / d[0] + r[1] * b / d[1];
        getchar();
        printf("%ld\n",b);

    }
}
