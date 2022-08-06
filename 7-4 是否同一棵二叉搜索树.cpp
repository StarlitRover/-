/*7-4 �Ƿ�ͬһ�ö��������� (25 ��)
����һ���������оͿ���Ψһȷ��һ�ö�����������Ȼ����һ�ø����Ķ���������ȴ�����ɶ��ֲ�ͬ�Ĳ������еõ�������ֱ�������{2, 1, 3}��{2, 3, 1}�����ʼΪ�յĶ��������������õ�һ���Ľ�������Ƕ�������ĸ��ֲ������У�����Ҫ�ж������Ƿ�������һ���Ķ�����������

�����ʽ:
�������������������ݡ�ÿ�����ݵĵ�1�и�������������N (��10)��L���ֱ���ÿ�����в���Ԫ�صĸ�������Ҫ�������и�������2�и���N���Կո�ָ�������������Ϊ��ʼ�������С����L�У�ÿ�и���N�������Ԫ�أ�����L����Ҫ�������С�

����������Ǳ�֤ÿ���������ж���1��N��һ�����С�������NΪ0ʱ����־����������������ݲ�Ҫ����

�����ʽ:
��ÿһ����Ҫ�������У���������ɵĶ�������������Ӧ�ĳ�ʼ�������ɵ�һ���������Yes�������������No����

��������:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
��β�޿���
�������:
Yes
No
No*/
#include <iostream>
#include <list>

using namespace std;

class TreeNode
{
public:
    int num = -1;
    TreeNode *left = nullptr, *right = nullptr;

    TreeNode()
    {};

    TreeNode(int k) : num(k)
    {};

    void append(int k);
};

void TreeNode::append(int k)
{
    if (num == -1)
    {
        num = k;
        return;
    }
    TreeNode *tmp = this;
    while ((tmp->num > k ? tmp->left : tmp->right) != nullptr)
        tmp = tmp->num > k ? tmp->left : tmp->right;
    if (tmp->num > k)
        tmp->left = new TreeNode(k);
    else
        tmp->right = new TreeNode(k);
}

void releaseTree(TreeNode &k)  //���ܽ����Ϊ������������Ȼ��deleteָ��ʱ�ͻ��Զ����øú���
{
    list<TreeNode *> pre, tmp;
    if (k.left != nullptr)
        pre.push_back(k.left);
    if (k.right != nullptr)
        pre.push_back(k.right);
    while (!pre.empty())
    {
        for (auto &t:pre)
        {
            if (t->left != nullptr)
                tmp.push_back(t->left);
            if (t->right != nullptr)
                tmp.push_back(t->right);
        }
        for (auto &t:pre)
            delete t;
        pre = tmp;
        tmp.clear();
    }
}

bool isSame(TreeNode *t1, TreeNode *t2)
{
    if (t1 == nullptr && t2 == nullptr)
        return true;
    if (t1 == nullptr || t2 == nullptr)
        return false;
    if (t1->num != t2->num)
        return false;
    else
        return isSame(t1->left, t2->left) && isSame(t1->right, t2->right);
}

int main()
{
    int n, l, m;
    cin >> n;
    while (n != 0)
    {
        cin >> l;
        TreeNode first;
        for (int j = 0; j < n; ++j)
        {
            cin >> m;
            first.append(m);
        }
        for (int i = 0; i < l; ++i)
        {
            TreeNode tmp;
            for (int j = 0; j < n; ++j)
            {
                cin >> m;
                tmp.append(m);
            }
            if (isSame(&first, &tmp))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            releaseTree(tmp);
        }
        releaseTree(first);
        cin >> n;
    }
}