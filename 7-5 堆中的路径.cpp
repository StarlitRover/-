/*7-5 ���е�·�� (25 ��)
��һϵ�и������ֲ���һ����ʼΪ�յ�С����H[]����������������±�i����ӡ��H[i]��������·����

�����ʽ:
ÿ����Ե�1�а���2��������N��M(��1000)���ֱ��ǲ���Ԫ�صĸ������Լ���Ҫ��ӡ��·����������һ�и�������[-10000, 10000]�ڵ�N��Ҫ������һ����ʼΪ�յ�С���ѵ����������һ�и���M���±ꡣ

�����ʽ:
�������и�����ÿ���±�i����һ���������H[i]��������·���ϵ����ݡ����ּ���1���ո�ָ�����ĩ�����ж���ո�

��������:
5 3
46 23 26 24 10
5 4 3
��β�޿���
�������:
24 23 10
46 23 10
26 10
��β�޿���*/
#include <iostream>
#include <vector>

using namespace std;

class min_heap
{
public:
    void append(int k);

    void printPath(int k);

private:
    int num = 0;
    vector<int> val;
};

void min_heap::append(int k)
{
    val.push_back(k);
    num += 1;
    int father_num = num / 2, self_num = num;
    while (self_num != 1 && val[father_num - 1] > val[self_num - 1])
    {
        swap(val[father_num - 1], val[self_num - 1]);
        self_num = father_num;
        father_num = father_num / 2;
    }
}

void min_heap::printPath(int k)
{
    for (k; k > 0; k /= 2)
    {
        cout << val[k - 1];
        if (k != 1)
            cout << " ";
    }
    cout << endl;
}

int main()
{
    int n, m, k;
    cin >> n >> m;
    min_heap h;
    for (int i = 0; i < n; ++i)
    {
        cin >> k;
        h.append(k);
    }
    for (int i = 0; i < m; ++i)
    {
        cin >> k;
        h.printPath(k);
    }
}
