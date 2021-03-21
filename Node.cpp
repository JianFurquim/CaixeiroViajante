#include "Node.h"
#include "Arvore.h"
#include "HashTable.h"
#include <vector>
#include <deque>
#include <list>

using namespace std;

void Node::insertNode(std::vector<Node> *graph, int i)
{
	Node* node = new Node();
	node->value = i;
	node->visited = false;
	graph->push_back((Node)*node);

}

void Node::insertElements(std::vector<Node> *grafo, int vert, int adja, int cost)
{
	std::vector<Node> graph = *grafo;
	int index, index_adj;
	
	index = graph[0].adj->arv_Busca(graph[0].adj, vert); //busca Vertice novo na arvore auxiliar

	if(index == 0) //Se o vertice não existe na arvore auxiliar/grafo
	{ 
		graph[0].insertNode(&graph, vert); //insere o novo vertice no grafo
		index = graph.size()-1; //atualiza o indice do vertice
		graph[0].adj = graph[0].adj->arv_Insere(graph[0].adj, vert, index, 0); //insere na arvore auxiliar para mante-la atulizada
		index_adj = graph[0].adj->arv_Busca(graph[0].adj, adja); //busca Adjacencia na arvora auxiliar

		if(index_adj == 0) //Se a adjacencia não existe na arvore auxiliar/grafo
		{	
			graph[0].insertNode(&graph, adja); //Insere a adjacencia no grafo
			index_adj = graph.size()-1; //atuliza o indice da adjacencia
			
			graph[0].adj = graph[0].adj->arv_Insere(graph[0].adj, adja, index_adj, 0); //insere a adjacencia na arvore auxiliar

			if(!graph[0].checkexist_Adj(graph[index].adj, index_adj)) //testa se a adjacencia se encontra na arvore de adjacencias do Nodo vertice
			{
				graph[index].adj = graph[index].adj->arv_Insere(graph[index].adj, index_adj, adja, cost); //insere a adjacencia na arvore de adjacencias do nodo vertice
																										//(nesta inserção a info e o indice são trocados de posição, porque as buscas nas arvores de adjacencias dos nodos
																										// o mais importante vai ser o indice que tal adjacencia se encontra no grafo).
			}
		}
		else //se a adjacencia ja existe no grafo
		{
			if(!graph[0].checkexist_Adj(graph[index].adj, index_adj)) //testa se a adjacencia se encontra na arvore de adjacencias do Nodo vertice
			{
				graph[index].adj = graph[index].adj->arv_Insere(graph[index].adj, index_adj, adja, cost);
			}
		} 		
	}
	else //Se o vertice já é um nodo no grafo
	{
		index_adj = graph[0].adj->arv_Busca(graph[0].adj, adja); //busca Adjacencia na arvora auxiliar
											//Repete os mesmo procedimentos do bloco de cima.
		if(index_adj == 0)
		{	
			graph[0].insertNode(&graph, adja);
			index_adj = graph.size()-1;
			
			graph[0].adj = graph[0].adj->arv_Insere(graph[0].adj, adja, index_adj, 0);
			
			if(!graph[0].checkexist_Adj(graph[index].adj, index_adj))
			{
				graph[index].adj = graph[index].adj->arv_Insere(graph[index].adj, index_adj, adja, cost);
			}
		}	
		else
		{
			if(!graph[0].checkexist_Adj(graph[index].adj, index_adj))
			{
				graph[index].adj = graph[index].adj->arv_Insere(graph[index].adj, index_adj, adja, cost);
			}
		}
	}
	*grafo = graph;
}

bool Node::checkexist_Adj(Arv* adj, int index_value)
{
	int value = adj->arv_Busca(adj, index_value);
	return value;
}

void Node::printGraph(std::vector<Node> graph)
{
	if(graph.size() != 0)
	{
		for(int i=1; i < graph.size(); i++)
		{
			if(graph[i].adj != NULL)
			{
				std::cout << graph[i].value << " -> ";
				graph[i].adj->arv_Imprime(graph[i].adj);
				std::cout<< "NULL" <<endl;
			}
			else
				std::cout << graph[i].value << " -> NULL" <<endl;
		}
	}
	else std::cout << "Graph empty !" <<endl;
	graph.clear();
}

bool Node::allVisited(std::vector<Node> graph)
{
	for(int i=1; i<graph.size(); i++)
	{
		if(graph[i].visited != true)
		{
			return false;
		} 
	}
	return true;
}

void Node::converse_Vect(Arv* a, std::deque<int> *vet, std::vector<Node> graph) // função para imprimir a arvore
{
	if(a != NULL) // testa se arvore nao e vazia
	{
		if(graph[a->info].visited) vet->push_back(a->info);
		else vet->push_front(a->info);
		// vet->push_front(a->info);

		if( a->esq != NULL)
		{
			converse_Vect(a->esq, vet, graph);
		}	
		
		if( a->dir != NULL)
		{
			converse_Vect(a->dir, vet, graph);
		}
		else return;
	}
}

void Node::searchTravelingSalesmanSpeed(std::vector<Node> graph, HashTable hash, int indexStart, int indexFinish, int cost, std::vector< std::deque<int> > *vet, std::deque<int> road)
{
	graph[indexStart].visited = true;
	road.push_back(graph[indexStart].value);

	if(graph[indexStart].value == graph[indexFinish].value && allVisited(graph))
	{
		int veryCost = vet->front().front();

		if(cost < veryCost)
		{
			vet->clear();
			road.push_front(cost);
			vet->push_back(road);
			road.clear();	
		}
	}
	else
	{
		std::deque<int> aux;
		graph[indexStart].converse_Vect(graph[indexStart].adj, &aux, graph);

		for(int i=0; i<aux.size(); i++)
		{
			int key = hash.createKey(graph[indexStart].value, graph[aux[i]].value);
			int temp = graph[indexStart].adj->costNode(graph[indexStart].adj, aux[i]);
			
			if(!hash.get((int*)key) && (cost+temp < vet->front().front()))
			{	
				hash.put((int*)key, (int*)road.front());
				searchTravelingSalesmanSpeed(graph, hash, aux[i], indexFinish, cost+temp, vet, road);
			}			
		}
		aux.clear();
	}

	graph.clear();
	hash.clean();
	return;
}

void Node::printTravelingSalesman(std::vector< std::deque<int> > vet)
{
	if(vet.size() == 0) std::cout << "Impossible way, not found!! "<<endl;
	else
	{

		std::cout<<endl<< "Best way: " <<endl;
		for(int j=1; j<vet[0].size(); j++)
		{
			std::cout << vet[0][j] << " -> ";
		}
		std::cout << "Cost: " << vet[0][0] <<endl;
	}

	vet.clear();
}