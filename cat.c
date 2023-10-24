#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char* argv[]){
printf("/***********Bindu Shell Cat command**********/\n");
if(argc ==1) { printf("enter the file name to be read/displayed\n");
               return 0;}
               else{
for(int i = 1; i < argc; i++)
		{
			FILE * ptr = fopen(argv[i], "r");
			if(!ptr)
			{
				fprintf(stderr, "no such file: %s\n", argv[i]);
				FILE* file= fopen(argv[i],"w");
				if(file !=NULL)printf("File %s created\n",argv[i]);
				else printf("error while creating the %s\n",argv[i]);
				fclose(file);
				
			}
			else
			{
				fprintf(stderr, "READING FILE: %s\n", argv[i]);
				char c;
				while((c = fgetc(ptr)) != EOF)
					printf("%c", c);
			}
			fclose(ptr);
		}
	}
	return 0;
}
