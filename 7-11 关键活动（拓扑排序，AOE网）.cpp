/*7-11 关键活动 (30 分)
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

输入格式:
输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

输出格式:
如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
输出样例:
17
1->2
2->4
4->6
6->7
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class point
{
public:
    int in_degree = 0, ve = 0, vl = 0; //这里只记录了入度数而没有记录所有入边（因为已经满足题目需求）
    vector<int> out_edge;
};

class edge
{
public:
    int val, tail, head;

    edge(int former, int latter, int weight) : tail(former - 1), head(latter - 1), val(weight)
    {};
};

class graph
{
public:
    vector <point> ps;
    vector <edge> es;

    graph(int m, int n)
    {
        ps = vector<point>(m, point());
        int former, latter, weight;
        for (int i = 0; i < n; ++i)
        {
            cin >> former >> latter >> weight;
            es.emplace_back(edge(former, latter, weight));
            ps[latter - 1].in_degree += 1;
        }
        sort(es.begin(), es.end(), [](edge &x, edge &y){ return x.tail > y.tail; }); 
//为了解决[起点编号相同时，与输入时任务的顺序相反]的问题,这里将已经按输入顺序排列好的边（活动）按照起点的大小进行降序排序，从而由尾向头看时，便是按照起点由小至大，且相同起点的边终点按输入顺序相反的方式排列
        for (int i = 0; i < n; ++i) //排序完成后再将边的信息压入相关点对象中
            ps[es[i].tail].out_edge.push_back(i);
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n);

    //拓扑排序：判断该图是否存在环
    vector<int> edge_num, dest;//edge_num来模拟拓扑排序的去边过程
    stack<int> in_degree0;
    stack<int> inverse; //记录逆拓扑排序顺序以计算事件的最晚开始时间
    for (int i = 0; i < m; ++i)
    {
        edge_num.push_back(g.ps[i].in_degree);
        if (edge_num[i] == 0) //记录所有起点（入度数为0）
            in_degree0.push(i); 
        if (g.ps[i].out_edge.empty()) //记录所有终点（出度为0）
            dest.push_back(i);
    }
    auto cnt = in_degree0.size(); //记录被标记的点数以验证是否所有点都被遍历
	//拓扑排序
    while (!in_degree0.empty())
    {
        point &p = g.ps[in_degree0.top()];
        in_degree0.pop();
        for (auto k: p.out_edge)
        {
            edge_num[g.es[k].head] -= 1;
            inverse.push(k);
            if (edge_num[g.es[k].head] == 0)
            {
                in_degree0.push(g.es[k].head);
                cnt += 1;
            }
            //顺便计算事件的最早发生时间
            if (g.es[k].val + p.ve > g.ps[g.es[k].head].ve)
                g.ps[g.es[k].head].ve = g.es[k].val + p.ve;
        }
    }
    //判断是否所有点都经历排序，若否则说明图g存在环
    if (cnt != m)
    {
        cout << "0" << endl;
        exit(0);
    }
    //计算每个事件的最晚开始时间
    int max_dest_vl = 0;
    for (auto &d: dest)
    {
        g.ps[d].vl = g.ps[d].ve;
        if (max_dest_vl < g.ps[d].ve)
            max_dest_vl = g.ps[d].ve;
    }
    for (auto &p: g.ps)
        p.vl = max_dest_vl;
    vector<bool> key_path(n, false); //key_path保证了edge的顺序不被打乱
    while (!inverse.empty())
    {
        edge &e = g.es[inverse.top()];
        if (g.ps[e.tail].vl >= g.ps[e.head].vl - e.val)
        {
            g.ps[e.tail].vl = g.ps[e.head].vl - e.val;
            if (g.ps[e.tail].vl == g.ps[e.tail].ve && g.ps[e.head].vl == g.ps[e.head].ve)
                key_path[inverse.top()] = true;
        }
        inverse.pop();
    }
    cout << max_dest_vl << endl;
    for (int i = n - 1; i > -1; --i)
        if (key_path[i])
            cout << g.es[i].tail + 1 << "->" << g.es[i].head + 1 << endl;
}
/*脑壳疼，这题耗了两三天. 这道题目的难点分别有:
1.该图中可能存在环使工程无法完成 (拓扑排序)
2.该图中可能存在多个起点与终点，较普通的AOE图不同
3.即使只有一个终点与起点也可能存在多条关键路径
4.输出关键任务时若起点相同则需要与输入时任务的顺序相反