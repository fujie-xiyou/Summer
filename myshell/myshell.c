#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/utsname.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<pwd.h>
#include<errno.h>

struct passwd* psd;//用户信息
struct utsname uts;//系统信息



void print_user();//打印用户名@主机名:<工作目录> 命令提示符
char *sgets(char *str,int len);//安全gets
char *format_pipe_cmd(char **command , int *count);
//将command中的 | 提取并替换为\0(即格式化管线)

char ** anal_cmd(char **command ,int *len , int count);
//把由 |  > <组成的复合命令解析成单一命令

void run_cmd(char **argv,int inp,int pri);//运行命令


void print_user(){
	char *work_path = (char *)malloc(sizeof(char) * 512);
	char *temp =NULL;
	psd = getpwuid(getuid());
	if(uname(&uts) < 0){
		printf("myshell: 无法获取系统信息,errno = %d\n",errno);
		exit(0);
	}
	if(getcwd(work_path,512) == NULL){
		printf("myshell: 无法获取工作目录,errno = %d\n",errno);
		exit(0);
	}
	if((temp = strstr(work_path,psd->pw_dir)) && temp == work_path){
		work_path = work_path + (strlen(psd->pw_dir) - 1);
		*work_path = '~';
	}
	printf("\e[36m%s@%s\e[37m:\e[34m%s\e[0m",psd->pw_name,uts.nodename,work_path);
	if(psd->pw_uid == 0) printf("# ");
	else printf("$ ");
}

char *sgets(char *str,int len){
	char * rtn = fgets(str,len,stdin);
	if(str[strlen(str)-1]=='\n'){
		str[strlen(str)-1]='\0';
	}
	return rtn;
}

char *format_pipe_cmd(char **command , int *count){//处理输入命令中的管线
	int i = 0;
	char *pipe = (char *)malloc(sizeof(char) * 20);//存储用户输入命令中的 |
	char *pipe_p = pipe;
	while((*command)[i]){
		if((*command)[i] == '|'){
			*(pipe_p++) = (*command)[i];
			(*command)[i] = '\0';
			(*count)++;
		}
		i++;
	}
	return pipe;
}

char ** anal_cmd(char **command ,int *len , int count ){
	if(*len <= 0) return NULL;
	int i = 0;
	char *command_p = *command;
	char **my_argv = (char **)malloc(sizeof(char *) * (*len) / count / 2);
	memset(my_argv , 0 , sizeof(char *) * (*len) / count / 2);
	//为最大限度节省内存,这里认为每个被'|'或者'>'隔开
	//的命令的参数个数不超过strlen(command)/count/2

	int single_len = 0;

	//将分割后的整条输入命令依次解析
	while(1){

		if(*command_p != ' ' && *command_p != '\0'){
			single_len++;
		}else{
			//将当前空格或\0之前的命令写入 my_argv[i]


			if(*command == command_p) {
				//如果一上来就是空格或\0 则跳过
				*command = ++command_p;
				(*len)--;
				continue;
			}
			my_argv[i] = (char *)malloc(sizeof(char) * single_len + 1);
			memcpy(my_argv[i],*command,single_len);
			my_argv[i++][single_len] = '\0';
			*command = command_p + 1;
			*len -= (single_len + 1);
			single_len = 0;
		}
		if(*(command_p++) == '\0') break;


	}
	my_argv[i] = NULL;
	return my_argv;

}

void run_cmd(char **argv,int inp,int pri){
	int pid;
	int stat_val;
	pid = fork();
	if(pid == -1) {
		printf("进程创建失败!\n errno = %d",errno);
		exit(0);
	}
	else if(pid == 0){
		execvp(argv[0],argv);
		exit(0);
	}
	wait(&stat_val);

}



int main(){
	char *command = malloc(sizeof(char) * 1024);//存储用户输入的命令
	int i,count;
	do{
		print_user();
		sgets(command,1024);
		char *pipe_p = NULL;//存储用户输入命令中的 | > 等符号
		char ** my_argv = NULL;
		int len = strlen(command);
		if(len == 0) continue;
		int flag_and;//标记结尾是否有&
		i = 0;
		count = 1;
		flag_and = 0;

		//处理后台运行符 待添加
		if(flag_and == 0) {}
		if(command[len - 1] == '&'){
			flag_and = 1;
			command[len -1] = '\0';
			len--;
		}
		pipe_p = format_pipe_cmd(&command,&count);
		printf("%d\n",count);
		for(i = 1; i < count; i++){
			printf("%s\n",pipe_p);
			pipe_p +=strlen(pipe_p) + 1;
		}
		my_argv = anal_cmd(&command , &len ,count);

		//run_cmd()


	}while(1);

}
