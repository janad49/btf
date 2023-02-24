CC = gcc
WARN = -Wall
LDFLAGS = -c
OBJS = zipio.o crc.o inflate.o getopt.o

btf: $(OBJS)
	$(CC) -o btf btf.c $(OBJS)

zipio.o:
	$(CC) $(LDFLAGS) zipio.c -o zipio.o
