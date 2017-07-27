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
char ** anal_cmd();//把由 |  > <组成的复合命令解析成单一命令
void run(char *path,char **argv,int inp,int pri);//运行指定程序


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

char ** anal_cmd(char **command ,int *len , int count , char *sym_p){

	int i = 0,j= 0;
	char *command_p = *command;
	char **my_argv = (char **)malloc(sizeof(char *) * (*len) / count / 2);
	//为最大限度节省内存,这里认为每个被'|'或者'>'隔开
	//的命令的参数个数不超过strlen(command)/count/2

	int single_len = 0;

	//将分割后的整条输入命令依次解析
	while(*command_p != '\0'){

		if(*command_p != ' ' && *command_p != '\0'){
			single_len++;
		}else{
			//将当前空格之前的命令写入 my_argv[i]
			if(*command == command_p) {
				if(*command_p == '\0') break;
				command_p++;
				continue;
			}
			my_argv[j] = (char *)malloc(sizeof(char) * single_len + 1);
			memcpy(my_argv[j],*command,single_len);
			my_argv[j++][single_len] = '\0';
			*command = command_p + 1;
			*len -= single_len;
			single_len = 0;
		}
		if(*(command_p++) == '\0') break;

	}



	return my_argv;

}

void run(char **argv,int inp,int pri){
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
	int i,j,count;
	do{
		print_user();
		sgets(command,1024);
		char sym[50];
		char *sym_p = sym;//存储用户输入命令中的 | > 等符号
		int len = strlen(command);
		int flag_and;//标记结尾是否有&
		i = 0;
		count = 0;
		flag_and = 0;
		if(command[len - 1] == '&'){
			flag_and = 1;
			command[len -1] = '\0';
			len--;
		}

		//将command中的 | > <提取并替换为\0
		//注意 只有完成这项操作  才能在后面调用anal_cmd()函数
		while(command[i]){
			if(command[i] == '|' || command[i] == '>' || command[i] == '<'){
				*(sym_p++) = command[i];
				command[i] = '\0';
				if(command[i+1] == '>'){
					*(sym_p++) = command[i+1];
					command[i] = ' ';
					command[i+1] = '\0';
				}
			}
			*(sym_p++) = '\0';
			count++;
			i++;
		}
		sym_p = sym;
		//anal_cmd();

	}while(1);

}
