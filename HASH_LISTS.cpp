//Внешнее разрешение коллизии. Все варианты задачи (add, find, remove)

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include "HashTable_3.h"

void remove(HashTable_3& ht, std::string key)
{
	int index = ht.hash(key);
	std::list<ELEM>::iterator it = std::find_if(ht.data[index].begin(), ht.data[index].end(), [&key](ELEM elem)->bool {return elem.key == key; });
	if (it != ht.data[index].end())
	{
		ht.data[index].erase(it);
		std::cout << "Deleted" << std::endl;
	}
	else
	{
		std::cout << "Not deleted" << std::endl;
	}
}

void find(HashTable_3& ht, std::string key)
{
	int index = ht.hash(key);
	std::list<ELEM>::iterator it = std::find_if(ht.data[index].begin(), ht.data[index].end(), [&key](ELEM elem)->bool {return elem.key == key; });
	if (it != ht.data[index].end())
	{
		std::cout << (*it).key << " " << (*it).other << std::endl;
	}
	else
	{
		std::cout << "Not found" << std::endl;
	}
}

void add(HashTable_3& ht, ELEM elem)
{
	int index = ht.hash(elem.key);
	if (std::find_if(ht.data[index].begin(), ht.data[index].end(), [&elem](ELEM el)->bool {return el.key == elem.key; }) == ht.data[index].end())
	{
		ht.data[index].push_back(elem);
		std::cout << "Added" << std::endl;
	}
	else
	{
		std::cout << "Not added" << std::endl;
	}
}

int main()
{
	HashTable_3 ht;
	ht.print();
	ELEM elem;
	std::cin >> elem.key >> elem.other;
	//std::string key;
	//std::cin >> key;
	//find(ht, key);
	add(ht, elem);
	ht.print();
}
