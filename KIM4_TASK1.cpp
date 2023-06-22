//Дан файл с произвольным количеством строк. Найти слова, удовлетворяющие заданному свойству: слово начинается с заданной подстроки
//Показать, в каких строках эти слова содержатся

#include <iostream>
#include <map>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>

auto check = [](std::string word, std::string substring)
{
	return word.find(substring) == 0;
};

void task1(std::fstream& file, bool (*lambda)(std::string, std::string))
{
	std::multimap<std::string, int> dict;
	std::string substring;
	std::cin >> substring;
	std::string str;
	std::string word;
	int curr = 0;
	while (getline(file, str))
	{
		curr++;
		std::stringstream ss(str);
		while (ss >> word)
		{
			if (check(word, substring))
			{
				dict.insert({ word, curr });
			}
		}
	}
	for (auto i : dict)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

int main()
{
	std::fstream file1("Text_1.txt");
	task1(file1, check);
}
