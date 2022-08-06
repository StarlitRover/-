/*7-23 还原二叉树 (25 分)
给定一棵二叉树的先序遍历序列和中序遍历序列，要求计算该二叉树的高度。

输入格式:
输入首先给出正整数N（≤50），为树中结点总数。下面两行先后给出先序和中序遍历序列，均是长度为N的不包含重复英文字母（区别大小写）的字符串。

输出格式:
输出为一个整数，即该二叉树的高度。

输入样例:
9
ABDFGHIEC
FDHGIBEAC
结尾无空行
输出样例:
5*/

#include <iostream>
#include <algorithm>

using namespace std;

int height(string &preorder, string &inorder)
{
    if (preorder.size() <= 2)  //两个节点以下的子树高度已定
        return preorder.size();
    char root = preorder[0];   //根据先序序列确定树根元素
    auto loc = find(inorder.begin(), inorder.end(), root); //根据已知根节点和中序序列确定根节点两边的所有节点
    int diff = loc - inorder.begin();
    string left_pre(preorder.begin() + 1, preorder.begin() + diff + 1), //【特别注意】用容器赋值时末尾的值[*(preorder.begin() + diff + 1)]会被舍弃
            left_in(inorder.begin(), loc),
            right_pre(preorder.begin() + diff + 1, preorder.end()),
            right_in(loc + 1, inorder.end());
    return max(height(left_pre, left_in), height(right_pre, right_in)) + 1; //进行递归
}

int main()
{
    int n;     //事实上不需要n(C可能需要)
    cin >> n;
    string pre, in;
    cin >> pre >> in;
    cout << height(pre, in);
}