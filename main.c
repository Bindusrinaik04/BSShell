 #include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "myshell.h"
int getusrCommand(char *usrCommand,char*remusrCommand,int max)
{
      char *prompt=(char*)malloc(sizeof(char)*(MAX_CWDPATH_SIZE + MAX_USERNAME_SIZE+MAX_HOSTNAME_SIZE+2));
      getprompt(prompt);
      char *input=readline(prompt);
      int code=0;
      if(!input) exit(-1); //if there was EOF
      trim(input);
      add_history(input);
      int inputlen=strlen(input);
      int i=0,j=inputlen-1;
      while(j>=0 && strcmp(&input[j], "|") != 0)
        { usrCommand[i++]=input[j--];}
      switch(input[j]){
        case '|' :code=1;break; 
        default :break;
      }
      usrCommand[i]='\0';
      input[j]='\0';
      trim(usrCommand);
      rStr(usrCommand);
      strcpy(remusrCommand,input);
      trim(remusrCommand);
      free(prompt);
      return code;
}

void runCommand(char *executablePath,int argc,char *argv[])
{
  char pathName[MAX_CWDPATH_SIZE];
      sprintf(pathName,"%s/%s",executablePath, argv[0]);
      int r=execv(pathName,argv);
      if(r<0)
            errorExit("failed to execute command\n");
}

void getstmt()
{
  char usrCommand[MAX_STATEMENT_LENGTH]; //primary user command
  char remusrCommand[MAX_STATEMENT_LENGTH]; //if there are any options ex:ls -l -a ,ls is primary command,-l -a are stored in remusrCommand 
  
  int p=getusrCommand(usrCommand,remusrCommand,MAX_STATEMENT_LENGTH);//p is used here to indicate whether pipe is present or not
  if(strlen(usrCommand)==0) return ; //if usrCommand length = 0 return meaning the usr did not give any primary input command so return
  char* argv[MAX_STATEMENT_LENGTH];
  int count=0;
  tokenize(usrCommand,argv,MAX_STATEMENT_LENGTH,&count);
      //find the executables of the user command
      char executablePath[MAX_CWDPATH_SIZE];
      int executableE=findExecutable(argv[0],executablePath);
      printf("Debug: argv[0] = %s\n", argv[0]);

      if(executableE < 0){
      //means the command might not be past of our list :ls,ps,so handle it as shell command
            handleshellCommand(argv);
      }
      else{
            //it is from the list of commands we are executing as part of this assignment:ls,ps
            pid_t child1;
            child1=fork();
            if(child1<0){
                  printError("fork failed\n");
                  return;
            }
            if(child1==0){
                if(p==1) //there is need for inter process communication 
                {
                int mainpipe[2]; //used to send the output from child to parent
                      int commandpipe[2];//used to send the remaining command to the child from parent
                if(pipe(mainpipe)<0) {
                      printError("pipe failed\n");
                      return;
                }
                      if(pipe(commandpipe)<0)
                      {
                            printError("pipe failed\n");
                            return;
                      }
                      pid_t child2;
                      if((child2=fork())<0)
                      {
                            printError("fork failed\n");
                            return;
                      }
                      if(child2==0)
                      {
                            //its output goes to mainpipe
					close(mainpipe[0]);
					dup2(mainpipe[1], 1);
				
					//it reads the input from the command pipe.
					close(commandpipe[1]);
					dup2(commandpipe[0], 0);

					getstmt();
					exit(0);
				}
                      else{
                            //child1 after forking child2
                            close(mainpipe[1]);
                            dup2(mainpipe[0],0);
                            //write remaining command to command pipe
                            close(commandpipe[0]);
                            write(commandpipe[1],remusrCommand,strlen(remusrCommand));

                            runCommand(executablePath,count,argv);
                            exit(0);
                      }
                }
                      
                else
			{
				runCommand(executablePath, count, argv);
				exit(0);
			}
		}
		else
		{
			//root shell waits for child to finish.
			wait(NULL);
		}
	}
}
int main(char* argc,char* argv[]){
initpath();

while(1){
getstmt();
}
return 0;
}

