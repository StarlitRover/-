/*7-10 公路村村通 (30 分)
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出?1，表示需要建设更多公路。

输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3

输出样例:
12
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class edge
{
public:
    int val;
    int x;
    int y;

    edge()
    {};

    edge(int m, int n, int cost) : x(m - 1), y(n - 1), val(cost)
    {};
};

class graph
{
public:
    vector<edge> cost;
    vector<vector<int>> adjacency;  //首次尝试邻接表结构(节省空间)
    int min_index;

    graph(int m, int n)
    {
        adjacency = vector<vector<int>>(m);
        int x, y, c, min = INT32_MAX;
        for (int i = 0; i < n; ++i)
        {
            cin >> x >> y >> c;
            cost.emplace_back(edge(x, y, c));
            adjacency[x - 1].push_back(i);
            adjacency[y - 1].push_back(i);
            if (c < min)
            {
                min = c;
                min_index = i;
            }
        }
    }
};

int main()
{
    int m, n, allCost = 0;
    cin >> m >> n;
    graph g(m, n);
    vector<bool> flag(m, false); //记录已纳入的节点
    flag[g.cost[g.min_index].x] = flag[g.cost[g.min_index].y] = true; //从最短边开始
    allCost += g.cost[g.min_index].val;
    set<int> edges; //存储已纳入节点与外部点之间的边
    for (auto k: g.adjacency[g.cost[g.min_index].x])
        edges.insert(k);
    for (auto k: g.adjacency[g.cost[g.min_index].y])
        edges.insert(k);
    edges.erase(g.min_index);
    for (int i = 0; i < m - 2 && !edges.empty(); ++i) //正常情况：m-2次；不连通图：edges会变空
    {
        int min = INT32_MAX, index = -1;
        for (auto k: edges) //每次找出edges中的最小边
            if (g.cost[k].val < min)
            {
                min = g.cost[k].val;
                index = k;
            }
        allCost += g.cost[index].val;
		//找出最小边中还未被纳入的节点即为新纳入的点
        int new_index = flag[g.cost[index].x] ? g.cost[index].y : g.cost[index].x; 
        flag[new_index] = true;
        for (auto p: g.adjacency[new_index]) //删除edges中新增节点与内部节点的边
            if (flag[g.cost[p].x] && flag[g.cost[p].y])
                edges.erase(p);
            else
                edges.insert(p); //同时添加新增节点与外部节点的边
    }
    cout << (find(flag.begin(), flag.end(), false) == flag.end() ? allCost : -1);
}