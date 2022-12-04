CC = gcc
CFLAGS = -g -Wall
LDLIBS = -lreadline

ysh: ysh.o builtin.o
ysh.o: ysh.c
builtin.o: builtin.c

clean:
	rm *.o ysh
