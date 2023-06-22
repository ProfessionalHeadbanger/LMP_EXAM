// Описать функцию, которая принимает хеш-таблицу (-1, 0, 1),
// ключ (string) и осуществляет поиск информации по ключу
#include <iostream>
#include <Windows.h>
#include "HashTable.h"
#include <string>
#include <fstream>
 
using THT = std::vector<CELL>;
using Iterator = THT::iterator;
 
void find1(HashTable_2& table, std::string key)
{
	int hash = table.hash(key);
	Iterator It = std::find_if(table.data.begin(), table.data.end(), [&key](CELL elem)-> bool {return elem.used == 1 && elem.elem.key == key; });
	ELEM result = (*It).elem;
	std::cout << result.key << result.other;
}
 
void find2(HashTable_2& table, std::string key)
{
	int hash = table.hash(key);
	if (table.data[hash].elem.key == key)
	{
		std::cout << hash << table.data[hash].elem.key << ' ' << table.data[hash].elem.other << ' ' << std::endl;
	}
	else 
	{
		for (int i = hash + 1; i < 150; i++)
		{
			if (table.data[hash].elem.key == key)
			{
				std::cout << hash << table.data[hash].elem.key << ' ' << table.data[hash].elem.other << ' ' << std::endl;
			}
		}
	}
}
 
int main()
{
	HashTable_2 table;
	std::string key;
	std::cin >> key;
	find2(table, key);
}
