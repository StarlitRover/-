/*7-28 搜索树判断 (25 分)
对于二叉搜索树，我们规定任一结点的左子树仅包含严格小于该结点的键值，而其右子树包含大于或等于该结点的键值。如果我们交换每个节点的左子树和右子树，得到的树叫做镜像二叉搜索树。

现在我们给出一个整数键值序列，请编写程序判断该序列是否为某棵二叉搜索树或某镜像二叉搜索树的前序遍历序列，如果是，则输出对应二叉树的后序遍历序列。

输入格式:
输入的第一行包含一个正整数N（≤1000），第二行包含N个整数，为给出的整数键值序列，数字间以空格分隔。

输出格式:
输出的第一行首先给出判断结果，如果输入的序列是某棵二叉搜索树或某镜像二叉搜索树的前序遍历序列，则输出YES，否侧输出NO。如果判断结果是YES，下一行输出对应二叉树的后序遍历序列。数字间以空格分隔，但行尾不能有多余的空格。

输入样例1:
7
8 6 5 7 10 8 11

输出样例1:
YES
5 7 6 8 11 10 8

输入样例2:
7
8 6 8 5 10 9 11
输出样例2:
NO*/

#include <iostream>
#include <vector>

using namespace std;
vector<int> Postfix, tree;
bool isMirror = false;

bool isSearchTree(int root, int tail)
{
    if (root == tail + 1) //有一边的子树不包含任何元素的情况(root==tail的情况最终也会走到这)
        return true;
    int t1 = root + 1, r2 = tail;
    if (!isMirror) //由于一边是<tree[root]，一边是>=tree[root]，这种不对称性(=)导致isMirror的两种情况不能合并
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
    Postfix.push_back(tree[root]); //顺便记录后缀表达式
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