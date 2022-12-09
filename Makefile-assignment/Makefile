# Makefile for hW3

# Definitions
CC = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
OBJS = file0.o file1.o file2.o file3.o file4.o main.o
EXEC = prog.exe
RM = rm -f

# Link the final executable (Instructions for the Linker)
$(EXEC): $(OBJS)
	$(CCLINK) -o $(EXEC) $(OBJS)

# Compile file0.c to create file0.o
flie0.o: file0.c file0.h file1.h file4.h
	$(CC) -c $(CFLAGS) file0.c

# Compile file1.c to create file1.o
flie1.o: file1.c file1.h file4.h
	$(CC) -c $(CFLAGS) file1.c

# Compile file2.c to create file2.o
flie2.o: file2.c file0.h file1.h file2.h
	$(CC) -c $(CFLAGS) file2.c

# Compile file3.c to create file3.o
flie3.o: file3.c file3.h file4.h
	$(CC) -c $(CFLAGS) file3.c

# Compile file4.c to create file4.o
flie4.o: file4.c file0.h file4.h
	$(CC) -c $(CFLAGS) file4.c

# Compile main.c to create main.o
main.o: main.c file0.h file1.h file2.h file3.h file4.h
	$(CC) -c $(CFLAGS) main.c
	

# Clean
clean:
	$(RM) $(EXEC) $(OBJS)
