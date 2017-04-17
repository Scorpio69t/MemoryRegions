CC = clang
CFLAGS = -g -Wall

PROG = main

OBJS = main.o regions.o linkedlist.o objectindex.o

$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

