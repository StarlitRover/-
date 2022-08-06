/*7-11 �ؼ�� (30 ��)
�ٶ�һ��������Ŀ��һ�������񹹳ɣ�������֮���еĿ��Բ���ִ�У��еı��������������һЩ����������ִ�С���������ȡ�����һ���������Լ�ÿ�����������ִ���������������񼯡�

�������һ��רҵ�����пγ�ѧϰ�ͱ�ҵ��ƿ��Կ���һ��������Ҫ��ɵ�һ��̣����ſγ̿��Կ�������������Щ�γ̿���ͬʱ���裬����Ӣ���C������ƣ�����û�б����������ŵ�Լ������Щ�γ��򲻿���ͬʱ���裬��Ϊ�������Ⱥ��������ϵ������C������ƺ����ݽṹ���ſΣ�������ѧϰǰ�ߡ�

������Ҫע����ǣ���һ�������񣬲����������������ȶ���һ�����еķ��������緽���д��ڡ�������A������������B��������B������������C��������C��������������A������ô�����������ĸ���������ִ�У������һ�������еķ�����

������������У���������������ÿ����������Ҫ��ʱ�䣬�����ǿ�������������������Ҫ�����ʱ�䡣����Щ�������У���Щ����ʹ�Ƴټ�����ɣ�Ҳ����Ӱ��ȫ�ֵĹ��ڣ�������Щ�������׼ʱ��ɣ�����������Ŀ�Ĺ��ھ�Ҫ���������������ͽС��ؼ������

���д�����ж�һ�������Ĺ�����Ŀ����������Ƿ���У�����õ��ȷ������У�������������������Ŀ��Ҫ�����ʱ�䣬��������еĹؼ����

�����ʽ:
�����1�и�������������N(��100)��M������N�����񽻽ӵ㣨���ν��໥����������������Ľڵ㣬���磺������2Ҫ������1��ɺ�ſ�ʼ����������֮�����һ�����ӵ㣩�����������ӵ㰴1~N��ţ�M������������������α��Ϊ1~M�����M�У�ÿ�и�����3�����������ֱ��Ǹ�����ʼ������漰�Ľ��ӵ����Լ������������ʱ�䣬�������ÿո�ָ���

�����ʽ:
���������Ȳ����У������0�������1������������������Ŀ��Ҫ��ʱ�䣬��2�п�ʼ������йؼ����ÿ���ؼ��ռһ�У�����ʽ��V->W�����������V��WΪ������ʼ������漰�Ľ��ӵ��š��ؼ�������˳������ǣ�����ʼ�Ľ��ӵ���С�����ȣ��������ͬʱ��������ʱ�����˳���෴��

��������:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
�������:
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
    int in_degree = 0, ve = 0, vl = 0; //����ֻ��¼���������û�м�¼������ߣ���Ϊ�Ѿ�������Ŀ����
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
//Ϊ�˽��[�������ͬʱ��������ʱ�����˳���෴]������,���ｫ�Ѿ�������˳�����кõıߣ�����������Ĵ�С���н������򣬴Ӷ���β��ͷ��ʱ�����ǰ��������С��������ͬ���ı��յ㰴����˳���෴�ķ�ʽ����
        for (int i = 0; i < n; ++i) //������ɺ��ٽ��ߵ���Ϣѹ����ص������
            ps[es[i].tail].out_edge.push_back(i);
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n);

    //���������жϸ�ͼ�Ƿ���ڻ�
    vector<int> edge_num, dest;//edge_num��ģ�����������ȥ�߹���
    stack<int> in_degree0;
    stack<int> inverse; //��¼����������˳���Լ����¼�������ʼʱ��
    for (int i = 0; i < m; ++i)
    {
        edge_num.push_back(g.ps[i].in_degree);
        if (edge_num[i] == 0) //��¼������㣨�����Ϊ0��
            in_degree0.push(i); 
        if (g.ps[i].out_edge.empty()) //��¼�����յ㣨����Ϊ0��
            dest.push_back(i);
    }
    auto cnt = in_degree0.size(); //��¼����ǵĵ�������֤�Ƿ����е㶼������
	//��������
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
            //˳������¼������緢��ʱ��
            if (g.es[k].val + p.ve > g.ps[g.es[k].head].ve)
                g.ps[g.es[k].head].ve = g.es[k].val + p.ve;
        }
    }
    //�ж��Ƿ����е㶼��������������˵��ͼg���ڻ�
    if (cnt != m)
    {
        cout << "0" << endl;
        exit(0);
    }
    //����ÿ���¼�������ʼʱ��
    int max_dest_vl = 0;
    for (auto &d: dest)
    {
        g.ps[d].vl = g.ps[d].ve;
        if (max_dest_vl < g.ps[d].ve)
            max_dest_vl = g.ps[d].ve;
    }
    for (auto &p: g.ps)
        p.vl = max_dest_vl;
    vector<bool> key_path(n, false); //key_path��֤��edge��˳�򲻱�����
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
/*�Կ��ۣ��������������. �����Ŀ���ѵ�ֱ���:
1.��ͼ�п��ܴ��ڻ�ʹ�����޷���� (��������)
2.��ͼ�п��ܴ��ڶ��������յ㣬����ͨ��AOEͼ��ͬ
3.��ʹֻ��һ���յ������Ҳ���ܴ��ڶ����ؼ�·��
4.����ؼ�����ʱ�������ͬ����Ҫ������ʱ�����˳���෴