/*7-4 是否同一棵二叉搜索树 (25 分)
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。随后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
结尾无空行
输出样例:
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

void releaseTree(TreeNode &k)  //不能将其改为析构函数，不然在delete指针时就会自动调用该函数
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