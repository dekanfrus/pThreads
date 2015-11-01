.SUFFIXES: .h .c .cpp .l .o
osproj2a: osproj2a.c
	g++ -pthread osproj2a.c -o pi
clean:
	/bin/rm -f *.o *~ core pi fib
