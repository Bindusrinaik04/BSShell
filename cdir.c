#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[]){
printf("/******Bindu cd command******/\n");
if(argc !=2) {
fprintf(stderr,"usage : %s <directory>\n",argv[0]);
return 1;
}

if(chdir(argv[1])!=0){
 fprintf(stderr,"chdir() error");
 return 1;
 }
 char cwd[1024];
 if(getcwd(cwd,sizeof(cwd))!=NULL){
  printf("currrent working directory:%s\n",cwd);
  }
  else {
   fprintf(stderr,"getcwd() error");
   return 1;
   }
   return 0;
   }
