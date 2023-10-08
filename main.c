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
int getusrCommand(char *usrCommand,char*remusrCommand,int MAX_STATEMENT_LENGTH)
{
      char *prompt=(char*)malloc(sizeof(char)*(MAX_CWDPATH_SIZE + MAX_USERNAME_SIZE+MAX_HOSTNAME_SIZE+2));
      getprompt(prompt);
      char *input=readline(prompt);
      int code=0;
      if(!input) exit(-1); //if there was EOF
      trim(input);
      add_history(input);
      int inputlen=strlen(input);
      int i=0j=inputlen-1;
      while(j>=0 && input[j]!="|")
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
     
  
}

void getstmt(){
  char usrCommand[MAX_STATEMENT_LENGH]; //primary user command
  char remusrCommand[MAX_STATEMENT_LENGTH]; //if there are any options ex:ls -l -a ,ls is primary command,-l -a are stored in remusrCommand 
  int p=getusrCommand(usrCommand,remusrCommand,MAX_STATEMENT_LENGTH);//p is used here to indicate whether pipe is present or not
  if(strlen(usrCommand)==0) return ; //if usrCommand length = 0 return meaning the usr did not give any primary input command so return
  char* argv[MAX_STATEMENT_LENGTH];
  int count=0;
  tokenize(usrCommand,argv,MAX_STATEMENT_LENGTH,count);
  
}

int main(char* argc,char* argv[]){
initpath();

while(1){
getstmt();
}
return 0;
}


