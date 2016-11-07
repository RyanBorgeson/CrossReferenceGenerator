CC = gcc
CFLAGS = -Wall
EXEC = CrossReference
INCLS =
LIBS =

OBJS = CrossReference.o list.o queue.o

$(EXEC): $(OBJS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)
	@rm *.o

$(OBJS): list.h queue.h
	$(CC) $(CFLAGS) $(INCLS) -c $*.c