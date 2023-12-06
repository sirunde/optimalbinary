all: main

main: main.o kf.o bst.o bst_node.o
	g++ -Wall -std=c++11 main.o kf.o bst.o bst_node.o -o main

main.o : main.cpp kf.h bst.h bst_node.h
	g++ -Wall -std=c++11 -c main.cpp

kf.o : kf.cpp kf.h
	g++ -Wall -std=c++11 -c kf.cpp

bst.o : bst.cpp bst.h bst_node.h	
	g++ -Wall -std=c++11 -c bst.cpp

bst_node.o : bst_node.cpp bst_node.h
	g++ -Wall -std=c++11 -c bst_node.cpp

clean:
	rm -rf *.o main