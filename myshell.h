#ifndef BSShell
#define BSShell

//maximum sizes for host name,username,current working directory,shell command statement
#define MAX_HOSTNAME_SIZE 256
#define MAX_USERNAME_SIZE 256
#define MAX_CWDPATH_SIZE 1024
#define MAX_STATEMENT_LENGTH 2048

//functions prototype
void initPath();

void getprompt(char *);
void printError(char *);
void errorExit(char *);

int shellCommand();
int token(char *, char **, int, int *);
char *trim(char *);
char *rStr(char *);

#endif

