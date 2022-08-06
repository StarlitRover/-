/*7-36 社交网络图中结点的“重要性”计算 (30 分)
在社交网络中，个人或单位（结点）之间通过某些关系（边）联系起来。他们受到这些关系的影响，这种影响可以理解为网络中相互连接的结点之间蔓延的一种相互作用，可以增强也可以减弱。而结点根据其所处的位置不同，其在网络中体现的重要性也不尽相同。

“紧密度中心性”是用来衡量一个结点到达其它结点的“快慢”的指标，即一个有较高中心性的结点比有较低中心性的结点能够更快地（平均意义下）到达网络中的其它结点，因而在该网络的传播过程中有更重要的价值。

对于非连通图，所有结点的紧密度中心性都是0。

给定一个无权的无向图以及其中的一组结点，计算这组结点中每个结点的紧密度中心性。

输入格式:
输入第一行给出两个正整数N和M，其中N（≤10^4）是图中结点个数，顺便假设结点从1到N编号；M（≤10^5）是边的条数。随后的M行中，每行给出一条边的信息，即该边连接的两个结点编号，中间用空格分隔。最后一行给出需要计算紧密度中心性的这组结点的个数K（≤100）以及K个结点编号，用空格分隔。

输出格式:
按照Cc(i)=x.xx的格式输出K个给定结点的紧密度中心性，每个输出占一行，结果保留到小数点后2位。

输入样例:
9 14
1 2
1 3
1 4
2 3
3 4
4 5
4 6
5 6
5 7
5 8
6 7
6 8
7 8
7 9
3 3 4 9

输出样例:
Cc(3)=0.47
Cc(4)=0.62
Cc(9)=0.35
*/
#include <iostream>
#include <vector>
#include <algorithm>

#define INFINITE INT32_MAX/2 //不能直接用INT32_MAX，会溢出
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, INFINITE));
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        dist[a - 1][b - 1] = dist[b - 1][a - 1] = 1;
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[j][i] = dist[i][j] = dist[i][k] + dist[k][j];
    int r, k;
    double cc;
    cin >> r;
    if (find(dist[0].begin(), dist[0].end(), INFINITE) != dist[0].end()) //若dist矩阵中依旧存在INFINITE则说明图不连通
        for (int i = 0; i < r; ++i)
        {
            cin >> k;
            printf("Cc(%d)=0.00\n", k);
        }
    else
        for (int i = 0; i < r; ++i)
        {
            cin >> k;
            int add = 0;
            for (int j = 0; j < n; ++j)
                add += dist[j][k - 1];
            cc = 1.0 * (n - 1) / add;
            printf("Cc(%d)=%.2f\n", k, cc);
        }
}
/*Floyd算法正确性的证明思路:
	考虑任意两点之间的最短路径，从路径内部（不包含两端）编号最小的节点开始，会将其路径周围两个节点的最短距离算出，于是将该点剔除连接与其相邻的两点,继续考虑其中编号最小的节点,然后不断迭代最终必然只剩下起点和终点.
	In that sense,every shortest path between any two points will be calculated in Floyd algorithm.