/*7-25 朋友圈 (25 分)
某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着一定相似的兴趣爱好，形成一个朋友圈。一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，如果A和B是朋友，且B和C是朋友，则A和C也是朋友。请编写程序计算最大朋友圈中有多少人。

输入格式:
输入的第一行包含两个正整数N（≤30000）和M（≤1000），分别代表学校的学生总数和俱乐部的个数。后面的M行每行按以下格式给出1个俱乐部的信息，其中学生从1~N编号：

第i个俱乐部的人数Mi（空格）学生1（空格）学生2 … 学生Mi

输出格式:
输出给出一个整数，表示在最大朋友圈中有多少人。

输入样例:
7 4
3 1 2 3
2 1 4
3 5 6 7
1 6

输出样例:
4*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

int find_root(int n, vector<int> &root)
{
    return n == root[n] ? n : (root[n] = find_root(root[n], root)); 
	//(root[n] = find_root(root[n], root)这一步使得在查找过程的同时更新root，从而减少下次查找的时间(root[n]会成为n最大的根节点)
}

int main()
{
    int n, m, k, tmp, max, maxr;
    cin >> n >> m;
    vector<int> size(n, 1), root(n);//size[n]:以n为根节点的子树下的节点个数;root[n]:n节点当前最大的根节点
    set<int> club; //记录一个社团中出现的所有根节点
    iota(root.begin(), root.end(), 0); //一开始让所有节点的根节点指向自己
    for (int i = 0; i < m; ++i)
    {
        max = 0;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            cin >> tmp;
            int _root = find_root(tmp - 1, root);
            club.insert(_root);
            if (max < size[_root])
            {
                max = size[_root];
                maxr = _root;
            }
        }
        for (auto &r: club) //该社团中最大的根节点吞并其他小的根节点
            if (r != maxr)
            {
                size[maxr] += size[r];
                root[r] = maxr;
            }
        club.clear();
    }
    cout << *max_element(size.begin(), size.end()) << endl;
}
