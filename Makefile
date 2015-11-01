.SUFFIXES: .h .c .cpp .l .o
osproj2a: osproj2a.c
	g++ -pthread osproj2a.c -o osproj2a
clean:
	/bin/rm -f *.o *~ core osproj2a
