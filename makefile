CC=gcc
BUILD_FLAGS=-c

test: btf.o
	$(CC) test.c btf.o -o test

btf.o: btf.c
	$(CC) $(BUILD_FLAGS) btf.c

clean:
	rm -rf *.o
	rm -rf test

