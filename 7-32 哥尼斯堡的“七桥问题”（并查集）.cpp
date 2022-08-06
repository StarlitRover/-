/*7-32 ����˹���ġ��������⡱ (25 ��)
����˹����λ�����۸���ϵ�һ�����У��������������켰�������ǵ������š�

�ɷ��߹������������ţ�����ÿ��ֻ�߹�һ�Σ���ʿ��ѧ��ŷ��(Leonhard Euler��1707?1783)���ս����������⣬���ɴ˴���������ѧ��

�����������������Ϊ�ж�ŷ����·�Ƿ���ڵ����⡣ŷ����·��ָ������뿪ֽ�棬�ɻ���ͼ��ÿ���߽�һ�Σ��ҿ��Իص�����һ����·���ָ���һ������ͼ�����Ƿ����ŷ����·��

�����ʽ:
�����һ�и����������������ֱ��ǽڵ���N (1��N��1000)�ͱ���M������M�ж�ӦM���ߣ�ÿ�и���һ�����������ֱ��Ǹ�����ֱ����ͨ�������ڵ�ı�ţ��ڵ��1��N��ţ���

�����ʽ:
��ŷ����·���������1���������0��

��������1:
6 10
1 2
2 3
3 1
4 5
5 6
6 4
1 4
1 6
3 4
3 6

�������1:
1

��������2:
5 8
1 2
1 3
2 3
2 4
2 5
5 3
5 4
3 4
�������2:
0*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    int n, m, a, b;
    cin >> n >> m;
    vector<size_t> cnt(n, 0), size(n, 0);
    vector<int> root(n);
    iota(root.begin(), root.end(), 0);
    //ͨ�����鼯�ж�ͼ�Ƿ���ͨ
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        a -= 1;
        b -= 1;
        cnt[a] += 1;
        cnt[b] += 1;
		//�Ƚ�a���ڼ�����b���ڼ��ŵ�������С
        int max = (size[root[a]] >= size[root[b]]) ? a : b, min = (size[root[a]] >= size[root[b]]) ? b : a;
        root[root[min]] = root[max]; //���root[min] = root[max]��ᵼ��min�����첻����ڸ��������
        size[root[max]] += size[root[min]] + 1;
    }
    int king = -1;
    for (auto& k: root) //֮���Կ��������ã�����Ϊ����һ�ָ��²���ʹroot�ĺ��巢���ı���ҿ�����ߺ���������Ч��
    {
        while (root[k] != k)
            k = root[k];
        if (king == -1)
            king = k;
        else if (k != king)
        {
            cout << 0;
            exit(0);
        }
    }
    //��ͼ��ͨ���ж�ÿ����Ķ��Ƿ�Ϊż��
    bool flag = true;
    for (auto &k: cnt)
        if (k % 2 == 1)
        {
            flag = false;
            break;
        }
    if (flag)
        cout << 1;
    else
        cout << 0;
}