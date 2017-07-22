#use -D USEDEBUG to see debug message

COMPLIEONLY = g++ -std=c++11 -Wall -c 
LINKOBJ = g++ -std=c++11 -Wall 

program: main.o ast.o parser.o
		$(LINKOBJ) main.o ast.o parser.o -o program

main.o:	main.cpp ast.h parser.h
		$(COMPLIEONLY) main.cpp -o main.o

ast.o: ast.h ast.cpp 
		$(COMPLIEONLY) ast.cpp -o ast.o

parser.o: parser.h parser.cpp ast.h
		$(COMPLIEONLY) parser.cpp -o parser.o

clean:
		rm *.o