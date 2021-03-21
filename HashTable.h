#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <unordered_map>

/*
*	Autor: Jian Furquim 161152063
*	Tema: Caicheiro Viajante
*	Descrição: Class para Hash auxiliar no algoritimo
*	Professor: Marcelo Luizelli
*/

using namespace std;

class HashTable  //class Tabela hash pra ser usado nas buscas
{
	std::unordered_map<const void*, const void*> htmap;
	
 public:
	void put(const void* key, const void* value); //Insere elemento na hash
	bool get(const void* key);//Vê tal elemento ja está na hash
	int createKey(int vert, int adj); //cria chave para a hash
	void clean(); //limpa a hash
};
#endif