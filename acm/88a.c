/*************************************************************************
	>    File Name: 88a.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月08日 星期二 08时22分28秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
int main(){
    MYSQL *mysql = mysql_init(NULL);//创建一个MYSQL句柄并初始化
    MYSQL_RES *res;
    MYSQL_ROW row;
    char word[100] , SQL[256] , ch;
    int i = 0 ;
    memset(word,0,sizeof(word));
    if(mysql_real_connect(mysql,"120.78.96.152","root","AAA000aaa","acm",0,NULL,0) == 0){
        printf("连接失败\n");
    }
    while((ch = getchar()) != EOF){
        if(ch >= 'a' && ch <= 'z'){
            word[i++] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            word[i++] = ch + 32;
        }
        else{
            if(strlen(word) > 0){
                sprintf(SQL,"INSERT INTO word VALUES('%s')",word);
                if(mysql_real_query(mysql , SQL , strlen(SQL))){
                    printf("插入失败:%s\n",mysql_error(mysql));
                }
                memset(word,0,sizeof(word));
                i = 0;
            }
        }
    }
    memset(SQL,0,sizeof(SQL));
    strcpy(SQL,"SELECT DISTINCT word FROM word ORDER BY word");
    if(mysql_real_query(mysql , SQL , strlen(SQL))){
        printf("查询失败:%s\n",mysql_error(mysql));
    }
    res = mysql_store_result(mysql);
    while(row = mysql_fetch_row(res)){
        printf("%s\n",row[0]);
    }
    mysql_free_result(res);


    //清空数据表
    strcpy(SQL,"DELETE FROM word");
    mysql_real_query(mysql,SQL,strlen(SQL));


    //关闭连接
    mysql_close(mysql);

}
