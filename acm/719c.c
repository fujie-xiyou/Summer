/*************************************************************************re you ready?re you ready?
	>    File Name: 719c.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月19日 星期三 09时08分11秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int n,i,j,num;
    char arr[1000];
    scanf("%d",&n);
    getchar();
    for(i=0 ; i<n ; i++){
        num=0;
        fgets(arr,1000,stdin);
        //gets(arr);
//        if(arr[strlen(arr)-1]=='\n') arr[strlen(arr)-1] = '\0';
        j=0;
        while(arr[j]!='\0')
            if(arr[j++]<0) num++;
        printf("%d\n",num/3);
    }
}
