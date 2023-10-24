#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char* argv[]){
printf("/******Bindu Shell mkdir command********/\n");
if(argc==1){
fprintf(stderr,"mkdir Usage: %s <pathname>",argv[0]);
return 1;
}

else {
int directory_status=mkdir(argv[1],0777);
if(directory_status<0){
fprintf(stderr,"creation of %s directory failed",argv[1]);
return 1;
}
}
return 0;
}
