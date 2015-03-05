### Assignment 26, Basic Date Class 2
### the main rule
a.out: dateTest.o date.o
	g++ -o a.out dateTest.o date.o
	tar -cf assign26.tar *.h *.cpp makefile

### for the object files
dateTest.o: dateTest.cpp date.h
	g++ -c dateTest.cpp

date.o: date.cpp date.h
	g++ -c date.cpp

### cleanup
clean:
	rm a.out *.o *.tar