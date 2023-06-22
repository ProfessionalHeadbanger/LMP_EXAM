//Условие конкретно этой задачи: можно ли добраться из указанной точки в другую указанную точку

#include <iostream>
#include <cstring>
#include <fstream>
 
using namespace std;
 
class Cell
{
public:
    int x, y;
    Cell(int x = 0, int y = 0) : x(x), y(y) {}
};
 
int operator==(Cell a, Cell b)
{
    return (a.x == b.x) && (a.y == b.y);
}
 
#define MAX 40
int mas[MAX][MAX];
bool reached = false;
 
int CanGo(int i, int j, int n, int m)
{
    if ((i < 0) || (i >= n) || (j < 0) || (j >= m)) return 0;
    if (mas[i][j] == 1 || mas[i][j] == -1) return 0;
    return 1;
}
 
void bfs(Cell finish, Cell current, int n, int m)
{
    if (!reached)
    {
        int dx[] = { 1,-1,0,0 };
        int dy[] = { 0,0,1,-1 };
        Cell p = current;
        if (p == finish) reached = 1;
        else for (int k = 0; k < 4; k++)
        {
            int ii = p.x + dx[k]; // (x, y) -> (ii, jj)
            int jj = p.y + dy[k];
            if (CanGo(ii, jj, n, m))
            {
                p.x = ii;
                p.y = jj;
                mas[current.x][current.y] = -1;
                bfs(finish, p, n, m);
                mas[p.x][p.y] = -1;
                mas[current.x][current.y] = 0;
            }
        }
    }
}
 
int main()
{
    Cell start, finish, current;
    int n, m;
    ifstream input("input.txt");
    input >> n >> m >> start.x >> start.y >> finish.x >> finish.y;
    current = start;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            input >> mas[i][j];
        }
    }
    input.close();
 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mas[i][j] << " ";
        }
        cout << '\n';
    }
 
    bfs(finish, current, n, m);
 
    if (reached) cout << "Y";
    else cout << "N";
}
