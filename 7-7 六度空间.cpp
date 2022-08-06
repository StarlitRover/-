/*7-7 六度空间 (30 分)
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10 
3
 ，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
结尾无空行
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
结尾无空行*/

//通过邻接矩阵求解路径长度≤6的连通矩阵
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class graph
{
private:
    int length;
    vector<vector<bool>> path;
public:
    graph()
    {};

    graph(int s)
    {
        length = s;
        path = vector<vector<bool>>(s, vector<bool>(s, false));
    };

    inline void AppendPath(int x, int y);

    vector<vector<bool>> inCircle(int r);
};

inline void graph::AppendPath(int x, int y)
{
    path[x - 1][y - 1] = path[y - 1][x - 1] = true;
}

vector<vector<bool>> graph::inCircle(int r)
{
    vector<vector<bool>> otc = path, pre = path, tmp;
    for (int i = 1; i < r; ++i) //!四重循环导致遇到较大测试样例时运行超时
    {
        tmp = vector<vector<bool>>(length, vector<bool>(length, false));
        for (int j = 0; j < length; ++j)
            for (int k = 0; k < length; ++k)
                for (int s = 0; s < length; ++s)
                    if (pre[j][s] && path[s][k])
                    {
                        tmp[j][k] = true;
                        continue;
                    }
        for (int w = 0; w < length; ++w)
            for (int v = 0; v < length; ++v)
                otc[w][v] = otc[w][v] || tmp[w][v];
        pre = tmp;
    }
    return otc;
}

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m);
    int x, y;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        g.AppendPath(x, y);
    }
    vector<vector<bool>> otc = g.inCircle(6);
    for (int i = 0; i < m; ++i)
    {
        cout << i + 1 << ": ";
        cout << fixed << setprecision(2) << 100.0 * count(begin(otc[i]), end(otc[i]), true) / m << "%" << endl;
    }
}


//通过递归思想：长度为n的节点寻找到长度为n+1的节点
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

class graph
{
private:
    int length;
    vector<vector<bool>> path;
public:
    graph()
    {};

    graph(int s)
    {
        length = s;
        path = vector<vector<bool>>(s, vector<bool>(s, false));
    };

    inline void AppendPath(int x, int y);

    inline bool isLinked(int x, int y);
};

inline void graph::AppendPath(int x, int y)
{
    path[x - 1][y - 1] = path[y - 1][x - 1] = true;
}

inline bool graph::isLinked(int x, int y)
{
    return path[x][y];
}

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m);
    int x, y;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        g.AppendPath(x, y);
    }
    vector<vector<bool>> otc(m, vector<bool>(m, false));
    for (int i = 0; i < m; ++i)
    {
        set<int> pre, tmp;
        pre.insert(i);
        int cnt = 0;
        while (!pre.empty() && cnt < 6)
        {
            tmp.clear();
            for (auto k:pre)
                for (int j = 0; j < m; ++j)
                {
                    if (g.isLinked(k, j) && !otc[i][j])  //!otc[i][j]这一判断可以减少很多重复查找(测试点4的关键)
                    {
                        tmp.insert(j);
                        otc[i][j] = true;
                    }
                }
            pre = tmp;
            ++cnt;
        }
    }
    for (int i = 0; i < m; ++i)
    {
        cout << i + 1 << ": ";
        cout << fixed << setprecision(2) << 100.0 * count(begin(otc[i]), end(otc[i]), true) / m << "%" << endl;
    }
}