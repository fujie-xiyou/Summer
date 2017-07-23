/*************************************************************************
	>    File Name: lseek.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月18日 星期二 14时30分40秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<sys/types.h>
//#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
void my_err(const char *err_string , int line){
    fprintf(stderr,"line: %d",line);
    perror(err_string);
    exit(0);
}
int my_read(int fd){
    int len,ret;
    char read_buf[64];
    if(lseek(fd,0,SEEK_END) == -1){
        my_err("lseek",__LINE__);
    }
    if((len=lseek(fd,0,SEEK_CUR)) == -1){
        my_err("lseek",__LINE__);
    }
    if(lseek(fd,0,SEEK_SET) == -1){
        my_err("lseek",__LINE__);
    }
    printf("文件长度: %d\n",len);
    if((ret=read(fd,read_buf,sizeof(read_buf))) == -1){
        my_err("read",__LINE__);
    }

    for(int i=0;i<len;i++){
        printf("%c",read_buf[i]);
    }
    printf("\n");
    return ret;

}
int main(){
    int fd;
    char write_buf[32] = "97520";
    /*if((fd=creat("text.t",S_IREXU)) == -1 ){
        printf("文件创建失败!\n");
    }*/
    if((fd=open("test.t",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU)) == -1){
        my_err("open",__LINE__);
    }else{
        printf("文件创建成功!\n");
    }
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf)){
        my_err("open",__LINE__);
    }
    my_read(fd);

}
