/*7-9 旅游规划 (25 分)
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N?1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
结尾无空行
输出样例:
3 40
结尾无空行*/

#include <iostream>
#include <vector>

#define INFINITE 250000

using namespace std;

class graph
{
private:
    vector<vector<int>> dist, cost;
public:
    graph(int m, int n)
    {
        dist = vector<vector<int>>(m, vector<int>(m, INFINITE));
        cost = vector<vector<int>>(m, vector<int>(m, INFINITE));
        for (int i = 0; i < m; ++i)
            dist[i][i] = cost[i][i] = 0;
        int x, y, d, c;
        for (int i = 0; i < n; ++i)
        {
            cin >> x >> y >> d >> c;
            dist[x][y] = dist[y][x] = d;
            cost[x][y] = cost[y][x] = c;
        }
    }

    inline int getDist(int x, int y)
    {
        return dist[x][y];
    }

    inline int getCost(int x, int y)
    {
        return cost[x][y];
    }
};

int main()
{
    int m, n, start, dest;
    cin >> m >> n >> start >> dest;
    graph g(m, n);
    vector<int> minDist(m, INFINITE), allCost(m, INFINITE);
    for (int i = 0; i < m; ++i)
    {
        minDist[i] = g.getDist(start, i);
        allCost[i] = g.getCost(start, i);
    }
    vector<bool> flag(m, false);
    flag[start] = true;
    while (!flag[dest])
    {
        int min = INFINITE - 1, index = -1;
        for (int i = 0; i < m; ++i)
        {
            if (flag[i]) continue;
            if (minDist[i] < min || minDist[i] == min && allCost[i] < allCost[index])
            {
                min = minDist[i];
                index = i;
            }
        }
        flag[index] = true;
        for (int i = 0; i < m; ++i)
        {
            if (flag[i]) continue;
            if (g.getDist(index, i) + min < minDist[i] ||
                g.getDist(index, i) + min == minDist[i] && g.getCost(index, i) + allCost[index] < allCost[i])
            {
                minDist[i] = g.getDist(index, i) + min;
                allCost[i] = g.getCost(index, i) + allCost[index];
            }
        }
    }
    cout << minDist[dest] << " " << allCost[dest];
}
//本题的主要思想是将Dijkstra中的路径长度比较转化成了先比较路径后比较费用，本质是一样的，只是改变了比较的方法.(Dijkstra算法是更为一般的广度优先搜索算法)