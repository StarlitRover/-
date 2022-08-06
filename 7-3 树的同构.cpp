#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class TreeNode
{
public:
    string name;
    int left_num, right_num;
    TreeNode *left = nullptr, *right = nullptr;
};

bool isSame(TreeNode *h1, TreeNode *h2)
{
    if (h1 == nullptr && h2 == nullptr)
        return true;
    if (h1 == nullptr || h2 == nullptr)
        return false;
    if (h1->name != h2->name)
        return false;
    if (isSame(h1->left, h2->right) && isSame(h1->right, h2->left) ||
        isSame(h1->left, h2->left) && isSame(h1->right, h2->right))
        return true;
    else
        return false;
}

int main()
{
    int n;
    cin >> n;
    vector<TreeNode> tree1(n);
    vector<bool> flag(n, true);
    string l, r;
    for (auto &t:tree1)
    {
        cin >> t.name >> l >> r;
        t.left_num = l == "-" ? -1 : atoi(l.c_str());
        if (t.left_num != -1)
            flag[t.left_num] = false;
        t.right_num = r == "-" ? -1 : atoi(r.c_str());
        if (t.right_num != -1)
            flag[t.right_num] = false;

    }
    for (auto &t:tree1)
    {
        t.left = t.left_num == -1 ? nullptr : &tree1[t.left_num];
        t.right = t.right_num == -1 ? nullptr : &tree1[t.right_num];
    }
    TreeNode *head1 = &tree1[find(begin(flag), end(flag), true) - begin(flag)];
    int m;
    cin >> m;
    if (m != n)
    {
        cout << "No";
        exit(0);
    }
    vector<TreeNode> tree2(m);
    flag = vector<bool>(m, true);
    for (auto &t:tree2)
    {
        cin >> t.name >> l >> r;
        t.left_num = l == "-" ? -1 : atoi(l.c_str());
        if (t.left_num != -1)
            flag[t.left_num] = false;
        t.right_num = r == "-" ? -1 : atoi(r.c_str());
        if (t.right_num != -1)
            flag[t.right_num] = false;
    }
    for (auto &t:tree2)
    {
        t.left = t.left_num == -1 ? nullptr : &tree2[t.left_num];
        t.right = t.right_num == -1 ? nullptr : &tree2[t.right_num];
    }
    TreeNode *head2 = &tree2[find(begin(flag), end(flag), true) - begin(flag)];
    if (isSame(head1, head2))
        cout << "Yes";
    else
        cout << "No";
}
