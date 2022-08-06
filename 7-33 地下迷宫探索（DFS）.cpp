/*7-33 地下迷宫探索 (30 分)
地道战是在抗日战争时期，在华北平原上抗日军民利用地道打击日本侵略者的作战方式。地道网是房连房、街连街、村连村的地下工事。

我们在回顾前辈们艰苦卓绝的战争生活的同时，真心钦佩他们的聪明才智。在现在和平发展的年代，对多数人来说，探索地下通道或许只是一种娱乐或者益智的游戏。本实验案例以探索地下通道迷宫作为内容。

假设有一个地下通道迷宫，它的通道都是直的，而通道所有交叉点（包括通道的端点）上都有一盏灯和一个开关。请问你如何从某个起点开始在迷宫中点亮所有的灯并回到起点？

输入格式:
输入第一行给出三个正整数，分别表示地下迷宫的节点数N（1<N≤1000，表示通道所有交叉点和端点）、边数M（≤3000，表示通道数）和探索起始节点编号S（节点从1到N编号）。随后的M行对应M条边（通道），每行给出一对正整数，分别是该条边直接连通的两个节点的编号。

输出格式:
若可以点亮所有节点的灯，则输出从S开始并以S结束的包含所有节点的序列，序列中相邻的节点一定有边（通道）；否则虽然不能点亮所有节点的灯，但还是输出点亮部分灯的节点序列，最后输出0，此时表示迷宫不是连通图。

由于深度优先遍历的节点序列是不唯一的，为了使得输出具有唯一的结果，我们约定以节点小编号优先的次序访问（点灯）。在点亮所有可以点亮的灯后，以原路返回的方式回到起点。

输入样例1:
6 8 1
1 2
2 3
3 4
4 5
5 6
6 4
3 6
1 5

输出样例1:
1 2 3 4 5 6 5 4 3 2 1

输入样例2:
6 6 6
1 2
1 3
2 3
5 4
6 5
6 4
输出样例2:
6 4 5 4 6 0*/

#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

int main()
{
    int n, m, start, a, b, cnt = 1;
    cin >> n >> m >> start;
    vector<set<int>> graph(n);  //vector<set>既拥有了vector的对节点的直接访问功能又有了set自动排序功能
    vector<int> path;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a - 1].insert(b - 1);
        graph[b - 1].insert(a - 1);
    }
    vector<bool> isVisited(n, false);
    stack<int> track;           //记录原始不含环路径
    start -= 1;
    isVisited[start] = true;
    path.push_back(start);
    int flag;
    while (cnt != n)
    {
        flag = -1;
        for (auto &adj: graph[start])
        {
            if (isVisited[adj])
                continue;
            flag = adj;
            break;
        }
        if (flag != -1)
        {
            track.push(start);  //track记录的路径中不包含当前节点，这会方便回溯时的操作
            path.push_back(flag);
            isVisited[flag] = true;
            start = flag;
            cnt += 1;
        }
        else if (track.empty()) //已退回至起点
            break;
        else                    //进行回溯
        {
            start = track.top();
            track.pop();
            path.push_back(start);
        }
    }
    cout << path[0] + 1;
    for (int i = 1; i < path.size(); ++i)
        cout << " " << path[i] + 1;
    if (cnt == n)
        while (!track.empty())  //猛然惊觉栈track中所存储的路径便是不含环的原路
        {
            cout << " " << track.top() + 1;
            track.pop();
        }
    else
        cout << " 0";
}
/*题目中的“原路”事实上指的是没有不含环(最短)的原路*/

//递归调用版DFS  --from website
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
int adj[1005][1005];
int vis[10005];
int n;
int cnt;
int flag;

void dfs(int s)
{
    if (flag)
        cout << " ";
    flag = 1;
    cout << s;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && adj[s][i])
        {
            vis[i] = 1;
            cnt++;
            dfs(i);
            cout << " " << s;
        }
}

int main()
{
    int a, b, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a][b] = adj[b][a] = 1;
    }
    cnt++;
    vis[s] = 1;
    dfs(s);
    if (cnt < n)
        cout << " 0";
    return 0;
}