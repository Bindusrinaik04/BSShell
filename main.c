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


