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

	std::vector<Node> graph; // grafo principal
	int vert=1, adja=1, cost, temp=0; //variaveis auxiliares 
	
	ifstream iFILE(argv[1]);

	Node* node = new Node();
	node->value = 0;
	node->visited = false;
	graph.push_back((Node)*node); //Inserção do nodo 0 serve para o metodo busca não retornar false no indice do primeiro nodo.
	graph[0].adj = graph[0].adj->arv_Insere(graph[0].adj, 0, 0, 0);
	
	int cont=0;

	while(!iFILE.eof()) 
	{	
		iFILE >> cost;
		graph[0].insertElements(&graph, vert, adja, cost);

		adja++;
		if(adja == 48)
		{
			vert++;
			adja=1;
		}
	}

	iFILE.close();

	std::cout << "Print Graph: "<<endl;
	graph[0].printGraph(graph);    //método de impressão do grafo
	std::cout <<endl;

	std::vector< std::deque<int> > vet; //Vetor de deques para salvar todos os caminhos gerados pelo caicheiro viajante
	std::deque<int> road; //Deque para salvar os caminhos percorridos pelo caicheiro viajante
	HashTable hash; //Tabela hash para ser usada como auxilio no caicheiro viajante
	road.push_back(99999); //Elemento inserido para ser usado como parametro pelo searchTravelingSalesmanSpeed que salva só o melhor caminho
	vet.push_back(road); //inserção do deque que contem o elemento
	road.clear(); //limpa o deque
//	graph[0].searchTravelingSalesmanSpeed(graph, hash, graph[0].adj->arv_Busca(graph[0].adj, atoi(argv[2])), graph[0].adj->arv_Busca(graph[0].adj, atoi(argv[3])), 0, &vet, road);
	graph[0].printTravelingSalesman(vet); // printa caminhos retornados pelos caicheiro viajante, e o melhor caminho separado

	vet.clear(); // limpa vetor de deques
	road.clear();  // limpa deque 
	graph.clear(); //limpa o grafo
}
