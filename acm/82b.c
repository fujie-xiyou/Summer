/*************************************************************************
	>    File Name: 82b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月02日 星期三 09时10分22秒
 ************************************************************************/

#include<stdio.h>
int r , c;
int vis[26];
int num , max;
int v[4][2] = {-1,0,1,0,0,-1,0,1};
char matrix[20][20];
int check(int x, int y){
    if(x >= 0 && y >= 0 && x < r && y < c && vis[matrix[x][y] - 'A'] == 0){
        return 1;
    }
    return 0;
}

void dfs(int x , int y){
    if(check(x,y)){
//        printf("%c ",matrix[x][y]);
        if(++num > max) max = num;
        vis[matrix[x][y] - 'A'] = 1;
        for(int i = 0; i < 4; i++){
            dfs(x + v[i][0] , y + v[i][1]);
        }
        num--;
        vis[matrix[x][y] - 'A'] = 0;

    } 
  //  printf("(%d)\n",num);
    return;
}

int main(){
    while(scanf("%d%d%*c",&r , &c) != EOF){

        num = 0;
        max = 0;
        for(int i = 0; i < r;i++){
            for(int j = 0; j < c; j++){
                scanf("%c",&matrix[i][j]);
            }
            getchar();
        }
        dfs(0,0);
        printf("%d\n",max);
    }
}
