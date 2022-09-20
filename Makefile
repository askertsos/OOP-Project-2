Client	:	Myclasses.o main.cpp
	g++  Myclasses.o -o Client main.cpp

Myclasses.o	:	Myclasses.cpp
	g++ -c Myclasses.cpp

clean	:
	rm Client Myclasses.o
