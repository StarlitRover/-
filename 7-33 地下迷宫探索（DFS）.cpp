/*7-33 �����Թ�̽�� (30 ��)
�ص�ս���ڿ���ս��ʱ�ڣ��ڻ���ƽԭ�Ͽ��վ������õص�����ձ������ߵ���ս��ʽ���ص����Ƿ������������֡�������ĵ��¹��¡�

�����ڻع�ǰ���Ǽ��׿����ս�������ͬʱ�������������ǵĴ������ǡ������ں�ƽ��չ��������Զ�������˵��̽������ͨ������ֻ��һ�����ֻ������ǵ���Ϸ����ʵ�鰸����̽������ͨ���Թ���Ϊ���ݡ�

������һ������ͨ���Թ�������ͨ������ֱ�ģ���ͨ�����н���㣨����ͨ���Ķ˵㣩�϶���һյ�ƺ�һ�����ء���������δ�ĳ����㿪ʼ���Թ��е������еĵƲ��ص���㣿

�����ʽ:
�����һ�и����������������ֱ��ʾ�����Թ��Ľڵ���N��1<N��1000����ʾͨ�����н����Ͷ˵㣩������M����3000����ʾͨ��������̽����ʼ�ڵ���S���ڵ��1��N��ţ�������M�ж�ӦM���ߣ�ͨ������ÿ�и���һ�����������ֱ��Ǹ�����ֱ����ͨ�������ڵ�ı�š�

�����ʽ:
�����Ե������нڵ�ĵƣ��������S��ʼ����S�����İ������нڵ�����У����������ڵĽڵ�һ���бߣ�ͨ������������Ȼ���ܵ������нڵ�ĵƣ�����������������ֵƵĽڵ����У�������0����ʱ��ʾ�Թ�������ͨͼ��

����������ȱ����Ľڵ������ǲ�Ψһ�ģ�Ϊ��ʹ���������Ψһ�Ľ��������Լ���Խڵ�С������ȵĴ�����ʣ���ƣ����ڵ������п��Ե����ĵƺ���ԭ·���صķ�ʽ�ص���㡣

��������1:
6 8 1
1 2
2 3
3 4
4 5
5 6
6 4
3 6
1 5

�������1:
1 2 3 4 5 6 5 4 3 2 1

��������2:
6 6 6
1 2
1 3
2 3
5 4
6 5
6 4
�������2:
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
    vector<set<int>> graph(n);  //vector<set>��ӵ����vector�ĶԽڵ��ֱ�ӷ��ʹ���������set�Զ�������
    vector<int> path;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a - 1].insert(b - 1);
        graph[b - 1].insert(a - 1);
    }
    vector<bool> isVisited(n, false);
    stack<int> track;           //��¼ԭʼ������·��
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
            track.push(start);  //track��¼��·���в�������ǰ�ڵ㣬��᷽�����ʱ�Ĳ���
            path.push_back(flag);
            isVisited[flag] = true;
            start = flag;
            cnt += 1;
        }
        else if (track.empty()) //���˻������
            break;
        else                    //���л���
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
        while (!track.empty())  //��Ȼ����ջtrack�����洢��·�����ǲ�������ԭ·
        {
            cout << " " << track.top() + 1;
            track.pop();
        }
    else
        cout << " 0";
}
/*��Ŀ�еġ�ԭ·����ʵ��ָ����û�в�����(���)��ԭ·*/

//�ݹ���ð�DFS  --from website
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