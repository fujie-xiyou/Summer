/*************************************************************************
	>    File Name: 724a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月24日 星期一 08时26分32秒
 ************************************************************************/

#include<stdio.h>
int main(){
    char word1[] = "aBblrsu";
    char word2[100000+5];
    int arr[7] , min=100000;;
    scanf("%s",word2);
    for(int i = 0; i < 7; i++){
        for(int j = 0; word2[j] != '\0'; j++){
            if(word1[i] == word2[j]){
                arr[i]++;
            }
        }
    }
    arr[0] /= 2;
    arr[6] /= 2;
    for(int i = 0; i < 7; i++){
        if(arr[i] < min) min = arr[i];
    }
    printf("%d\n",min);
}
