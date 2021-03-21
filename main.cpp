#include <fstream>
#include "Node.h"
#include "Arvore.h"
#include "HashTable.h"
#include <vector>
#include <deque>

/*	
*	Autor: Jian Furquim 161152063
*	Tema: Exercício_4 Caicheiro Viajante
*	Diciplina: IA
*	Professor: Marcelo luizelli
*	Compilar: usando o terminal no caminho que se encontra os arquivos digite: make
*       Exe: ./main grafo.txt node-start node-finish
*/

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		std::cout << argv[0] << " entrada.txt node-start node-finish" <<endl;
		exit(0);
	}

	 // grafo principal
	std::vector<Node> graph;

	//variaveis auxiliares 
	int vert=1, adja=1, cost, temp=0;
	
	ifstream iFILE(argv[1]);

	Node* node = new Node();
	node->value = 0;
	node->visited = false;
	//Inserção do nodo 0 serve para o metodo busca não retornar false no indice do primeiro nodo.
	graph.push_back((Node)*node);
	graph[0].adj = graph[0].adj->arv_Insere(graph[0].adj, 0, 0, 0);
	
	int cont=0;

	while(!iFILE.eof()) 
	{	
		iFILE >> vert;
		iFILE >> adja;
		iFILE >> cost;
		graph[0].insertElements(&graph, vert, adja, cost);
	}

	iFILE.close();

	std::cout << "Print Graph: "<<endl;
	//método de impressão do grafo
	graph[0].printGraph(graph);
	std::cout <<endl;

	//Vetor de deques para salvar todos os caminhos gerados pelo caicheiro viajante
	std::vector< std::deque<int> > vet;
	//Deque para salvar os caminhos percorridos pelo caicheiro viajante
	std::deque<int> road;
	//Tabela hash para ser usada como auxilio no caicheiro viajante 
	HashTable hash;
	//Elemento inserido para ser usado como parametro pelo searchTravelingSalesmanSpeed que salva só o melhor caminho
	road.push_back(99999);
	 //inserção do deque que contem o elemento
	vet.push_back(road);
	//limpa o deque
	road.clear(); 
	graph[0].searchTravelingSalesmanSpeed(
		graph, hash, graph[0].adj->arv_Busca(graph[0].adj, atoi(argv[2])),
		graph[0].adj->arv_Busca(graph[0].adj, atoi(argv[3])),
		0,
		&vet,
		road);
	// printa caminhos retornados pelos caicheiro viajante, e o melhor caminho separado
	graph[0].printTravelingSalesman(vet);

	vet.clear(); // limpa vetor de deques
	road.clear();  // limpa deque 
	graph.clear(); //limpa o grafo
}
