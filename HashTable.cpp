#include "HashTable.h"
#include <iostream>
#include <unordered_map>
#include <math.h>

using namespace std;

void HashTable::put(const void* key, const void* value) //Insere elemento na hash
{
	htmap[key] = value;
}

bool HashTable::get(const void* key) //Vê tal elemento ja está na hash
{
	std::unordered_map<const void*, const void*>::const_iterator temp = htmap.find(key);

	if(temp == htmap.end()) return false;
	else return true;
}

int HashTable::createKey(int vert, int adj) //Cria chave pra hash
{
	int hashkey=0;
	
	hashkey += pow( 3 , 2 - 0) * vert;
	hashkey += pow( 5 , 2 - 1) * adj;

	return hashkey;
}

void HashTable::clean() //limpa a hash
{
	htmap.clear();
}