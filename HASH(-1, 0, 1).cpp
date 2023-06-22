//Внутреннее решение коллизии с таблицей (-1, 0, 1). add, find, remove

#include <iostream>
#include <Windows.h>
#include "HashTable.h"
#include <string>
#include <fstream>
 
void find(HashTable_2& table, std::string key)
{
	int hash = table.hash(key);
	std::vector<CELL>::iterator It = std::find_if(table.data.begin(), table.data.end(), [&key](CELL elem)-> bool {return elem.used == 1 && elem.elem.key == key; });
	if (It != table.data.end())
	{
		ELEM result = (*It).elem;
		std::cout << result.key << " " << result.other << "\n";
	}
	else
		std::cout << "Not found";
}
 
void remove(HashTable_2& table, std::string key)
{
	int hash = table.hash(key);
	std::vector<CELL>::iterator It = std::find_if(table.data.begin(), table.data.end(), [&key](CELL elem)->bool {return elem.used == 1 && elem.elem.key == key; });
	if (It != table.data.end())
	{
		(*It).used = -1;
		std::cout << "Deleted";
	}
	else
		std::cout << "Not deleted";
}
 
void add(HashTable_2& table, ELEM elem)
{
	int hash = table.hash(elem.key);
	std::vector<CELL>::iterator It = std::find_if(table.data.begin(), table.data.end(), [&elem](CELL el)->bool {return el.used == 1 && el.elem.key == elem.key; });
	bool added = false;
	if (It == table.data.end())
	{
		if (table.data[hash].used != 1)
		{
			table.data[hash].elem = elem;
			table.data[hash].used = 1;
			added = true;
		}
		else
		{
 
			int cur = hash + 1;
			while (cur != hash && !added)
			{
				if (table.data[cur].used != 1)
				{
					table.data[cur].elem = elem;
					table.data[cur].used = 1;
					added = true;
				}
				cur = (cur + 1) % table.size;
			}
		}
	}
	if (added)
	{
		std::cout << "Added";
	}
	else
	{
		std::cout << "Not added";
	}
}
 
int main()
{
	HashTable_2 table;
	table.print();
	//std::string key;
	//std::cin >> key;
	ELEM elem;
	elem.key = "faf";
	elem.other = 123;
	add(table, elem);
	table.print();
}
