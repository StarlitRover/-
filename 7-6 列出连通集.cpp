/*7-6 列出连通集 (25 分)
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N?1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
按照"{v1,v2,...,vk}"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
结尾无空行
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
结尾无空行*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class graph
{
private:
    vector<vector<bool>> path;
public:
    graph()
    {};

    graph(int s)
    {
        path = vector<vector<bool>>(s, vector<bool>(s, false));
    };

    inline void AppendPath(int x, int y);

    inline bool isLinked(int x, int y);
};

inline void graph::AppendPath(int x, int y)
{
    path[x][y] = path[y][x] = true;
}

inline bool graph::isLinked(int x, int y)
{
    return path[x][y] == true;
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
    vector<bool> isVisited(m, false);
	
    //DFS
    for (int i = 0; i < m; ++i)
    {
        if (isVisited[i])
            continue;
        vector<int> set;
        set.push_back(i);
        stack<int> p; //用栈p来记录路径
        p.push(i);
        isVisited[i] = true;
        int k = i;
        for (int j = 0; j < m; ++j)
        {
            if (g.isLinked(k, j) && !isVisited[j])
            {
                set.push_back(j);
                isVisited[j] = true;
                p.push(k);
                k = j; //一旦有新的节点可以到达便先到新的节点进行搜寻
                j = -1;
                continue;
            }
            else if (j == m - 1) //无路可走则按路径p返回继续搜寻
            {
                if (p.empty())
                    break;
                k = p.top();
                p.pop();
                j = 0;
                continue;
            }
        }
        cout << "{ ";
        for (auto k:set)
            cout << k << " ";
        cout << "}" << endl;
    }
    isVisited = vector<bool>(m, false);
    
	//BFS
    for (int i = 0; i < m; ++i)
    {
        if (isVisited[i])
            continue;
        isVisited[i] = true;
        vector<int> pre, all, tmp;
        all.push_back(i);
        pre.push_back(i);
        while (!pre.empty())
        {
            for (auto k:pre)
            {
                for (int j = 0; j < m; ++j)
                    if (g.isLinked(k, j) && !isVisited[j])
                    {
                        all.push_back(j);
                        tmp.push_back(j);
                        isVisited[j] = true;
                    }
            }
            pre = tmp;
            tmp.clear();
        }
        cout << "{ ";
        for (auto k:all)
            cout << k << " ";
        cout << "}" << endl;
    }
}