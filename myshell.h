 #ifndef BSShell
#define BSShell
#define MAX_HOSTNAME_SIZE 256
#define MAX_USERNAME_SIZE 256
#define MAX_CWDPATH_SIZE 1024
#define MAX_STATEMENT_LENGTH 2048


//functions prototype
void initpath();

void getprompt(char *);
void printError(char *);
void errorExit(char *);

int handleshellCommand(char *[]);
int tokenize(char *, char **, int, int *);
char *trim(char *);
char *rStr(char *);
int findExecutable(char *,char *);

#endif
//maximum sizes for host name,username,current working directory,shell command statement
