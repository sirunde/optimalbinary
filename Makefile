all: main

main: main.o kf.o bst.o bst_node.o
	g++ main.o kf.o bst.o bst_node.o -o main

main.o : main.cpp kf.h bst.h bst_node.h
	g++ -c main.cpp

kf.o : kf.cpp kf.h
	g++ -c kf.cpp

bst.o : bst.cpp bst.h bst_node.h	
	g++ -c bst.cpp

bst_node.o : bst_node.cpp bst_node.h
	g++ -c bst_node.cpp

clean:
	rm -rf *.o main