//КИМ 3 
//4. Дан одномерный массив целых чисел. Проверить, что количество четных элементов кратно трем. 
//Создание потоков организовать с использованием класса thread. Потоки взаимодействующие. Взаимодействие организовать через объект ядра "Событие"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <stack>

//const
struct Piece
{
	int* begin, * end;
	Piece(int* begin = nullptr, int* end = nullptr)
	{
		this->begin = begin;
		this->end = end;
	}
};

//const
class SafeStack
{
private:
	std::stack<Piece> stack;
	HANDLE HEvent;

public:
	SafeStack()
	{
		HEvent = CreateEvent(nullptr, false, true, nullptr);
	}
	void push(Piece elem)
	{
		if (WaitForSingleObject(HEvent, INFINITE) == WAIT_OBJECT_0)
		{
			try
			{
				stack.push(elem);
			}
			catch (...)
			{
				SetEvent(HEvent);
			}
			SetEvent(HEvent);
		}
	}
	bool try_pop(Piece& elem)
	{
		bool result = false;
		if (WaitForSingleObject(HEvent, INFINITE) == WAIT_OBJECT_0)
		{
			try
			{
				if (!stack.empty())
				{
					result = true;
					elem = stack.top();
					stack.pop();
				}
			}
			catch (...)
			{
				SetEvent(HEvent);
			}
			SetEvent(HEvent);
		}
		return result;
	}
	bool is_empty()
	{
		return stack.empty();
	}
	~SafeStack()
	{
		CloseHandle(HEvent);
	}
};

const size_t NTHREAD = 4;
size_t n = 0;
const int piece_size = 5;
volatile long res_count;
SafeStack stack;

//cosnt
int count_num(Piece piece)
{
	int local_count = 0;
	for (int* i = piece.begin; i != piece.end; i++)
	{
		if (*i % 2 == 0) //меняется только это условие в зависимости от задачи
		{
			local_count++;
		}
	}
	return local_count;
}

//const
void thread_task()
{
	Piece piece;
	while (!stack.is_empty())
	{
		if (stack.try_pop(piece))
		{
			_InterlockedExchangeAdd(&res_count, count_num(piece));
		}
	}
}

//const
void par_count_num(int* arr)
{
	std::thread TH[NTHREAD - 1];
	for (int i = 0; i < n / piece_size; i++)
	{
		Piece piece(arr + i * piece_size, arr + (i + 1) * piece_size);
		stack.push(piece);
	}

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::thread(thread_task);
	}

	Piece piece(arr + n - n % piece_size, arr + n);
	_InterlockedExchangeAdd(&res_count, count_num(piece));

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
	if (res_count % 3 == 0)
	{
		std::cout << "Yes" << std::endl;
	}
	else
	{
		std::cout << "No" << std::endl;
	}
}
