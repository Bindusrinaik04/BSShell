 all: bsshell ls ps
bsshell: myshell.c main.c myshell.h
         gcc myshell.c main.c -lreadline -o bsshell
ls: ls.c
    gcc ls.c -o ls
ps: ps.c
    gcc ps.c -o ps
