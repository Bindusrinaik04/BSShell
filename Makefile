 all: bsshell ls ps cat mkdir wc echo cdir
bsshell: myshell.c main.c myshell.h
	gcc myshell.c main.c -lreadline -o bsshell
wc: wc.c
	gcc wc.c -o wc
cat: cat.c
	gcc cat.c -o cat
echo: echo.c
	gcc echo.c -o echo
mkdir: mkdir.c
	gcc mkdir.c -o mkdir
ls: ls.c
	gcc ls.c -o ls
ps: ps.c
	gcc ps.c -o ps
cdir: cdir.c
	gcc cdir.c -o cdir
