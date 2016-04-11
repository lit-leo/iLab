test: main.o vector.o vector.h
	g++ main.o vector.o -o test
main.o: main.cpp
	g++ -c main.cpp -o main.o
stack.o: vector.cpp
	g++ -c vector.cpp -o vector.o
vector.h:
	echo head