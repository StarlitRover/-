/*7-10 ��·���ͨ (30 ��)
���д�����·��ͳ�����ݱ��У��г����п��ܽ���ɱ�׼��·����������·�ĳɱ�����ʹÿ�����䶼�й�·��ͨ����Ҫ����ͳɱ���

�����ʽ:
�������ݰ���������Ŀ������N����1000���ͺ�ѡ��·��ĿM����3N��������M�ж�ӦM����·��ÿ�и���3�����������ֱ��Ǹ�����·ֱ����ͨ����������ı���Լ��õ�·�Ľ���Ԥ��ɱ���Ϊ������������1��N��š�

�����ʽ:
������ͨ��Ҫ����ͳɱ�������������ݲ����Ա�֤��ͨ�������?1����ʾ��Ҫ������๫·��

��������:
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

�������:
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
    vector<vector<int>> adjacency;  //�״γ����ڽӱ�ṹ(��ʡ�ռ�)
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
    vector<bool> flag(m, false); //��¼������Ľڵ�
    flag[g.cost[g.min_index].x] = flag[g.cost[g.min_index].y] = true; //����̱߿�ʼ
    allCost += g.cost[g.min_index].val;
    set<int> edges; //�洢������ڵ����ⲿ��֮��ı�
    for (auto k: g.adjacency[g.cost[g.min_index].x])
        edges.insert(k);
    for (auto k: g.adjacency[g.cost[g.min_index].y])
        edges.insert(k);
    edges.erase(g.min_index);
    for (int i = 0; i < m - 2 && !edges.empty(); ++i) //���������m-2�Σ�����ͨͼ��edges����
    {
        int min = INT32_MAX, index = -1;
        for (auto k: edges) //ÿ���ҳ�edges�е���С��
            if (g.cost[k].val < min)
            {
                min = g.cost[k].val;
                index = k;
            }
        allCost += g.cost[index].val;
		//�ҳ���С���л�δ������Ľڵ㼴Ϊ������ĵ�
        int new_index = flag[g.cost[index].x] ? g.cost[index].y : g.cost[index].x; 
        flag[new_index] = true;
        for (auto p: g.adjacency[new_index]) //ɾ��edges�������ڵ����ڲ��ڵ�ı�
            if (flag[g.cost[p].x] && flag[g.cost[p].y])
                edges.erase(p);
            else
                edges.insert(p); //ͬʱ��������ڵ����ⲿ�ڵ�ı�
    }
    cout << (find(flag.begin(), flag.end(), false) == flag.end() ? allCost : -1);
}