 #include "myshell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

void initpath(){

DIR *dir = opendir(getenv("HOME"));
	if(!dir)
		errorExit("couldn't open home directory\n");
	struct dirent * entry;

	while(entry = readdir(dir))
	{
		if(entry->d_type == DT_REG && strcmp("paths.txt", entry->d_name) == 0)
		{
		
			return;
		}
	}
	char filepath[MAX_CWDPATH_SIZE];
	strcpy(filepath,getenv("HOME"));
	strcat(filepath,"/path.txt");
	
	FILE *fptr = fopen(filepath, "w");

	fprintf(fptr, "%s ", "./");
	fprintf(fptr, "%s ", "/bin/");
	fprintf(fptr, "%s ", "/usr/bin/");
	fprintf(fptr, "%s ", "/usr/sbin/");

	fclose(fptr);
}
	
//finding the executables with given path
int findExecutable(char *name,char *buf){
	char paths[MAX_CWDPATH_SIZE];
	strcpy(paths,getenv("HOME"));
	strcat(paths,"/path.txt");
	FILE *ptr=fopen(paths,"r");
	if(!ptr) errorExit("path.txt not found\n");

	char curDir[MAX_CWDPATH_SIZE];
	while(fscanf(ptr,"%s",curDir)!=EOF){
	DIR *dir =opendir(curDir);
		if(!dir)
			errorExit("could not open a directory");
		struct dirent *entry;
		while(entry=readdir(dir)){
		if(strcmp(entry->d_name,name)==0)
		{
			if(entry->d_type !=DT_DIR)
			{
				strcpy(buf,curDir);
				return 0;
			}
		}
		}
		closedir(dir);
		
	}
	fclose(ptr);
	return -1;
}

void errorExit(char *error)
{
	fprintf(stderr, "%s", error);
	fprintf(stderr, "%s", strerror(errno));
	exit(-1);
}
void printError(char *message)
{
	fprintf(stderr, "%s", message);
	fprintf(stderr, "%s", strerror(errno));
}

void getprompt(char *promptline){
     char username[MAX_USERNAME_SIZE];
	char hostname[MAX_HOSTNAME_SIZE];
	char cwdPath[MAX_CWDPATH_SIZE];
	if(gethostname(hostname,MAX_HOSTNAME_SIZE)<0)
	 errorExit("failed to get host name\n");
	if(getlogin_r(username,MAX_USERNAME_SIZE)<0)
	 errorExit("failed to get user name\n");
	 if(getcwd(cwdPath,MAX_CWDPATH_SIZE)<0)
	 errorExit("failed to get the current working directory path\n");
	 
	 fflush(stdout);
	 sprintf(promptline, "\033[1;33m%s@%s:%s$\033[0m ", username, hostname, cwdPath);

}
//for removing the spaces either from starting or from the ending of the message
char *trim(char *message)
{
    // Find the start and end of the non-whitespace characters
    int start = 0;
    int end = strlen(message) - 1;

    while (start <= end && (message[start] == ' ' || message[start] == '\t' || message[start] == '\n'))
    {
        start++;
    }

    while (end >= start && (message[end] == ' ' || message[end] == '\t' || message[end] == '\n'))
    {
        end--;
    }

    // Copy the trimmed portion back to the original string
    if (start > 0 || end < (int)strlen(message) - 1)
    {
        memmove(message, message + start, end - start + 1);
        message[end - start + 1] = '\0';
    }

    return message;
}
//for dividing the given input into tokens
 int tokenize(char *usrCommand, char *argv[], int maxargs, int *argc) {
    *argc = 0;
    char *token = strtok(usrCommand, " \t\n");

    while (token != NULL && *argc < maxargs) {
        argv[*argc] = malloc(strlen(token) + 1);

        if (argv[*argc] == NULL) {
            perror("malloc");
            // Free previously allocated memory
            for (int i = 0; i < *argc; i++) {
                free(argv[i]);
            }
            exit(EXIT_FAILURE);
        }

        strcpy(argv[*argc], token);

        (*argc)++;
        token = strtok(NULL, " \t\n");
    }

    argv[*argc] = NULL;

    // Return 0 to indicate successful tokenization
    return 0;
}

//for reversing the string
char *rStr(char *str){
  if(str==NULL) { printError("no string to revers a string\n"); 
		 return NULL;
		}
  int length = strlen(str);
	if(length <= 1) {
		return str;
	}
	for(int left=0,right = length-1 ;left < right;left++,right--){
	 char temp=str[left];
		str[left]=str[right];
		str[right]=temp;
	}
		 return str;
}
//for handling shell commands
 int handleshellCommand(char *cmd[]){
	if(strcmp(cmd[0],"exit")==0){
	printf("exiting from Bindu's Shell\n");
		kill(getppid(),SIGTERM);
		exit(0);
	}
	if (strcmp(cmd[0], "cd") == 0) {
	printf("executing actual cd shell command\n");
        chdir(cmd[1]);
        return 0;     
}
fprintf(stderr,"command not found\n");
}
 
