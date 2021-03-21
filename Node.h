#ifndef NODE_H
#define NODE_H

#include <vector>
#include <deque>
#include "Arvore.h"
#include "HashTable.h"

/*
*	Autor: Jian Furquim 161152063
*	Tema: Caicheiro Viajante
*	Descrição: Class pricipal pra manutenção do graph
*	Professor: Marcelo Luizelli
*/

using namespace std;

class Node
{
public:
	int value;
	bool visited;
	Arv* adj = NULL;

	void insertNode(std::vector <Node> *graph, int value); //Metodo para inserir um novo Nodo
	void printGraph(std::vector <Node> graph);	//Método para imprimir o grafo
	void searchTravelingSalesmanSpeed(std::vector<Node> graph, HashTable hash, int indexStart, int indexFinish, int cost, std::vector< std::deque<int> > *vet, std::deque<int> road); //Caicheiro Viajante com um numero reduzido de iterações salvando so o melhor caminho
	void printTravelingSalesman(std::vector< deque<int> > vet); //Método para imprimir os caminhos do caicheiro viajante, e o melhor deles.
	bool checkexist_Adj(Arv* adj, int index_value); //Método para testar se uma adjacencia ja existe na arvore de adjacencias de um Nodo
	bool allVisited(std::vector<Node> graph); //Método para testar se todos os nodos do grafo já foram visitados 
	void converse_Vect(Arv* a, std::deque<int> *vet, std::vector<Node> graph); //método pra converter uma arvore de adjacencias em um vetor.
	void insertElements(std::vector<Node> *graph, int vert, int adja, int cost);
};
#endif