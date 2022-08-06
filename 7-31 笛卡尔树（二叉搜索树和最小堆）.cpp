/*7-31 �ѿ����� (25 ��)
�ѿ�������һ������Ķ�������������������ؼ���K1��K2�����ȵѿ������ǹ���K1�Ķ����������������������������K1ֵ���ȸý���K1ֵС�����������������н���K2�ؼ����������ȶ��У�������Ϊ��С�ѣ���˳��Ҫ�󣬼��ý���K2ֵ�������������н���K2ֵС������һ�ö����������жϸ����Ƿ�ѿ�������

�����ʽ:
�������ȸ���������N����1000����Ϊ���н��ĸ��������N�У�ÿ�и���һ��������Ϣ������������K1ֵ��K2ֵ�����ӽ���š��Һ��ӽ���š������0~(N-1)˳���š���ĳ��㲻���ں��ӽ�㣬���λ�ø���?1��

�����ʽ:
���YES���������һ�õѿ��������������NO��

��������1:
6
8 27 5 1
9 40 -1 -1
10 20 0 3
12 21 -1 4
15 22 -1 -1
5 35 -1 -1

�������1:
YES

��������2:
6
8 27 5 1
9 40 -1 -1
10 20 0 3
12 11 -1 4
15 22 -1 -1
50 35 -1 -1
�������2:
NO*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<pair<int, int>> tree, son_nodes;  //pair���Ǹ��ö���������������ģ�������

//��ʵ�϶���������Ҳ����ͨ�������������Ǹ��������н����ж� 
bool isBinarySearchTree(int node, bool isLeftNode, int threshold) //isLeftNode��threshold��Ϊ�˷�ֹ���ң����������С���ڵ�ȵ�ǰ�ڵ��С��
{
    if (node == -1)
        return true;
    int left = son_nodes[node].first, right = son_nodes[node].second;
    if (left != -1)
    {
        if (tree[node].first <= tree[left].first)
            return false;
        if (!isLeftNode && tree[left].first <= threshold)
            return false;
    }
    if (right != -1)
    {
        if (tree[node].first >= tree[right].first)
            return false;
        if (isLeftNode && tree[right].first >= threshold)
            return false;
    }
    return isBinarySearchTree(left, true, tree[node].first) && isBinarySearchTree(right, false, tree[node].first);
}

bool isMinHeap(int node)
{
    if (node == -1)
        return true;
    int left = son_nodes[node].first, right = son_nodes[node].second;
    if ((left == -1 ? false : tree[left].second <= tree[node].second) || (right == -1 ? false : tree[right].second <= tree[node].second))
        return false;  //ע�⡾||�������ȼ��ȡ�?:�������ȼ�������������Ҫ��()
    return isMinHeap(left) && isMinHeap(right);
}

int main()
{
    int n, left, right;
    cin >> n;
    vector<bool> isRoot(n, true);
    for (int i = 0; i < n; ++i)
    {
        cin >> left >> right;
        tree.emplace_back(left, right);
        cin >> left >> right;
        son_nodes.emplace_back(left, right);
        if (left != -1)
            isRoot[left] = false;
        if (right != -1)
            isRoot[right] = false;
    }
    int node = find(isRoot.begin(), isRoot.end(), true) - isRoot.begin();
    if (isBinarySearchTree(node, true, INT32_MAX) && isMinHeap(node))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}