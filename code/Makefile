all: myfile

myfile: main.o CSP.o utility.o Node.o
		g++ main.o CSP.o utility.o Node.o -o myfile

main.o: main.cpp CSP.cpp utility.cpp Node.cpp
	g++ -c -g main.cpp CSP.cpp utility.cpp Node.cpp

CSP.o: CSP.cpp utility.cpp Node.cpp CSP.h
	g++ -c -g CSP.cpp utility.cpp Node.cpp CSP.h

utility.o: utility.cpp CSP.cpp Node.cpp utility.h
	g++ -c -g utility.cpp CSP.cpp Node.cpp utility.h

Node.o: Node.cpp Node.h
	g++ -c -g Node.cpp Node.h


clean:
	rm *.o myfile
