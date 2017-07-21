cc = gcc
all:
	$(cc) my_ls.c -o my_ls -g
clear:
	rm -f my_ls

