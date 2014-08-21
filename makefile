#file: makefile

CC=g++
CFLAGS=-Wall

all: main doc

main: main.o infix.o postfix.o operator.o
	$(CC) $(CFLAGS) -o main main.o infix.o postfix.o operator.o
main.o: main.cpp infix.h postfix.h stack.cpp stack.h operator.h
	$(CC) $(CFLAGS) -c main.cpp
infix.o: infix.cpp infix.h stack.cpp stack.h operator.h
	$(CC) $(CFLAGS) -c infix.cpp
postfix.o: postfix.cpp postfix.h stack.cpp stack.h operator.h
	$(CC) $(CFLAGS) -c postfix.cpp
operator.o: operator.cpp operator.h
	$(CC) $(CFLAGS) -c operator.cpp

doc:
	doxygen -g
	./procDoxyfile.sh
	doxygen
	make -C latex/

clean:
	rm -f *.o *~ main Doxyfile Doxyfile.bak
	rm -rf html/ latex/
