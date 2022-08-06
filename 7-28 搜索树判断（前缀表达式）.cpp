/*7-28 �������ж� (25 ��)
���ڶ��������������ǹ涨��һ�����������������ϸ�С�ڸý��ļ�ֵ�������������������ڻ���ڸý��ļ�ֵ��������ǽ���ÿ���ڵ�������������������õ������������������������

�������Ǹ���һ��������ֵ���У����д�����жϸ������Ƿ�Ϊĳ�ö�����������ĳ���������������ǰ��������У�����ǣ��������Ӧ�������ĺ���������С�

�����ʽ:
����ĵ�һ�а���һ��������N����1000�����ڶ��а���N��������Ϊ������������ֵ���У����ּ��Կո�ָ���

�����ʽ:
����ĵ�һ�����ȸ����жϽ������������������ĳ�ö�����������ĳ���������������ǰ��������У������YES��������NO������жϽ����YES����һ�������Ӧ�������ĺ���������С����ּ��Կո�ָ�������β�����ж���Ŀո�

��������1:
7
8 6 5 7 10 8 11

�������1:
YES
5 7 6 8 11 10 8

��������2:
7
8 6 8 5 10 9 11
�������2:
NO*/

#include <iostream>
#include <vector>

using namespace std;
vector<int> Postfix, tree;
bool isMirror = false;

bool isSearchTree(int root, int tail)
{
    if (root == tail + 1) //��һ�ߵ������������κ�Ԫ�ص����(root==tail���������Ҳ���ߵ���)
        return true;
    int t1 = root + 1, r2 = tail;
    if (!isMirror) //����һ����<tree[root]��һ����>=tree[root]�����ֲ��Գ���(=)����isMirror������������ܺϲ�
    {
        while (t1 <= tail && tree[t1] < tree[root])
            ++t1;
        while (r2 > root && tree[r2] >= tree[root])
            --r2;
    }
    else
    {
        while (t1 <= tail && tree[t1] >= tree[root])
            ++t1;
        while (r2 > root && tree[r2] < tree[root])
            --r2;
    }
    if (t1 - r2 != 1)
        return false;
    bool left = isSearchTree(root + 1, t1 - 1), right = isSearchTree(r2 + 1, tail);
    Postfix.push_back(tree[root]); //˳���¼��׺���ʽ
    return left && right;
}

int main()
{
    int n, tmp;
    bool flag = true;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> tmp;
        tree.push_back(tmp);
    }
    if (!isSearchTree(0, n - 1))
    {
        isMirror = true;
        Postfix.clear();
        flag = isSearchTree(0, n - 1);
    }
    if (flag)
    {
        cout << "YES\n" << Postfix[0];
        for (int i = 1; i < n; ++i)
            cout << " " << Postfix[i];
    }
    else
        cout << "NO";
}