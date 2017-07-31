/*************************************************************************
	>    File Name: 731a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月31日 星期一 10时17分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
int move[8][2]={2,1,1,2,-2,-1,-1,-2,1,-2,-2,1,-1,2,2,-1};
int vis[8][8];
_Bool check(int x,int y){
    if(x > 0 && y > 0  && vis == 0 ){
        return true;
    }
    return false;
}
void dfs(int x,int y){

}
