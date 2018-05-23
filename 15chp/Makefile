CC = gcc
INC=-I.
APUEERR = /home/hanxu/Documents/APUE/apue.3e/error.c
CFLAGS = -g -Wall 
LIB=-lpthread

OBJ = 15-31p.o 
PRG = out

$(PRG) : $(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ) $(APUEERR)

.SUFFIXES:.c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $*.c -o $*.o


.PHONY:clean
clean :
	rm $(OBJ) $(PRG);

