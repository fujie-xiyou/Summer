/*************************************************************************
 >    File Name: my_ls.c
 >       Author: fujie
 >         Mail: fujie.me@qq.com
 > Created Time: 2017年07月20日 星期四 16时15分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include <libgen.h>

#define PARAM_NONE 0 //无参数
#define PARAM_A    1 //-a 显示隐藏文件
#define PARAM_L    2 //-l 显示详细信息
#define PARAM_R    4 //-R 递归显示
#define MAXROWLEN  80 //一行最多显示字符
int nnn = 0;
int g_leave_len = MAXROWLEN; //一行剩余长度,用于输出对齐
int g_maxlen; //存放某目录下最长文件名的长度
//char path_all[512]; //用于在-R时存储全路径:q


void my_err(const char * err_string, int line) {
	fprintf(stderr, "第 %d 行: ", line);
	perror(err_string);
	exit(0);
}

/*用内建的快排排序文件名*/
int cmp(const void *a, const void *b) {
	return strcasecmp((char *) a, (char *) b);
}

void display(int flag, char *pathname);

void display_singal(char *name);

void display_dir(int flag_param, char *path);

/*获取文件属性并打印*/
void display_attribute(struct stat buf, char *name) {
	char buf_time[32];
	struct passwd *psd;
	struct group *grp;

	/*获取并打印文件类型*/
	if (S_ISLNK(buf.st_mode))
		printf("l");
	else if (S_ISREG(buf.st_mode))
		printf("-");
	else if (S_ISDIR(buf.st_mode))
		printf("d");
	else if (S_ISCHR(buf.st_mode))
		printf("c");
	else if (S_ISBLK(buf.st_mode))
		printf("b");
	else if (S_ISSOCK(buf.st_mode))
		printf("s");

	/*获取并打印文件所有者的权限*/
	if (buf.st_mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXUSR)
		printf("x");
	else
		printf("-");

	/*获取用户组权限*/
	if (buf.st_mode & S_IRGRP)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXGRP)
		printf("x");
	else
		printf("-");

	/*获取其他权限*/
	if (buf.st_mode & S_IROTH)
		printf("r");
	else
		printf("-");
	if (buf.st_mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	if (buf.st_mode & S_IXOTH)
		printf("x");
	else
		printf("-");

	printf("    ");

	/*根据uid与gid获取所有者的用户名与组名*/
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%4d ", buf.st_nlink);
	printf("%-8s", psd->pw_name);
	printf("%-8s", grp->gr_name);

	printf("%6d", buf.st_size); //打印文件大小
	strcpy(buf_time, ctime(&buf.st_mtime)); //获取文件时间
	buf_time[strlen(buf_time) - 1] = '\0';
	printf(" %s", buf_time); //打印时间
}

/*递归打印文件夹*/
void display_r(int flag_param, char *path) {
	printf("递归了 %d 次.\n",++nnn);
	printf("path = %s\n",path);
	//char temp[512];
	DIR *dir;
	struct dirent *ptr;
	int count = 0;
	//int dircount = 0;
	int i = 0 , j = 0;

	char temp[PATH_MAX + 1];
	char **filename;
	struct stat buf;
	g_maxlen = 0;
	//获取给定文件夹下的文件数目和最长文件名
	dir = opendir(path);
	if (dir == NULL) {
		my_err("opendir", __LINE__);
	}
	while ((ptr = readdir(dir)) != NULL) {
		if (g_maxlen < strlen(ptr->d_name)) {
			g_maxlen = strlen(ptr->d_name);
		}
		count++;
	}

	closedir(dir);

	if (count > 256) {
		my_err("该文件夹下的文件数目过多!", __LINE__);
	}
	printf("\n");

	filename = (char **) malloc(sizeof(void *) * count);
	if(filename == NULL) my_err("内存申请失败!",__LINE__);


	for (i = 0; i < count; i++) {
		filename[i] = (char *) malloc(strlen(path) + g_maxlen + 2);
		if(filename[i] == NULL) my_err("内存申请失败!",__LINE__);
	}

	int len = strlen(path);
	//获取目录下的所有文件名
	dir = opendir(path);
	for (i = 0; i < count; i++) {
		ptr = readdir(dir);
		if (ptr == NULL) {
			my_err("readdir", __LINE__);
		}

		strcpy(filename[i], path);
		strcat(filename[i], ptr->d_name);
		filename[i][len + strlen(ptr->d_name)] = '\0';

	}

	//用内建的快排排序文件名
	//qsort(filename, count, strlen(path) + g_maxlen + 2 , cmp);

	//怕了 上冒泡

    char *t;
    for(i=0;i<count - 1;i++)
    {
        for(j=0;j<count - 1;j++)
        {
            if(strcmp(filename[j],filename[j+1])>0)
            {
                t=filename[j];
                filename[j]=filename[j+1];
                filename[j+1]=t;
            }
        }
    }


	for (i = 0; i < count; i++) {
		if(basename(filename[i])[0] == '.') continue;
		if (stat(filename[i], &buf) == -1) {
			//printf("%s\n",filename[i]);
			my_err("stat", __LINE__);
		}

		if (S_ISDIR(buf.st_mode)) {
			//argv[i]是目录
			//如果目录最后一个字符不是'/' ,就加上'/'
			if (filename[i][strlen(filename[i]) - 1] != '/') {
				filename[i][strlen(filename[i]) + 1] = '\0';
				filename[i][strlen(filename[i])] = '/';
			} else {

				filename[i][strlen(filename[i])] = '\0';
			}
			printf("count = %d , g_maxlen = %d\nfilename[%d] = %s\n路径长度: %d\n",
					count,g_maxlen,i,filename[i],strlen(filename[i]));
			//printf("++%s++\n",filename[i]);

			display_dir(flag_param, filename[i]);

		}
	}
	for(i = 0; i < count; i++){
		free(filename[i]);
	}
	free(filename);

	closedir(dir);
	//如果命令行中没有-l选项符

//    if((flag_param & PARAM_L) == 0)
//        printf("\n");

}

/*不使用-l选项时,打印单个文件名并上下对齐*/
void display_singal(char *name) {
	int i, len;

	//如果本行不足以打印一个文件名 则换行
	if (g_leave_len < g_maxlen) {
		printf("\n");
		g_leave_len = MAXROWLEN;
	}
	len = strlen(name);
	len = g_maxlen - len;
	printf("%-s", name);

	for (i = 0; i < len; i++) {
		printf(" ");
	}
	printf("  ");
	g_leave_len -= (g_maxlen + 2);
}

/*
 * 根据命令行参数和完整路径显示目标文件
 * 参数flag: 命令行参数
 * 参数pathname: 包含了文件名的路径名
 */
void display(int flag, char *pathname) {
	int i, j;
	struct stat buf;
	char name[NAME_MAX + 1];

	/*从路径中解析出文件名
	for (i = 0, j = 0; i < strlen(pathname); i++) {
		if (pathname[i] == '/') {
			j = 0;
			continue;
		}
		name[j++] = pathname[i];
	}
	name[j] = '\0';
*/
	strcpy(name,basename(pathname));


	/*使用lstat而不是stat方便处理链接文件*/
	if (lstat(pathname, &buf) == -1) {
		printf("\n+++ %s ++++\n",pathname);
		my_err("lstat", __LINE__);
	}
	switch (flag) {
	case PARAM_NONE:
		if (name[0] != '.') {
			display_singal(name);
		}
		break;
	case PARAM_A:
		display_singal(name);
		break;
	case PARAM_L:
		if (name[0] != '.') {
			display_attribute(buf, name);
			printf("  %-s\n", name);
		}
		break;

	case PARAM_R:
		if (name[0] != '.') {
			display_singal(name);
			//display_r(flag,name);
		}
		break;
	case PARAM_A + PARAM_L:
		display_attribute(buf, name);
		printf("  %-s\n", name);
		break;
	default:
		break;
	}
}
void display_dir(int flag_param, char *path) {
	printf("d_d path\n");
	DIR *dir;
	struct dirent *ptr;
	int count = 0;
	char filename[256][PATH_MAX + 1], temp[PATH_MAX + 1];

	//获取给定文件夹下的文件数目和最长文件名
	dir = opendir(path);
	if (dir == NULL) {
		//printf("%s",path);
		my_err("opendir", __LINE__);
	}
	while ((ptr = readdir(dir)) != NULL) {
		if (g_maxlen < strlen(ptr->d_name)) {
			g_maxlen = strlen(ptr->d_name);
		}
		count++;
	}
	closedir(dir);

	if (count > 256) {
		my_err("该文件夹下的文件数目过多!", __LINE__);
	}

	int i, j, len = strlen(path);
	//获取目录下的所有文件名
	dir = opendir(path);
	for (i = 0; i < count; i++) {
		ptr = readdir(dir);
		if (ptr == NULL) {
			my_err("readdir", __LINE__);
		}
		strcpy(filename[i], path);
		strcat(filename[i], ptr->d_name);
		filename[i][len + strlen(ptr->d_name)] = '\0';

	}

	//用内建的快排排序文件名
	qsort(filename, count, sizeof(filename[0]), cmp);

	if(flag_param & PARAM_R){
		printf("%s/:\n", basename(path));
		strcat(path,"/");
	}
	for (i = 0; i < count; i++)
		display(flag_param, filename[i]);
	printf("\n");
	if (flag_param & PARAM_R)
		//如果包含R参数  从当前目录开始递归
		display_r(flag_param, path);
	closedir(dir);
	//如果命令行中没有-l选项符
	if ((flag_param & (PARAM_L + PARAM_R)) == 0  )
		printf("\n");

}

int main(int argc, char ** argv) {
	char path[PATH_MAX + 1];
	char param[32]; //保存命令行参数
	int flag_param = PARAM_NONE; //参数种类(-l -a -R)
	struct stat buf;

	/*命令行参数解析
	 * 使用getopt()函数
	 */
	int ch; //临时保存单个参数
	int i, count = 0; //参数中目录/文件总数
	opterr = 0; //使getopt不向stderr输出错误信息
	while ((ch = getopt(argc, argv, "laR")) != -1) {
		switch (ch) {
		case 'l':
			flag_param |= PARAM_L;
			break;
		case 'a':
			flag_param |= PARAM_A;
			break;
		case 'R':
			flag_param |= PARAM_R;
			break;
		default:
			fprintf(stderr, "不支持参数 %c\n", ch);
			exit(1);
		}
	}
	for (i = 1; i < argc; i++)
		if (argv[i][0] != '-')
			count++;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			strcpy(path, argv[i]);
			//如果目标文件名或目录不存在,退出
			if (stat(path, &buf) == -1) {
				my_err("stat", __LINE__);
			}
			if (S_ISDIR(buf.st_mode)) {
				//argv[i]是目录
				//如果目录最后一个字符不是'/' ,就加上'/'
				if (path[strlen(argv[i]) - 1] != '/') {
					path[strlen(argv[i])] = '/';
					path[strlen(argv[i]) + 1] = '\0';
				} else {
					//strcpy难道不会自己添加\0???
					path[strlen(path)] = '\0';
				}

				display_dir(flag_param, path);

			} else {
				//argv[i]是文件
				display(flag_param, path);
				if (count > 1)
					printf("\n");
			}
			if (count > 1)
				printf("\n");

		}

	}
	if (count == 0) {
		strcpy(path, "./");
		path[2] = '\0';
		//if(flag_param & PARAM_R)
		display_dir(flag_param, path);
	}
	return 0;

}
