/*************************************************************************
	>    File Name: 718c.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月18日 星期二 10时09分01秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int n,m,an,sum,i,j;
    while(scanf("%d %d",&n,&m) != EOF){
        sum=0;
        an=0;
        j=1;
        for(i=0;j<=n;i++,j++){
            an+=2;
            sum+=an;
            if(j%m==0) {
                printf("%d",sum/m);
                if(j==n) printf("\n");
                else printf(" ");
                sum = 0;
                i = 0;
            }
            if(j==n && n%m != 0) printf("%d\n",sum/(n%m));
        }
    }
}
