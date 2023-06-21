//Описать потокобезопасный контейнер "Очередь", в качестве объекта синхронизации использовать событие. 
//Продемонстрировать работу контейнера в задаче "Производитель - Потребитель"

#include <iostream>
#include <Windows.h>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

const int piece_size = 5;

//const
struct Piece
{
	int arr[piece_size];
	Piece() 
	{
		for (int i = 0; i < piece_size; i++)
		{
			arr[i] = 0;
		}
	}
	Piece(const Piece& p)
	{
		for (int i = 0; i < piece_size; i++)
		{
			this->arr[i] = p.arr[i];
		}
	}
	Piece& operator=(const Piece& p)
	{
		if (this != &p)
		{
			for (int i = 0; i < piece_size; i++)
			{
				this->arr[i] = p.arr[i];
			}
		}
		return *this;
	}
	friend std::ostream& operator<< (std::ostream& out, const Piece p)
	{
		for (int i = 0; i < piece_size; i++)
		{
			out << p.arr[i] << " ";
		}
		out << '\n';
		return out;
	}
};

//const
class SafeQueue
{
private:
	std::queue<Piece> queue;
	CRITICAL_SECTION cs;
public:
	SafeQueue()
	{
		InitializeCriticalSection(&cs);
	}
	void push(Piece elem)
	{
		EnterCriticalSection(&cs);
		try
		{
			queue.push(elem);
		}
		catch (...)
		{
			LeaveCriticalSection(&cs);
		}
		LeaveCriticalSection(&cs);
	}
	bool try_pop(Piece& elem)
	{
		bool result = false;
		EnterCriticalSection(&cs);
		try
		{
			if (!queue.empty())
			{
				result = true;
				elem = queue.front();
				std::cout << elem;
				queue.pop();
			}
		}
		catch (...)
		{
			LeaveCriticalSection(&cs);
		}
		LeaveCriticalSection(&cs);

		return result;
	}
	bool is_empty()
	{
		return queue.empty();
	}
	~SafeQueue()
	{
		DeleteCriticalSection(&cs);
	}
};

const size_t NTHREAD = 8;
volatile long res_count = 0;
SafeQueue queue;
volatile long vwp = 5;
volatile long vwc = 5;
std::condition_variable cv;
std::mutex mute;

//const
int count_num(Piece piece)
{
	int local_count = 0;
	for (int i = 0; i < piece_size; i++)
	{
		if (piece.arr[i] % 2 == 0) //условие зависит от задачи
		{
			local_count++;
		}
	}
	return local_count;
}

//const
void task_producer(int ID)
{
	while (_InterlockedExchangeAdd(&vwp, -1) > 0)
	{
		Piece tmp;
		for (int i = 0; i < piece_size; i++)
		{
			tmp.arr[i] = rand() % 100 + ID;
		}
		Sleep(2);
		queue.push(tmp);
		cv.notify_all();
	}
}

//const
void task_consumer(int ID)
{
	while (_InterlockedExchangeAdd(&vwc, -1) > 0)
	{
		Piece piece;
		std::unique_lock<std::mutex> locker(mute);
		cv.wait_for(locker, std::chrono::seconds(5), []() {return !queue.is_empty(); });
		if (queue.try_pop(piece))
		{
			Sleep(5);
			_InterlockedExchangeAdd(&res_count, count_num(piece));
		}
		else
		{
			_InterlockedExchangeAdd(&vwc, 1);
		}
	}
}

//const
void par_count_num()
{
	std::thread TH[NTHREAD];
	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i < NTHREAD - 4)
		{
			TH[i] = std::thread(task_producer, i);
		}
		else
		{
			TH[i] = std::thread(task_consumer, i);
		}
	}
	for (int i = 0; i < NTHREAD; i++)
	{
		TH[i].join();
	}
}

int main()
{
	par_count_num();
	std::cout << res_count << std::endl;
}
