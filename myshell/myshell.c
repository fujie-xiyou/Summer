#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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


/*
 * 重定向记录结构体
 */
typedef struct{
	char red_inp[10][256]; //某条命令的输入重定向列表
	char type_inp[10];   //对于列表中的每一条重定向记录,标记一个类型 1 < 2<<(暂无)
	char red_pri[10][256]; //输出重定向列表
	char type_pri[10]; // 1 >  2>>
}redir_t;

/*
 * 存储一条不含 | 的命令的参数
 * 以及I/O重定向的目标(NULL表示标准I/O)
 */
typedef struct {
	char *(argv[20]);
	redir_t rec;
} cmd_t;

struct passwd* psd;//用户信息
struct utsname uts;//系统信息
int pfds[2];//管道数组




/*
 * 从给定地址开始往后读到一个字符串
 * (忽略前面的\0)
 */
char *get_string(char *cmd_temp , int* i);

void print_user();//打印用户名@主机名:<工作目录> 命令提示符

char *sgets(char *str,int len);//安全gets

char *format_pipe(char *command );
//将command中的 | 提取并替换为\0(即格式化管线)



/*
 * 每次调用本函数将解析出来一条由format_pipe()
 * 函数处理后的command中的一条命令并返回它的首地址
 * 再次调用将读取下一条命令并返回
 * 当command中的命令解析完将返回NULL
 */
char *div_cmd(char **command );


/*
 * 用于将div_cmd分割出来的单条命令进行解析
 * 将I/O重定向目标存储到结构体中
 */
cmd_t * anal_single_cmd(char *single_cmd );


//shell内建命令
_Bool build_in_cmd(cmd_t *cmd);


void run_cmd(char **command ,_Bool is_pipe , char *pipe_p);//运行命令



char *get_string(char *cmd_temp , int* i){
	int temp;
	while(cmd_temp[*i] == '\0'){
		(*i)++;
	}
	temp =*i;
	(*i) += strlen(&cmd_temp[*i]);
	return &cmd_temp[temp];
}


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

char *format_pipe(char *command){//处理输入命令中的管线
	int i = 0;
	char *pipe_t = (char *)malloc(sizeof(char) * 20);//存储用户输入命令中的管线
	memset(pipe_t,0,sizeof(char) * 20);
	char *pipe_p = pipe_t;
	while(command[i]){
		if(command[i] == '|'){
			*(pipe_p++) = command[i];
			command[i] = '\0';
		}
		i++;
	}
	return pipe_t;
}
char *div_cmd(char **command){
	char * single_cmd = NULL;
	//int i = 0;
	char *command_p = *command;
	int single_len = 0;

	//将分割后的整条输入命令依次解析
	while (1) {
		single_len++;
		if (*command_p == '\0') {
			if(command_p == *command){
				//如果一上来就是\0  说明结束了  兄弟
				return NULL;
			}
			single_cmd = (char *) malloc(sizeof(char) * single_len);
			memcpy(single_cmd, *command, single_len);
			*command = command_p + 1;
			break;
		}
		command_p++;
	}
	return single_cmd;
}
cmd_t * anal_single_cmd(char *single_cmd /*, char *pipe_t*/){

	int i = 0 , j = 0 ,l = 0 ,k = 0;
//	int single_len = strlen(single_cmd);
	char cmd_temp[strlen(single_cmd) + 1];
	strcpy(cmd_temp,single_cmd);
	while(cmd_temp[i]){
		if(cmd_temp[i] == ' ' || cmd_temp[i] == '<' || cmd_temp[i] == '>'){
			cmd_temp[i] = '\0';
		}
		i++;
	}
	cmd_t *cmd = (cmd_t *) malloc(sizeof(cmd_t));

	//开始从头读取命令
	i = 0;
	while(single_cmd[i]){
		if(cmd_temp[i] == '\0'){
			if(cmd->argv[0] == NULL && single_cmd[i] == ' ') {
				//如果某条命令开始之前就有由空格导致的\0 则跳过
				i++;
				continue;
			}
			if(single_cmd[i] == '>'){
				if(single_cmd[i+1] == '>'){
					i+=2;
					cmd->rec.type_pri[j] = 2;
				}
				else
				{
					i+=1;
					cmd->rec.type_pri[j] = 1;
				}
				strcpy(cmd->rec.red_pri[j++],get_string(cmd_temp,&i));
			}else if(single_cmd[i] == '<'){
				if(single_cmd[i+1] == '<'){
					i+=2;
					cmd->rec.type_inp[l] = 2;
				}else
				{
					i+=1;
					cmd->rec.type_inp[l] = 1;
				}
				strcpy(cmd->rec.red_inp[l++],get_string(cmd_temp,&i));
			}
			if(single_cmd[i] == '\0') break;
			i++;

		}else{
			cmd->argv[k] = (char *)malloc(strlen(&cmd_temp[i]) + 1);
			strcpy(cmd->argv[k++],get_string(cmd_temp,&i));
		}
	}
	return cmd;

}

_Bool build_in_cmd(cmd_t *cmd){
	if(strcmp(cmd->argv[0],"exit") == 0 ||
			strcmp(cmd->argv[0],"logout") == 0) exit(0);
	if(strcmp(cmd->argv[0],"cd") == 0){
		if(cmd->argv[1] == NULL || strcmp(cmd->argv[1],"~") == 0) cmd->argv[1] = psd->pw_dir;
		if(chdir(cmd->argv[1]) < 0){
			printf("cd: ");
			switch(errno){
				case 2:
					printf("没有那个文件或目录");
					break;
				case 13 :
					printf("权限不足");
					break;
				default:
					printf("执行出错");
			}
			printf(": %s\n",cmd->argv[1]);
		}
		return true;
	}
	return false;
}

void run_cmd(char **command, _Bool is_pipe, char *pipe_p) {
	int pid;
	int stat_val;
	int i = 0, j = 0;
	int fd, fp, fdt, fpt;
	char *single_cmd = NULL;
	cmd_t *cmd = NULL;
	single_cmd = div_cmd(command);
	cmd = anal_single_cmd(single_cmd);
	pipe(pfds);
	if (build_in_cmd(cmd))
		return;
	do {
		fdt = dup(0);
		fpt = dup(1); //先将标准输入输出文件流复制到fdt和fpt

		//处理输入重定向  包括管道右端
		if (is_pipe) {
			rename("/tmp/pipe_w" , "/tmp/pipe_r");
			fd = open("/tmp/pipe_r", O_RDONLY);
			dup2(fd, 0);
		} else if (cmd->rec.type_inp[i] != 0) {
			fd = open(cmd->rec.red_inp[i], O_RDONLY);
			dup2(fd, 0);
			i++;
		}
		//处理输出重定向  包括管道左端
		if (*pipe_p != '\0') {
			fp = open("/tmp/pipe_w", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
			dup2(fp, 1);
		} else if (cmd->rec.type_pri[j] != 0) {
			fp = open(cmd->rec.red_pri[j], O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR);
			dup2(fp, 1);
			j++;
		}
		pid = fork();
		if (pid == -1) {
			printf("进程创建失败!\n errno = %d", errno);
			exit(0);
		} else if (pid == 0) {
			if(execvp(cmd->argv[0], cmd->argv) == -1){
				printf("myshell: ");
				switch(errno){
					case 2:
						printf("找不到命令");
						break;
					case 13 :
						printf("权限不足");
						break;
					default:
						printf("执行出错");
				}
				printf(": %s\n",cmd->argv[0]);
			}
			exit(0);
		}
		close(fd);
		close(fp);
		remove("/tmp/pipe_r");
		dup2(fdt, 0);
		dup2(fpt, 1); //恢复标准输入输出
		wait(&stat_val);

	} while (cmd->rec.type_inp[i] != 0 || cmd->rec.type_pri[j] != 0);

	if (*pipe_p != '\0')
		run_cmd(command, true, pipe_p + 1);

}



int main(){
	char *command = malloc(sizeof(char) * 1024);//存储用户输入的命令
	do{
		print_user();
		sgets(command,1024);
		int len = strlen(command);
		if(len == 0) continue;
		int flag_and;//标记结尾是否有&
		flag_and = 0;
		char *pipe_p;
		pipe_p = format_pipe(command);
		//处理后台运行符 待添加
		if(flag_and == 0) {}
		if(command[len - 1] == '&'){
			flag_and = 1;
			command[len -1] = '\0';
			len--;
		}
		run_cmd(&command , false ,pipe_p);

	}while(1);

}
