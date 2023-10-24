#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int iswhitespace(char c){
switch(c){
case ' ':
case '\t':
case '\n':return 1;
default:return 0;

}

}

//function related to count function
void count_function(FILE* file){
int lines=0;
int words=0;
int characters=0;
char c,p='\0';
while((c=fgetc(file))!=EOF){
characters++;
if(iswhitespace(c) && p!='\0' && !iswhitespace(p))
		{
			if(c == '\n'){lines++; if(!iswhitespace(p)) words++;}
			if(c == ' ') words++;
		}
		
		p = c;
	}

	if(c == EOF && p!='\0' && !iswhitespace(p)) words++;
  	printf("characters=%d\t words=%d\t lines=%d\n",characters,words,lines);
}


int main(int argc,char* argv[]){

printf("/***********Bindu Shell Wc command**************/\n");
if(argc>1){
int i;
for(i=1;i<argc;i++)
{
FILE* file=fopen(argv[i],"r");
if(!file){
fprintf(stderr,"unable to open file %s\n",argv[i]);
return 1;
}
else{
count_function(file);
fclose(file);
}
}
}
return 0;
}
