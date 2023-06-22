//КИМ 3 
//4. Дан одномерный массив целых чисел. Проверить, что количество четных элементов кратно трем. 
//Создание потоков организовать с использованием класса thread. Потоки взаимодействующие. Взаимодействие организовать через объект ядра "Событие"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <future>
#include <mutex>

const size_t NTHREAD = 4;
size_t n = 0;
volatile long res_count;
std::mutex mute;

void count_num(int* arr, int beg, int end)
{
	int local_count = 0;
	for (int i = beg; i != end; i++)
	{
		if (arr[i] % 2 == 0) //меняется только это условие в зависимости от задачи
		{
			local_count++;
		}
	}

	mute.lock();
	try
	{
		res_count += local_count;
	}
	catch (...)
	{
		mute.unlock();
	}
	mute.unlock();
}

//const
void par_count_num(int* arr)
{
	std::future<void> TH[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::async(std::launch::async, count_num, arr, i * size, (i + 1) * size);
	}

	count_num(arr, (NTHREAD - 1) * size, n);

	for (int i = 0; i < NTHREAD - 1; i++)
	{
		TH[i].get();
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
	if (res_count % 3 == 0)
	{
		std::cout << "Yes" << std::endl;
	}
	else
	{
		std::cout << "No" << std::endl;
	}
}
