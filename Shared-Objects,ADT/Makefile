CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=grades.o 
EXEC=prog.exe
RM=grades.o libgrades.so

libgrades.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libgrades.so -llinked-list -L.
	
#list of dependency rules
grades.o: grades.c grades.h linked-list.h
	$(CCLINK) -c -fpic grades.c

clean:
	rm -rf $(RM)
	
