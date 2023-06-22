//КИМ 3 
//4. Дан одномерный массив целых чисел. Проверить, что количество четных элементов кратно трем. 
//Создание потоков организовать с использованием класса thread. Потоки взаимодействующие. Взаимодействие организовать через объект ядра "Событие"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <atomic>

const size_t NTHREAD = 4;
size_t n = 0;
std::atomic<int> res_max = 0;

//cosnt
void count_num(int* arr, int beg, int end)
{
	int local_max = 0;
	for (int i = beg; i != end; i++)
	{
		if (arr[i] > local_max) //меняется только это условие в зависимости от задачи
		{
			local_max = arr[i];
		}
	}

	if (local_max > res_max)
	{
		res_max.store(local_max);
	}
}

//const
void par_count_num(int* arr)
{
	std::thread TH[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::thread(count_num, arr, i * size, (i + 1) * size);
	}

	count_num(arr, (NTHREAD - 1) * size, n);

	for (int i = 0; i < NTHREAD - 1; i++)
	{
		TH[i].join();
	}
}

int main()
{
	int* arr;
	std::fstream file("input.txt");
	file >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		file >> arr[i];
	}

	par_count_num(arr);
	std::cout << "Max: " << res_max << std::endl;
}
