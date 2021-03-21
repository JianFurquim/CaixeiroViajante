output: main.o Node.o Arvore.o HashTable.o
	g++ -std=c++11 main.o Node.o Arvore.o HashTable.o -o main

Arvore.o: Arvore.cpp Arvore.h
	g++ -c -std=c++11 Arvore.cpp

Node.o: Node.cpp Node.h
	g++ -c -std=c++11 Node.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -c -std=c++11 HashTable.cpp

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

clean:
	rm -rf *.o main
