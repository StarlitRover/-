/*7-23 ��ԭ������ (25 ��)
����һ�ö�����������������к�����������У�Ҫ�����ö������ĸ߶ȡ�

�����ʽ:
�������ȸ���������N����50����Ϊ���н�����������������Ⱥ�������������������У����ǳ���ΪN�Ĳ������ظ�Ӣ����ĸ�������Сд�����ַ�����

�����ʽ:
���Ϊһ�����������ö������ĸ߶ȡ�

��������:
9
ABDFGHIEC
FDHGIBEAC
��β�޿���
�������:
5*/

#include <iostream>
#include <algorithm>

using namespace std;

int height(string &preorder, string &inorder)
{
    if (preorder.size() <= 2)  //�����ڵ����µ������߶��Ѷ�
        return preorder.size();
    char root = preorder[0];   //������������ȷ������Ԫ��
    auto loc = find(inorder.begin(), inorder.end(), root); //������֪���ڵ����������ȷ�����ڵ����ߵ����нڵ�
    int diff = loc - inorder.begin();
    string left_pre(preorder.begin() + 1, preorder.begin() + diff + 1), //���ر�ע�⡿��������ֵʱĩβ��ֵ[*(preorder.begin() + diff + 1)]�ᱻ����
            left_in(inorder.begin(), loc),
            right_pre(preorder.begin() + diff + 1, preorder.end()),
            right_in(loc + 1, inorder.end());
    return max(height(left_pre, left_in), height(right_pre, right_in)) + 1; //���еݹ�
}

int main()
{
    int n;     //��ʵ�ϲ���Ҫn(C������Ҫ)
    cin >> n;
    string pre, in;
    cin >> pre >> in;
    cout << height(pre, in);
}