/*7-6 �г���ͨ�� (25 ��)
����һ����N�������E���ߵ�����ͼ������DFS��BFS�ֱ��г������е���ͨ�������趥���0��N?1��š���������ʱ�������������Ǵӱ����С�Ķ������������ŵ�����˳������ڽӵ㡣

�����ʽ:
�����1�и���2������N(0<N��10)��E���ֱ���ͼ�Ķ������ͱ��������E�У�ÿ�и���һ���ߵ������˵㡣ÿ���е�����֮����1�ո�ָ���

�����ʽ:
����"{v1,v2,...,vk}"�ĸ�ʽ��ÿ�����һ����ͨ���������DFS�Ľ���������BFS�Ľ����

��������:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
��β�޿���
�������:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
��β�޿���*/
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
        stack<int> p; //��ջp����¼·��
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
                k = j; //һ�����µĽڵ���Ե�����ȵ��µĽڵ������Ѱ
                j = -1;
                continue;
            }
            else if (j == m - 1) //��·������·��p���ؼ�����Ѱ
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