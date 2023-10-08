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
	
	FILE *fptr = fopen(filePath, "w");

	fprintf(fptr, "%s ", "./");
	fprintf(fptr, "%s ", "/bin/");
	fprintf(fptr, "%s ", "/usr/bin/");
	fprintf(fptr, "%s ", "/usr/sbin/");

	fclose(fptr);
}
	
}

void errorExit(char *error)
{
	fprintf(stderr, "%s", error);
	fprintf(stderr, "%s", strerror(errno));
	exit(-1);
}
void printErr(char *message)
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
	 if(getcwd(cwdpath,MAX_CWDPATH_SIZE)<0)
	 errorExit("failed to get the current working directory path\n");
	 
	 fflush(stdout);
	 sprintf(promptline, "\033[1;33m%s@%s:%s$\033[0m ", username, hostname, cwdPath);

}

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

int tokenize(char *usrCommand,char *argv[],int Maxargs,int* argc){
	*argc =0;
 char *token = strtok(usrCommand, " \t\n");
while(token !=NULL && *argc < maxArgs) {
         
        argv[*argc] = strdup(token);

         
        (*argc)++;
        token = strtok(NULL, " \t\n");
    }

     
    argv[*argc] = NULL;

    // Return 0 to indicate successful tokenization
    return 0;
}

