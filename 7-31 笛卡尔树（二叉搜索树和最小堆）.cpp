/*7-31 笛卡尔树 (25 分)
笛卡尔树是一种特殊的二叉树，其结点包含两个关键字K1和K2。首先笛卡尔树是关于K1的二叉搜索树，即结点左子树的所有K1值都比该结点的K1值小，右子树则大。其次所有结点的K2关键字满足优先队列（不妨设为最小堆）的顺序要求，即该结点的K2值比其子树中所有结点的K2值小。给定一棵二叉树，请判断该树是否笛卡尔树。

输入格式:
输入首先给出正整数N（≤1000），为树中结点的个数。随后N行，每行给出一个结点的信息，包括：结点的K1值、K2值、左孩子结点编号、右孩子结点编号。设结点从0~(N-1)顺序编号。若某结点不存在孩子结点，则该位置给出?1。

输出格式:
输出YES如果该树是一棵笛卡尔树；否则输出NO。

输入样例1:
6
8 27 5 1
9 40 -1 -1
10 20 0 3
12 21 -1 4
15 22 -1 -1
5 35 -1 -1

输出样例1:
YES

输入样例2:
6
8 27 5 1
9 40 -1 -1
10 20 0 3
12 11 -1 4
15 22 -1 -1
50 35 -1 -1
输出样例2:
NO*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<pair<int, int>> tree, son_nodes;  //pair真是个好东西，还可以用来模拟二叉树

//事实上二叉搜索树也可以通过中序遍历结果是个递增序列进行判断 
bool isBinarySearchTree(int node, bool isLeftNode, int threshold) //isLeftNode和threshold是为了防止左（右）子树的最大（小）节点比当前节点大（小）
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
        return false;  //注意【||】的优先级比【?:】的优先级高因此这里必须要加()
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