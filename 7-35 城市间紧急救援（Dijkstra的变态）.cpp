/*7-35 城市间紧急救援 (25 分)
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。在地图上显示有多个分散的城市和一些连接城市的快速道路。每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。

输入格式:
输入第一行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0 ~ (N?1)；M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号。

第二行给出N个正整数，其中第i个数是第i个城市的救援队的数目，数字间以空格分隔。随后的M行中，每行给出一条快速道路的信息，分别是：城市1、城市2、快速道路的长度，中间用空格分开，数字均为整数且不超过500。输入保证救援可行且最优解唯一。

输出格式:
第一行输出最短路径的条数和能够召集的最多的救援队数量。第二行输出从S到D的路径中经过的城市编号。数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2

输出样例:
2 60
0 1 3*/

#include <iostream>
#include <vector>
#include <map>

#define INFINITE INT32_MAX
using namespace std;
vector<int> pre, num_cnt, num, node_cnt;
//pre:计算最终路径的前驱节点编号;num_cnt:记录节点上最多达到的救援队数量（从终点至起点计数的）;num:记录每个节点处原有的救援队数量;node_cnt:记录路径上每个节点的前驱节点个数从而避免不必要的重复递归
vector<vector<int>> possible_pre; //记录所有最短路径所构成的前驱节点（因为没有考虑救援队数量所以是possible）

int count(int node) //返回路径条数
{
    if (possible_pre[node].empty()) //如过到达起点则说明是一条路径
        return 1;
    int cnt = 0;
    for (auto &k: possible_pre[node]) //这里可以进一步优化：若k节点已被遍历,则直接取k节点前驱节点中救援队总数最大的节点而不用遍历
    {
        if (num_cnt[node] + num[k] > num_cnt[k])
        {
            num_cnt[k] = num_cnt[node] + num[k];
            pre[k] = node;
        }
        else if (node_cnt[k] != -1) //说明之前已经递归遍历过节点k
        {
            cnt += node_cnt[k];
            continue;
        }
        cnt += count(k); //如果节点k的num_cnt被更新了必须要再次递归遍历该节点因为需要更新这些节点的num_cnt
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
        dist[{a, b}] = dist[{b, a}] = r; //pair和map强强组合来存稀疏矩阵
    }
    vector<int> shortest(n, INFINITE);   //Dijkstra算法中的最短距离
    vector<bool> isVisited(n, false);
    possible_pre = vector<vector<int>>(n);
    node_cnt = num_cnt = pre = vector<int>(n, -1);
    shortest[s] = 0;
    isVisited[s] = true;
    for (auto &k: graph[s]) //初始化最短距离
    {
        shortest[k] = dist[{s, k}];
        possible_pre[k].push_back(s);
    }
    while (!isVisited[d])  //Dijkstra算法
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
                possible_pre[k].clear(); //把先前存入的节点全部清空
                possible_pre[k].push_back(min_index);
            }
            else if (shortest[min_index] + dist[{min_index, k}] == shortest[k]) //若与当前最短距离相等则存入possible_pre
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