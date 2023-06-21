// Матрица 10х10. Определить максимальную денежную сумму из левой верхней
// ячейки в правую нижнюю и количество разных маршрутов
#include <iostream>
#include <fstream>
 
void task(int matrix[10][10], int& count, int& max_sum, int cur_x = 0, int cur_y = 0, int sum = 0)
{
	if (cur_x == 9 && cur_y == 9)
	{
		sum += matrix[cur_x][cur_y];
		if (sum == max_sum)
			++count;
		if (sum > max_sum)
		{
			max_sum = sum;
			count = 1;
		}
 
	}
	else
	{
		if (cur_x + 1 < 10)
			task(matrix, count, max_sum, cur_x + 1, cur_y, sum + matrix[cur_x][cur_y]);
		if (cur_y + 1 < 10)
			task(matrix, count, max_sum, cur_x, cur_y + 1, sum + matrix[cur_x][cur_y]);
	}
}
 
int main()
{
	std::ifstream file("input.txt");
	int matrix[10][10];
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			file >> matrix[i][j];
 
	int count = 0;
	int max_sum = 0;
	task(matrix, count, max_sum);
	std::cout << count << ' ' << max_sum;
}
