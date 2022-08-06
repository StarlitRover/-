/*7-7 ���ȿռ� (30 ��)
�����ȿռ䡱�����ֳ��������ȷָ���Six Degrees of Separation�������ۡ�������ۿ���ͨ�׵ز���Ϊ��������κ�һ��İ����֮����������˲��ᳬ��������Ҳ����˵�����ͨ�����������ܹ���ʶ�κ�һ��İ���ˡ���
�����ȿռ䡱������Ȼ�õ��㷺����ͬ���������ڵõ�Խ��Խ���Ӧ�á�������ʮ��������ͼ��֤�������ʼ����������ѧ��Ŭ��׷���Ŀ�ꡣȻ��������ʷ��ԭ���������о�����̫��ľ����Ժ����ѡ����ŵ����˵�������Ҫ�����ڵ绰�����š�΢���Լ��������ϼ�ʱͨ�ŵȹ��ߣ��ܹ������罻�����ϵ��һ�������Ѿ���ʹ�á����ȿռ䡱���۵���֤��Ϊ���ܡ�

�������һ���罻����ͼ�������ÿ���ڵ������ϡ����ȿռ䡱���۵Ľ��ռ��������İٷֱȡ�

�����ʽ:
�����1�и����������������ֱ��ʾ�罻����ͼ�Ľ����N��1<N��10 
3
 ����ʾ������������M����33��N����ʾ�罻��ϵ����������M�ж�ӦM���ߣ�ÿ�и���һ�����������ֱ��Ǹ�����ֱ����ͨ���������ı�ţ��ڵ��1��N��ţ���

�����ʽ:
��ÿ����������ý����벻����6�Ľ����ռ��������İٷֱȣ���ȷ��С�����2λ��ÿ����ڵ����һ�У���ʽΪ�������:���ո񣩰ٷֱ�%����

��������:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
��β�޿���
�������:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
��β�޿���*/

//ͨ���ڽӾ������·�����ȡ�6����ͨ����
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class graph
{
private:
    int length;
    vector<vector<bool>> path;
public:
    graph()
    {};

    graph(int s)
    {
        length = s;
        path = vector<vector<bool>>(s, vector<bool>(s, false));
    };

    inline void AppendPath(int x, int y);

    vector<vector<bool>> inCircle(int r);
};

inline void graph::AppendPath(int x, int y)
{
    path[x - 1][y - 1] = path[y - 1][x - 1] = true;
}

vector<vector<bool>> graph::inCircle(int r)
{
    vector<vector<bool>> otc = path, pre = path, tmp;
    for (int i = 1; i < r; ++i) //!����ѭ�����������ϴ��������ʱ���г�ʱ
    {
        tmp = vector<vector<bool>>(length, vector<bool>(length, false));
        for (int j = 0; j < length; ++j)
            for (int k = 0; k < length; ++k)
                for (int s = 0; s < length; ++s)
                    if (pre[j][s] && path[s][k])
                    {
                        tmp[j][k] = true;
                        continue;
                    }
        for (int w = 0; w < length; ++w)
            for (int v = 0; v < length; ++v)
                otc[w][v] = otc[w][v] || tmp[w][v];
        pre = tmp;
    }
    return otc;
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
    vector<vector<bool>> otc = g.inCircle(6);
    for (int i = 0; i < m; ++i)
    {
        cout << i + 1 << ": ";
        cout << fixed << setprecision(2) << 100.0 * count(begin(otc[i]), end(otc[i]), true) / m << "%" << endl;
    }
}


//ͨ���ݹ�˼�룺����Ϊn�Ľڵ�Ѱ�ҵ�����Ϊn+1�Ľڵ�
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

class graph
{
private:
    int length;
    vector<vector<bool>> path;
public:
    graph()
    {};

    graph(int s)
    {
        length = s;
        path = vector<vector<bool>>(s, vector<bool>(s, false));
    };

    inline void AppendPath(int x, int y);

    inline bool isLinked(int x, int y);
};

inline void graph::AppendPath(int x, int y)
{
    path[x - 1][y - 1] = path[y - 1][x - 1] = true;
}

inline bool graph::isLinked(int x, int y)
{
    return path[x][y];
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
    vector<vector<bool>> otc(m, vector<bool>(m, false));
    for (int i = 0; i < m; ++i)
    {
        set<int> pre, tmp;
        pre.insert(i);
        int cnt = 0;
        while (!pre.empty() && cnt < 6)
        {
            tmp.clear();
            for (auto k:pre)
                for (int j = 0; j < m; ++j)
                {
                    if (g.isLinked(k, j) && !otc[i][j])  //!otc[i][j]��һ�жϿ��Լ��ٺܶ��ظ�����(���Ե�4�Ĺؼ�)
                    {
                        tmp.insert(j);
                        otc[i][j] = true;
                    }
                }
            pre = tmp;
            ++cnt;
        }
    }
    for (int i = 0; i < m; ++i)
    {
        cout << i + 1 << ": ";
        cout << fixed << setprecision(2) << 100.0 * count(begin(otc[i]), end(otc[i]), true) / m << "%" << endl;
    }
}