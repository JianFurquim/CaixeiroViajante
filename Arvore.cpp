#include <vector>
#include <deque>
#include "Arvore.h"

using namespace std;
	
int Arv::arv_Vazia(Arv* a) 
{
	return (a==NULL); 
}

Arv* Arv::arv_Cria(int c, int index, Arv* sae, Arv* sad) // criação de um novo nodo
{
	Arv* a = new Arv; //aloca memoria 
	a->info=c; //guarda a informação no campo info
	a->index=index;
	a->esq=sae; //guarda o endereço da esquerda no ponteiro da esquerda
	a->dir=sad; //guarda o endereço da direita no ponteiro da direita
	return a; //retorna o nodo criado
}

Arv* Arv::arv_Libera(Arv* a)
{
	if(!arv_Vazia(a)) //testa se arvore nao esta vazia 
	{
		arv_Libera(a->esq); //libera recursivamente
		arv_Libera(a->dir);
		delete a;
	}
	return NULL; // retorna nulo
}

void Arv::arv_Imprime(Arv* a) // função para imprimir a arvore
{
	if(a != NULL) // testa se arvore nao e vazia e imprime
	{
		cout << a->index << " -> ";
 
		if( a->esq != NULL)
		{
			arv_Imprime(a->esq);
		}	
		
		if( a->dir != NULL)
		{
			arv_Imprime(a->dir);
		}
		else return;
	}
}

Arv* Arv::arv_Insere(Arv* a, int v, int index, int cost) // função para inserir um novo nodo
{
	if(a==NULL)
	{
		a = new Arv(); // aloca memoria 
		a->info = v; // salva a informação
		a->index = index; //indice no grafo
		a->cost = cost;
		a->esq = NULL; // ponteiro da esquera aponta nulo
		a->dir = NULL; // ponteiro da direita aponta nulo
	}
	else if(v < a->info) // se v for menor que a raiz insere na esquerda
		a->esq = arv_Insere(a->esq , v, index, cost); 
	else
		a->dir = arv_Insere(a->dir , v, index, cost); // se v for maior que a raiz insere na direita
	
	// a = arv_balance(a);
	return a;
}

int Arv::arv_Busca(Arv* r, int value) // busca um elemento
{
	if(r == NULL) // testa se a arvore nao e vazia
	{
		return 0;
	}

	if (r->info > value) return arv_Busca(r->esq , value); // se a informação da raiz entra no nodo da esquerda
	else if (r->info < value) return arv_Busca(r->dir , value); // se a imformação da raiz entra no nodo da direita
	else if (r->info == value) return r->index;// se for igual ja achou
	else return 0; // se nao nao existe na arvore
}
 
void Arv::arv_Cont_Leaf(Arv* r, int* cont) // conta as folhas da arvore
{

	if(arv_Vazia(r)) //testa se a arvore nao e vazia 
	{
		cout << "Node Empty !" <<endl;
		return;
	}
	else if(r->dir != NULL && r->esq != NULL) // se os dois lados da raiz nao forem nulos entra nos dois nodos recurcivamente
	{
		r->arv_Cont_Leaf(r->dir ,cont);
		r->arv_Cont_Leaf(r->esq , cont);
	}
	else if(r->esq != NULL)  // se so o nodo da esquerda nao for nulo entra no da esquerda
	{
		r->arv_Cont_Leaf(r->esq , cont);
	}
	else if(r->dir != NULL) // se so o nodo da direita nao for nulo entra no da direita
	{
		r->arv_Cont_Leaf(r->dir , cont);
	}
	*cont = *cont + 1; // acumula o numero de folhas 
}

Arv* Arv::arv_Retira(Arv* r, int v) // função de retirar um nodo
{
	if(r == NULL) return NULL; // testa se a arvore nao e vazia 
	else if (r->info > v)  // se o elemento a ser excluido for menor que a raiz entra na esquerda recurcivamente
	{
		r->esq = arv_Retira(r->esq , v); 
	}
	else if (r->info < v) // se for maior entra na direita
		r->dir = arv_Retira(r->dir , v);
	else
	{
		if (r->esq == NULL && r->dir == NULL) //se os dois forem nulos apaga o nodo
		{
			free (r);
			r = NULL;
		}
		else if (r->esq == NULL) // se so a esquerda for nula usa um auxiliar e apaga o nodo
		{
			Arv* t = r;
			r = r->dir;
			free (t);
		}
		else if (r->dir == NULL) // faz o mesmo do de cima 
		{
			Arv* t = r;
			r = r->esq;
			free (t);
		}
		else // essa parte nao entendi direito, essa função foi compiada em aula
		{
			Arv* pai = r;
			Arv* f = r->esq;
			while (f->dir != NULL){
				pai = f;
				f = f->dir;
			}
			r->info = f->info;
			f->info = v;
			r->esq = arv_Retira(r->esq, v);
		}
	}
	return r;
}

void Arv::arv_Converse_Vect(Arv* a, std::deque<int> *vet) // função para imprimir a arvore
{
	if(a != NULL) // testa se arvore nao e vazia
	{
		vet->push_front(a->info); //Salva o indice no grafo que este nodo adjacente se encontra
 
		if( a->esq != NULL)
		{
			arv_Converse_Vect(a->esq, vet);
		}	
		
		if( a->dir != NULL)
		{
			arv_Converse_Vect(a->dir, vet);
		}
		else return;
	}
}

int Arv::costNode(Arv* arv, int value)
{
	if(arv == NULL) // testa se a arvore nao e vazia
	{
		return 0;
	}

	if (arv->info > value) return costNode(arv->esq , value); // se a informação da raiz entra no nodo da esquerda
	else if (arv->info < value) return costNode(arv->dir , value); // se a imformação da raiz entra no nodo da direita
	else if (arv->info == value) return arv->cost;// se for igual ja achou retorna peso
	// else return 0; // se nao nao existe na arvore
}