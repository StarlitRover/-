/*7-9 ���ι滮 (25 ��)
����һ���Լ�����·��ͼ�����֪�����м�ĸ��ٹ�·���ȡ��Լ��ù�·Ҫ��ȡ�Ĺ�·�ѡ�������Ҫ��дһ�����򣬰���ǰ����ѯ���ο���һ�������غ�Ŀ�ĵ�֮������·���������������·��������̵ģ���ô��Ҫ�������˵�һ��·����

�����ʽ:
����˵�����������ݵĵ�1�и���4��������N��M��S��D������N��2��N��500���ǳ��еĸ�����˳�������еı��Ϊ0~(N?1)��M�Ǹ��ٹ�·��������S�ǳ����صĳ��б�ţ�D��Ŀ�ĵصĳ��б�š�����M���У�ÿ�и���һ�����ٹ�·����Ϣ���ֱ��ǣ�����1������2�����ٹ�·���ȡ��շѶ�м��ÿո�ֿ������־�Ϊ�����Ҳ�����500�����뱣֤��Ĵ��ڡ�

�����ʽ:
��һ�������·���ĳ��Ⱥ��շ��ܶ���ּ��Կո�ָ��������β�����ж���ո�

��������:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
��β�޿���
�������:
3 40
��β�޿���*/

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
//�������Ҫ˼���ǽ�Dijkstra�е�·�����ȱȽ�ת�������ȱȽ�·����ȽϷ��ã�������һ���ģ�ֻ�Ǹı��˱Ƚϵķ���.(Dijkstra�㷨�Ǹ�Ϊһ��Ĺ�����������㷨)