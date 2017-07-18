/*************************************************************************
	>    File Name: 718a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月18日 星期二 08时01分46秒
 ************************************************************************/

#include<stdio.h>
int main(){
    char mail[100+5],*p; 
    int at,spot;
    while(scanf("%s",mail) != EOF){
    //scanf("%s",mail);
        getchar();
        at=0;
        spot=0;
        p=mail;
        while(*(p++) != '\0'){
            
            if(*p != '\0' && *p == '@'){ 
            	at++;
            	if(*(p+1) == '\0') at = 100;
            }
            if(*p != '\0' && *p == '.'){
	            if(*(p-1) == '@' || *(p+1) == '\0' || *(p+1) == '@'){
    	            spot = 0;
    	            break;
    	        }
            	else  {
                    if(at == 1) spot = 1;
        	    }
            }
        }
        if(mail[0] != '.' && mail[0] != '@' && at == 1 && spot >= 1){
            printf("YES\n");
        }
        else printf("NO\n");
        
    }
    return 0;
}
