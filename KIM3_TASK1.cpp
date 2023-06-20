// Дан файл, состоящий из нескольких строк. Каждая строка содержит слова,
// разделенные любым количесвтом пробелов. Разработать функцию для поиска слов,
// которые есть во всех строках файла и обладают заданным свойством. Функция должна 
// принимать лямбду для проверки нужного свойства слова. Привести пример вызова функции
// для свойства: оканчиваются заданной буквой
 
#include <iostream>
#include <functional>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <Windows.h>
 
auto lambda = [](std::string word, char letter)
{
	return word[word.length() - 1] == letter;
};
 
void task(std::ifstream& file, bool (*lambda)(std::string, char), char letter)
{
	std::map<std::string, int> dict;
	std::string str;
	std::string word;
	int count = 0;
	while (getline(file, str))
	{
		++count;
		std::istringstream iss(str);
		while (iss >> word)
		{
			if (lambda(word, letter))
			{
				if (dict.find(word) == dict.end())
				{
					dict.insert({ word, 1 });
				}
				else
				{
					++dict.find(word)->second;
				}
			}
		}
	}
	for (auto& i : dict)
	{
		if (i.second == count)
			std::cout << i.first << std::endl;
	}
}
 
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ifstream file("input.txt");
	char letter;
	std::cin >> letter;
 
	task(file, lambda, letter);
}
