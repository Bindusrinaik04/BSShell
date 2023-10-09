  #include <stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include "myshell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<string.h>


void print_entry(const char*entry_name,int show_hidden){
struct stat entry_stat;
if(stat(entry_name,&entry_stat)==-1){
perror("stat error\n");
return;
}
if(!show_hidden && entry_name[0]=='.')
return;

printf("%s \n",entry_name);
  
}

void print_help(int help_form){
if(help_form){
 printf("usage of ls command: listing the directories\n syntax : ls -options directory path\n -a :shows hidden files and directories \n- -h displays the help info\n");
 }
 }

int main(int argc,char *argv[]){
printf("======Bindu Shell====\n");
int show_hidden=0;
int long_format=0;
int help_form=0;
const char *dir_path =".";

//parse the command line options
for(int i=1;i<argc;i++){
if(argv[i][0]=='-'){
if(argv[i][1]=='a') show_hidden =1;
 
else if(argv[i][1]=='h') { help_form++;print_help(help_form); return 0; }
else { printf("use valid options for ls (i.e,-a,-h)\n");
       return 1;
       }

}
else {
 dir_path=argv[i];
}
}

DIR *directory = opendir(dir_path);
if(directory == NULL){
perror("open dir error\n");
return 1;
}

struct dirent *entry;
while((entry=readdir(directory))!=NULL){
print_entry(entry->d_name,show_hidden);
}

closedir(directory);
return 0;
}
