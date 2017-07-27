/*************************************************************************
	>    File Name: 725b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月25日 星期二 08时47分29秒
 ************************************************************************/
//大整数相加
#include<stdio.h>
#include<string.h>
int main(){
    int n,i,j,flag;
    char a[1005],b[1005],c[1005];
    char *p,*q;
    char temp = '0';
    scanf("%d",&n);
    getchar();
    j = n;
    while(j--){
        scanf("%s %s",a,b);
        getchar();
        p = &a[strlen(a) - 1];
        q = &b[strlen(b) - 1];
        i = 0;
        flag = 0;
        memset(c,0,sizeof(c[0]) * 1005);
        while(1){
            c[i++] = *p + *q - 48;
            if(p == &a[0]) p = &temp , flag |= 1;
            else if(p != &temp) p--;
            if(q == &b[0]) q = &temp , flag |= 2;
            else if(q != &temp) q--;
            if(flag == 3) break;
        }
        flag = strlen(c);//往后借用flag存储结果长度
        for(i = 0; i < flag; i++){
            if(c[i] > '9'){
                c[i] = c[i] -10;
                c[i+1]++;
                if(i == flag - 1) {
                    c[i+1] += 48;
                    c[i+2] = '\0';
                }
            }
        }


        printf("Case %d:\n%s + %s = ",n-j,a,b);
        i = strlen(c);
        while(i--){
            printf("%c",c[i]);
        }
        if(j != 0) printf("\n");
        printf("\n");
    }
}
