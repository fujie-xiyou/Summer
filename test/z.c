/*************************************************************************
	>    File Name: z.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月24日 星期一 08时00分15秒
 ************************************************************************/

#include<stdio.h>
int count = 0;
void f(void){
    char arr[1024];
    printf("count = %d\n",++count);
    f();
}
int main(){
    f();
}
