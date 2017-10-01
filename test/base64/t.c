/*************************************************************************
	>    File Name: t.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月26日 星期六 01时15分10秒
 ************************************************************************/

#include<stdio.h>
#include"./cencode.h"
#include<string.h>
int main(){
    base64_encodestate state_in;
    base64_init_encodestate(&state_in);
    char* arr = "abcdjjjhgbhbhbhbgbhbhbbhbbhghbbhgbgbhbhbgbg";
    char code_out[2000] ,code_end[5];
    memset(code_out ,0 ,20);
    memset(code_end ,0 ,5);
    base64_encode_block(arr ,strlen(arr) ,code_out ,&state_in);
    base64_encode_blockend(code_end ,&state_in);
    strcat(code_out ,code_end);
    printf("%s\n" ,code_out);
}
