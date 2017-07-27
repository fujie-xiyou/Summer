/*************************************************************************
	>    File Name: 726.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月26日 星期三 08时16分49秒
 ************************************************************************/
//dfs 棋盘问题
#include<stdio.h>
char board[9][9];
int flagi ; 
int dfs(int i , int j){
    if(board[i][j] == 0){

    }
}
int main(){
    int n;
    scanf("%d%*c",&n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            board[i][j] = getchar();
            if(board[i][j] == '#') board[i][j] = 1;
            else board[i][j] = 0;;
        }
        getchar();
    }
}
