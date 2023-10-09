#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "myshell.h"
#include<string.h>

void print_header(){
 printf("PID \tProcess_Name \tstate \t\tppid\n");
}

int readstatfile(const char *proc_dir) {
    char stat_path[256];
    snprintf(stat_path, sizeof(stat_path), "%s/stat", proc_dir);

    // Opening and processing the stat file
    FILE *fp = fopen(stat_path, "r");
    if (fp == NULL) {
        printf("Error while opening the stat file of %s\n", proc_dir);
        return 1;
    }

    char content[1024];
    if (fgets(content, sizeof(content), fp) == NULL) {
        printf("Error reading stat file\n");
        fclose(fp);
        return 1;
    }

     int stat_pid;
    char stat_comm[256];
    char stat_state;
    int stat_ppid;
    
    if (sscanf(content, "%d (%255[^)]) %c %d", &stat_pid, stat_comm, &stat_state, &stat_ppid) != 4) {
        printf("Error while parsing stat file\n");
        fclose(fp);
        return 1;
    }

     printf("%-8d%-20s%-16c%-16d\n", stat_pid, stat_comm, stat_state, stat_ppid);

    fclose(fp);
    return 0;
}

void print_help(int help_form){
if(help_form){
 printf("usage of ps command: listing the processes  with their PID\n syntax : ps -options \n-h displays the help info\n");
 }
 }
  

int main(int argc,char *argv[]) {
    printf("***********Bindu Sri**********\n");
   int help_form=0;
    const char *target = "/proc";
    if(argc>1){
    for(int i=1;i<argc;i++){
      if(strcmp(argv[i],"-h")==0) { help_form++;print_help(help_form); return 0; }
       
      else { printf("use valid options for ps (i.e,-h ,ps pid or simple ps)\n");
       return 1;
       }

} }
    
    // Open the /proc directory
    DIR *dir = opendir(target);
    if (dir == NULL) {
        printf("Error with opening target\n");
        exit(1);
    }
    print_header();
    // Read and display processes in the /proc directory
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char *name = entry->d_name;
            int pid = atoi(name);
            if (pid > 0) {
                char process_dir[256];
                snprintf(process_dir, sizeof(process_dir), "%s/%s", target, name);
                if (readstatfile(process_dir) != 0) {
                    printf("Error while processing the contents of the directory\n");
                }
            }
        }
    }

    closedir(dir);

    return 0;
}
