//В файле записан набор из нескольких костей домино. Построить из них цепочку максимальной длины

#include <iostream>
#include <fstream>
#include <vector>
 
void backtrack(std::vector <std::pair<int, int>>& dominoes, std::vector <std::pair<int, int>>& best, std::vector <std::pair<int, int>>& current, std::vector<bool>& used)
{
	if (current.size() > best.size() && used.back() == true)
	{
		best = current;
	}
	else
	{
		for (int i = 0; i < dominoes.size(); i++)
		{
			if (!used[i])
			{
				std::pair<int, int> domino = dominoes[i];
				if (current.empty())
				{
					current.push_back(domino);
					used[i] = true;
					backtrack(dominoes, best, current, used);
					current.pop_back();
					used[i] = false;
				}
				else if (current[0].first == domino.first)
				{
					std::swap(domino.first, domino.second);
					current.insert(current.begin(), domino);
					used[i] = true;
					backtrack(dominoes, best, current, used);
					current.erase(current.begin());
					used[i] = false;
				}
				else if (current[0].first == domino.second)
				{
					current.insert(current.begin(), domino);
					used[i] = true;
					backtrack(dominoes, best, current, used);
					current.erase(current.begin());
					used[i] = false;
				}
				else if (current.back().second == domino.first)
				{
					current.push_back(domino);
					used[i] = true;
					backtrack(dominoes, best, current, used);
					current.pop_back();
					used[i] = false;
				}
				else if (current.back().second == domino.second)
				{
					std::swap(domino.first, domino.second);
					current.push_back(domino);
					used[i] = true;
					backtrack(dominoes, best, current, used);
					current.pop_back();
					used[i] = false;
				}
			}
		}
	}
}
 
int main()
{
	std::fstream file("Domino_3.txt");
	std::vector <std::pair<int, int>> dominoes;
	while (!file.eof())
	{
		std::pair<int, int> tmp;
		file >> tmp.first >> tmp.second;
		dominoes.push_back(tmp);
	}
	std::vector<std::pair<int, int>> best, current;
	std::vector<bool> used(dominoes.size(), false);
	backtrack(dominoes, best, current, used);
	for (auto x : best)
	{
		std::cout << x.first << ' ' << x.second << std::endl;
	}
	std::cout << best.size();
}	
