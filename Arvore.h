#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <cstdlib> 
#include <vector>
#include <deque>

/*
*	Autor: Jian Furquim 161152063
*	Tema: Caicheiro Viajante
*	Descrição: Class para Heap auxiliar no algoritimo
*	Professor: Marcelo Luizelli
*/

using namespace std;

class Arv //Class Heap binaria
{
	public:
		
		int info; // informação do nodo
		int index; // index do nodo no grafo
		int cost; // custo do caminho para o nodo
		Arv* esq; // ponteiro para esquerda
		Arv* dir; //ponteiro para direita

		int arv_Vazia(Arv* a); // cria arvore vazia
		int arv_Busca(Arv* r, int v); //busca um nodo especifico atraves da sua informação
		int costNode(Arv* arv, int value); //Método para ver quanto custa para ir de um Nodo para uma adjacencia.
		Arv* arv_Cria(int c, int index, Arv* sae, Arv* sad); // cria um nodo completo
		Arv* arv_Libera(Arv* a); //libera uma arvore
		Arv* arv_Insere(Arv* a, int v, int index, int cost); //insere um novo nodo
		Arv* arv_Retira(Arv* r, int v); // retira um nodo
		void arv_Imprime(Arv* a); // imprime a arvore
		void arv_Cont_Leaf(Arv* r , int* cont); // conta as folhas
		void arv_Converse_Vect(Arv* a, std::deque<int> *vet); //método para converter uma arvore em vetors

};
#endif