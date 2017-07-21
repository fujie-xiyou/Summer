/*************************************************************************
	>    File Name: 721b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月21日 星期五 08时12分07秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(){
    int n,len,flag;
    char arr[100];
    scanf("%d",&n);
    getchar();
    while(n--){
        flag = 1;
        gets(arr);
        len = strlen(arr);
        for(int i = 0;i<len/2; i++){
            if(arr[i] != arr[len-i-1]){
                flag = 0;
                break;
            }
        }
        if(flag) printf("yes");
        else printf("no");
        if(n != 0) printf("\n");
    }
}
