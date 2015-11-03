.SUFFIXES: .h .c .cpp .l .o

all: osproj2a osproj2b osproj2c

osproj2a: osproj2a.c
	g++ -pthread -ggdb osproj2a.c -o osproj2a
osproj2b: osproj2b.cpp
	g++ -pthread -ggdb osproj2b.cpp -o osproj2b
osproj2c: osproj2c.cpp
	g++ -pthread -ggdb osproj2c.cpp -o osproj2c
clean:
	/bin/rm -f *.o *~ core osproj2a osproj2b osproj2c
