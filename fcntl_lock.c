/*************************************************************************
	>    File Name: fcntl_lock.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年07月19日 星期三 11时15分49秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

void my_err(const char * err_string ,int line){
    fprintf(stderr,"第 %d 行:",line);
    perror(err_string);
    printf("\n");
    exit(0);
}
/*设置锁函数*/
int lock_set(int fd,struct flock * lock){
    if(fcntl(fd,F_SETLK,lock) == 0){
        //上锁成功
        if(lock->l_type == F_RDLCK)
            printf("设置读锁成功,pid:%d\n",getpid());
        else if(lock->l_type == F_WRLCK)
            printf("设置写锁成功,pid:%d\n",getpid());
        else if(lock->l_type == F_UNLCK)
            printf("释放锁成功,pid:%d\n",getpid());
    }else{
        //my_err("fcntl",__LINE__);
        perror("设置锁失败!\n");
        return -1;
    }
    return 0;
}


//测试锁
int lock_test(int fd,struct flock * lock){
    if(fcntl(fd,F_GETLK,lock) == 0){
        if(lock->l_type  == F_UNLCK){
            printf("此文件可以设置锁\n");
            return 0;
        }else{
            if(lock->l_type == F_RDLCK){
                printf("该文件存在进程 %d 设置的读锁\n",lock->l_pid);
            }else if(lock->l_type == F_WRLCK){
                printf("该文件存在进程 %d 设置的写锁\n",lock->l_pid);
            }
            return -2;
        }
    }
    else{
        perror("获取不兼容锁失败\n");
        return -1;
    }
}
int main(){
    int fd,ret;
    struct flock lock;
    char read_buf[32];

    //打开或创建文件
    if((fd=open("test.t",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU)) == -1){
        my_err("open",__LINE__);
    }
    if(write(fd,"test lock",10) != 10){
        my_err("write",__LINE__);
    }
    //初始化lock结构
    memset(&lock,0,sizeof(struct flock));
    lock.l_start = SEEK_SET;
    lock.l_whence = 0;
    lock.l_len = 0;

    //设置读锁
    lock.l_type = F_RDLCK;
    if(lock_test(fd,&lock) == 0){
        lock.l_type = F_RDLCK;
        lock_set(fd,&lock);
    }

    //读数据
    lseek(fd,0,SEEK_SET);
    if((ret = read(fd,read_buf,10)) < 0){
        my_err("read",__LINE__);
    }
    read_buf[ret] = '\0';
    printf("%s\n",read_buf);
    getchar();

    //设置写锁
    lock.l_type = F_WRLCK;
    if(lock_test(fd,&lock) == 0){
        lock.l_type = F_WRLCK;
        lock_set(fd,&lock);
    }


    //释放锁
    lock.l_type = F_UNLCK;
    lock_set(fd,&lock);
    close(fd);
    return 0;

}
