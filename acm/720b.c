/*************************************************************************
	>    File Name: 720b.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月20日 星期四 09时19分23秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int n,i,j,k,len;
    char str[1000+5],newstr[1000+5];
    scanf("%d",&n);
    getchar();
    for(int i = 0; i<n; i++){
        gets(str);
        j=0;
        len=0;
        while(str[j]!='\0'){
            if(str[j] == ' '){
                newstr[j]=str[j];
                j++;
                continue;
            }
            len++;
            if(str[j+1] == ' ' || str[j+1] == '\0'){
                k=len;
                while(k--){
                    newstr[j-k]=str[j-len+k+1];
                }
                newstr[j+1]=str[j+1];
                if(str[j+1] == ' ') {
                    j++;
                    len=0;
                }
            }
            j++;
//            len=0;
        }
        newstr[j]='\0';
        printf("%s\n",newstr);
        //if(i != n-1) printf("\n");
    }
}
