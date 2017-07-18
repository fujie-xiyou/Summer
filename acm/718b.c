/*************************************************************************
	>    File Name: 718b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月18日 星期二 09时53分29秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int n,i,j;
    float a[100+5],temp,sum;
    while(scanf("%d",&n) != EOF){
        sum = 0;
        for(i = 0; i<n; i++)
            scanf("%f",&a[i]);
        for(i=0;i<n-1;i++){
            for(j=i+1;j<n;j++){
                if(a[i]>a[j]){
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }
        for(i=1;i<n-1;i++) sum+=a[i];
        printf("%.2f\n",sum/(n-2));

    }
}
