/*7-25 ����Ȧ (25 ��)
ĳѧУ��N��ѧ�����γ�M�����ֲ���ÿ�����ֲ����ѧ������һ�����Ƶ���Ȥ���ã��γ�һ������Ȧ��һ��ѧ������ͬʱ�������ɸ���ͬ�ľ��ֲ������ݡ��ҵ����ѵ�����Ҳ���ҵ����ѡ�������ۿ��Եó������A��B�����ѣ���B��C�����ѣ���A��CҲ�����ѡ����д��������������Ȧ���ж����ˡ�

�����ʽ:
����ĵ�һ�а�������������N����30000����M����1000�����ֱ����ѧУ��ѧ�������;��ֲ��ĸ����������M��ÿ�а����¸�ʽ����1�����ֲ�����Ϣ������ѧ����1~N��ţ�

��i�����ֲ�������Mi���ո�ѧ��1���ո�ѧ��2 �� ѧ��Mi

�����ʽ:
�������һ����������ʾ���������Ȧ���ж����ˡ�

��������:
7 4
3 1 2 3
2 1 4
3 5 6 7
1 6

�������:
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
	//(root[n] = find_root(root[n], root)��һ��ʹ���ڲ��ҹ��̵�ͬʱ����root���Ӷ������´β��ҵ�ʱ��(root[n]���Ϊn���ĸ��ڵ�)
}

int main()
{
    int n, m, k, tmp, max, maxr;
    cin >> n >> m;
    vector<int> size(n, 1), root(n);//size[n]:��nΪ���ڵ�������µĽڵ����;root[n]:n�ڵ㵱ǰ���ĸ��ڵ�
    set<int> club; //��¼һ�������г��ֵ����и��ڵ�
    iota(root.begin(), root.end(), 0); //һ��ʼ�����нڵ�ĸ��ڵ�ָ���Լ�
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
        for (auto &r: club) //�����������ĸ��ڵ��̲�����С�ĸ��ڵ�
            if (r != maxr)
            {
                size[maxr] += size[r];
                root[r] = maxr;
            }
        club.clear();
    }
    cout << *max_element(size.begin(), size.end()) << endl;
}
