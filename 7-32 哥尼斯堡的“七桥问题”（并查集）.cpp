/*7-32 哥尼斯堡的“七桥问题” (25 分)
哥尼斯堡是位于普累格河上的一座城市，它包含两个岛屿及连接它们的七座桥。

可否走过这样的七座桥，而且每桥只走过一次？瑞士数学家欧拉(Leonhard Euler，1707?1783)最终解决了这个问题，并由此创立了拓扑学。

这个问题如今可以描述为判断欧拉回路是否存在的问题。欧拉回路是指不令笔离开纸面，可画过图中每条边仅一次，且可以回到起点的一条回路。现给定一个无向图，问是否存在欧拉回路？

输入格式:
输入第一行给出两个正整数，分别是节点数N (1≤N≤1000)和边数M；随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个节点的编号（节点从1到N编号）。

输出格式:
若欧拉回路存在则输出1，否则输出0。

输入样例1:
6 10
1 2
2 3
3 1
4 5
5 6
6 4
1 4
1 6
3 4
3 6

输出样例1:
1

输入样例2:
5 8
1 2
1 3
2 3
2 4
2 5
5 3
5 4
3 4
输出样例2:
0*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    int n, m, a, b;
    cin >> n >> m;
    vector<size_t> cnt(n, 0), size(n, 0);
    vector<int> root(n);
    iota(root.begin(), root.end(), 0);
    //通过并查集判断图是否连通
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        a -= 1;
        b -= 1;
        cnt[a] += 1;
        cnt[b] += 1;
		//比较a所在集团与b所在集团的势力大小
        int max = (size[root[a]] >= size[root[b]]) ? a : b, min = (size[root[a]] >= size[root[b]]) ? b : a;
        root[root[min]] = root[max]; //如果root[min] = root[max]则会导致min的首领不会归于更大的首领
        size[root[max]] += size[root[min]] + 1;
    }
    int king = -1;
    for (auto& k: root) //之所以可以用引用，是因为这是一种更新不会使root的含义发生改变而且可以提高后续遍历的效率
    {
        while (root[k] != k)
            k = root[k];
        if (king == -1)
            king = k;
        else if (k != king)
        {
            cout << 0;
            exit(0);
        }
    }
    //若图连通则判断每个点的度是否为偶数
    bool flag = true;
    for (auto &k: cnt)
        if (k % 2 == 1)
        {
            flag = false;
            break;
        }
    if (flag)
        cout << 1;
    else
        cout << 0;
}