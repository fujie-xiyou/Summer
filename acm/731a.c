/*************************************************************************
	>    File Name: 731a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月31日 星期一 10时17分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
int move[8][2] = {-2,-1,-2,1,-1,2,-1,-2,1,-2,1,2,2,-1,2,1};
int vis[8][8];
int p,q,step;
_Bool check(int x,int y){
    if(x >= 0 && y >= 0  && x < p && y < q && vis[x][y] == 0 ){
        return true;
    }
    return false;
}
void dfs(int x,int y){
    if(check(x,y)) {
        vis[x][y] = 1;
        if(++step == p * q) {
            printf("%c%d",x+65,y+1);
            //printf("yes\n");
            return;
        }
        for(int i = 0 ; i < 8 ; i++){
            dfs(x + move[i][0] , y + move[i][1]);
        }
        vis[x][y] = 0;
        step--;
    }
    
    return;
}
int main(){
    int n;
    scanf("%d%*c",&n);
    for(int i = 0; i < n ; i++){
        step = 0;
        scanf("%d%d%*c",&p,&q);
        for(int j = 0; j < p ; j++){
            for(int k = 0; k < q; k++){
                memset(&vis , 0 , sizeof(vis));
                dfs(k,j);
            }
        }
        printf("\n");
    }
}
