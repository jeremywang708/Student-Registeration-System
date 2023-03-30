CC=gcc
CFLAGS=-g -ansi -pedantic -Wall -w
OBJS=main.o student.o course.o menu.o

all: myprogram

myprogram: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myprogram

main.o: main.c student.h course.h menu.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

course.o: course.c course.h
	$(CC) $(CFLAGS) -c course.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f $(OBJS) myprogram
