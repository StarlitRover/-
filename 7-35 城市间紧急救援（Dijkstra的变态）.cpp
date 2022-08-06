/*7-35 ���м������Ԯ (25 ��)
��Ϊһ�����е�Ӧ����Ԯ����ĸ����ˣ�����һ�������ȫ����ͼ���ڵ�ͼ����ʾ�ж����ɢ�ĳ��к�һЩ���ӳ��еĿ��ٵ�·��ÿ�����еľ�Ԯ��������ÿһ�������������еĿ��ٵ�·���ȶ����ڵ�ͼ�ϡ������������н��������绰�����ʱ����������Ǵ�����ľ�Ԯ�Ӿ�������·��أ�ͬʱ��һ·���ټ������ܶ�ľ�Ԯ�ӡ�

�����ʽ:
�����һ�и���4��������N��M��S��D������N��2��N��500���ǳ��еĸ�����˳�������еı��Ϊ0 ~ (N?1)��M�ǿ��ٵ�·��������S�ǳ����صĳ��б�ţ�D��Ŀ�ĵصĳ��б�š�

�ڶ��и���N�������������е�i�����ǵ�i�����еľ�Ԯ�ӵ���Ŀ�����ּ��Կո�ָ�������M���У�ÿ�и���һ�����ٵ�·����Ϣ���ֱ��ǣ�����1������2�����ٵ�·�ĳ��ȣ��м��ÿո�ֿ������־�Ϊ�����Ҳ�����500�����뱣֤��Ԯ���������Ž�Ψһ��

�����ʽ:
��һ��������·�����������ܹ��ټ������ľ�Ԯ���������ڶ��������S��D��·���о����ĳ��б�š����ּ��Կո�ָ��������β�����ж���ո�

��������:
4 5 0 3
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2

�������:
2 60
0 1 3*/

#include <iostream>
#include <vector>
#include <map>

#define INFINITE INT32_MAX
using namespace std;
vector<int> pre, num_cnt, num, node_cnt;
//pre:��������·����ǰ���ڵ���;num_cnt:��¼�ڵ������ﵽ�ľ�Ԯ�����������յ����������ģ�;num:��¼ÿ���ڵ㴦ԭ�еľ�Ԯ������;node_cnt:��¼·����ÿ���ڵ��ǰ���ڵ�����Ӷ����ⲻ��Ҫ���ظ��ݹ�
vector<vector<int>> possible_pre; //��¼�������·�������ɵ�ǰ���ڵ㣨��Ϊû�п��Ǿ�Ԯ������������possible��

int count(int node) //����·������
{
    if (possible_pre[node].empty()) //������������˵����һ��·��
        return 1;
    int cnt = 0;
    for (auto &k: possible_pre[node]) //������Խ�һ���Ż�����k�ڵ��ѱ�����,��ֱ��ȡk�ڵ�ǰ���ڵ��о�Ԯ���������Ľڵ�����ñ���
    {
        if (num_cnt[node] + num[k] > num_cnt[k])
        {
            num_cnt[k] = num_cnt[node] + num[k];
            pre[k] = node;
        }
        else if (node_cnt[k] != -1) //˵��֮ǰ�Ѿ��ݹ�������ڵ�k
        {
            cnt += node_cnt[k];
            continue;
        }
        cnt += count(k); //����ڵ�k��num_cnt�������˱���Ҫ�ٴεݹ�����ýڵ���Ϊ��Ҫ������Щ�ڵ��num_cnt
    }
    return cnt;
}

int main()
{
    map<pair<int, int>, int> dist;
    int n, m, s, d, input;
    cin >> n >> m >> s >> d;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> input;
        num.push_back(input);
    }
    int a, b, r;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> r;
        graph[a].push_back(b);
        graph[b].push_back(a);
        dist[{a, b}] = dist[{b, a}] = r; //pair��mapǿǿ�������ϡ�����
    }
    vector<int> shortest(n, INFINITE);   //Dijkstra�㷨�е���̾���
    vector<bool> isVisited(n, false);
    possible_pre = vector<vector<int>>(n);
    node_cnt = num_cnt = pre = vector<int>(n, -1);
    shortest[s] = 0;
    isVisited[s] = true;
    for (auto &k: graph[s]) //��ʼ����̾���
    {
        shortest[k] = dist[{s, k}];
        possible_pre[k].push_back(s);
    }
    while (!isVisited[d])  //Dijkstra�㷨
    {
        int min = INFINITE, min_index = -1;
        for (int i = 0; i < n; ++i)
            if (!isVisited[i] && shortest[i] < min)
            {
                min = shortest[i];
                min_index = i;
            }
        isVisited[min_index] = true;
        for (auto &k: graph[min_index])
            if (shortest[min_index] + dist[{min_index, k}] < shortest[k])
            {
                shortest[k] = shortest[min_index] + dist[{min_index, k}];
                possible_pre[k].clear(); //����ǰ����Ľڵ�ȫ�����
                possible_pre[k].push_back(min_index);
            }
            else if (shortest[min_index] + dist[{min_index, k}] == shortest[k]) //���뵱ǰ��̾�����������possible_pre
                possible_pre[k].push_back(min_index);
    }
    num_cnt[d] = num[d];
    int cnt = count(d);
    cout << cnt << " " << num_cnt[s] << endl;
    cout << s;
    s = pre[s];
    while (s != -1)
    {
        cout << " " << s;
        s = pre[s];
    }
}