/*7-40 �������а� (25 ��)
ÿ����˻����ý�嶼�ṫ��һ�����а񣬵���ϸ�ĵĶ��߷��֣���ͬ���ҵ����а����в�ͬ�������й����������е�һ��ʱ���й�ý��͹��������ư񡱣��������Ľ���������һ����������ý��͹��������ư񡱡�����˿��ٵĹ��ҹ���һ���������˾����ư񡱣�˵�������޵Ĺ��һ��Ϊ������� ���ھ�����дһ�����򣬶�ÿ��ǰ����ѯ�Ĺ��Ұ��ն����������ķ�ʽ��������������

�����ʽ:
����ĵ�һ�и�������������N��M����224����Ϊ�����Ϲ���224�����Һ͵��������ֱ��ǲ��������Ĺ��Һ͵������ܸ������Լ�ǰ����ѯ�Ĺ��ҵĸ�����Ϊ����������ǰѹ��Ҵ�0 ~ N?1��š�֮����N�����룬��i�и������Ϊi?1�Ĺ��ҵĽ��������������������˿�������λΪ���򣩣����־�Ϊ[0,1000]�����ڵ��������ÿո�ָ��������һ�и���M��ǰ����ѯ�Ĺ��ҵı�ţ��ÿո�ָ���

�����ʽ:
��һ����˳�����ǰ����ѯ�Ĺ��ҵ�����:���㷽ʽ��š����������նԸù����������ķ�ʽ���㣻���㷽ʽ���Ϊ�����ư�=1�����ư�=2�������˾����ư�=3�������˾����ư�=4��������Կո�ָ��������β�����ж���ո�

��ĳ���ڲ�ͬ������ʽ������ͬ���Σ�����������С�ļ��㷽ʽ��

��������:
4 4
51 100 1000
36 110 300
6 14 32
5 18 40
0 1 2 3

�������:
1:1 1:2 1:3 1:4*/

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_COUNTRY_NUM 225
using namespace std;

class country
{
public:
    int num;
    double judge[4];  //�����ּ��㷽ʽ�Ľ��

    country(int g, int m, int p, int n)
    {
        judge[0] = g;
        judge[1] = m;
        judge[2] = 1.0 * g / p;
        judge[3] = 1.0 * m / p;
        num = n;
    };
};

int method;
vector<country> countries;

int main()
{
    int n, k, g, m, p, t;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        cin >> g >> m >> p;
        countries.emplace_back(country(g, m, p, i));
    }
    vector<pair<int, int>> rank(n, pair(MAX_COUNTRY_NUM, 0));   //��������С�Ľ���Լ���Ӧ������ʽ���
    for (method = 0; method < 4; ++method)
    {
        sort(countries.begin(), countries.end(), [](country &x, country &y)
        { return x.judge[method] > y.judge[method]; });
        int r = 1;
        double pre = countries[0].judge[method];
        for (int i = 0; i < n; ++i)
        {
            r = (countries[i].judge[method] == pre) ? r : i + 1;  //ע�⽱������ͬ������ͬ��������䵱ǰ���+1���������е�һ�����ǵ������ǵڶ���
            if (r < rank[countries[i].num].first)
                rank[countries[i].num] = move(pair(r, method + 1));
            pre = countries[i].judge[method];
        }
    }
    for (int i = 0; i < k; ++i)
    {
        cin >> t;
        cout << ((i == 0) ? "" : " ") << rank[t].first << ":" << rank[t].second;
    }
}