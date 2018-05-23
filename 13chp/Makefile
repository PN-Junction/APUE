CC = gcc
INC=-I. -I./lib
APUEERR = /home/hanxu/Documents/APUE/apue.3e/error.c
CFLAGS = -g -Wall 
LIB=-lpthread

OBJ = 13-7p.o daemonize.o
PRG = out

$(PRG) : $(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(APUEERR)

.SUFFIXES:.c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $*.c -o $*.o

#13-7p.o: apue.h pthread.h syslog.h daemonize.h
#daemonize.o: daemonize.h

.PHONY:clean
clean :
	rm $(OBJ) $(PRG);

