//КИМ 3 
//4. Дан одномерный массив целых чисел. Проверить, что количество четных элементов кратно трем. 
//Создание потоков организовать с использованием класса thread. Потоки взаимодействующие. Взаимодействие организовать через объект ядра "Событие"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <process.h>

const size_t NTHREAD = 4;
size_t n = 0;
volatile long res_count;
CRITICAL_SECTION cs;

struct elem
{
	int* arr;
	size_t beg, end;
};

//cosnt
unsigned __stdcall count_num(void* arr)
{
	elem* inf = (elem*)arr;
	int local_count = 0;
	for (int i = inf->beg; i != inf->end; i++)
	{
		if (inf->arr[i] % 2 == 0) //меняется только это условие в зависимости от задачи
		{
			local_count++;
		}
	}
	EnterCriticalSection(&cs);
	try
	{
		res_count += local_count;
	}
	catch (...)
	{
		LeaveCriticalSection(&cs);
	}
	LeaveCriticalSection(&cs);
	_endthreadex(0);
	return 0;
}

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
	EnterCriticalSection(&cs);
	try
	{
		res_count += local_count;
	}
	catch (...)
	{
		LeaveCriticalSection(&cs);
	}
	LeaveCriticalSection(&cs);
}

//const
void par_count_num(int* arr)
{
	HANDLE TH[NTHREAD - 1];
	unsigned THID[NTHREAD - 1];
	elem inf[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		inf[i].arr = arr;
		inf[i].beg = i * size;
		if (i == NTHREAD - 1)
		{
			inf[i].end = n;
		}
		else
		{
			inf[i].end = (i + 1) * size;
		}
		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &count_num, &inf[i], 0, nullptr);
	}

	count_num(arr, (NTHREAD - 1) * size, n);
	WaitForMultipleObjects(NTHREAD - 1, TH, true, INFINITE);

	for (int i = 0; i < NTHREAD - 1; i++)
	{
		CloseHandle(TH[i]);
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
	InitializeCriticalSection(&cs);
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
