#include <bits/stdc++.h>
#include "AVLTree.h"
#include "Treap.h"
#include "BinarySearch.h"
using namespace L_B__;
/*�������ݣ�һǧ���������or��������
 * ��һ�֣�insert����--������Treap(���������Ͼ�����¼�)>=<AVL>>BST--�������AVL>>Treap BSTֱ�ӱ���
 * �ڶ���: remove����--Treap��AVL����BST�ͱ�����
 * �����û�ü���չ���ıȽ��ˣ��ܽ����Treap��Ժ�дһ�㣬Ч�ʸ߲��߿�������
 *  ���о���Treap��ֱ�Ӵ����K���ֵ�������ƣ��Լ�����λ���Ҿ������ơ�
 *  ���ƣ�����treapÿ����㶼�����������������ļ�¼�����Կ��Ժܿ�Ĳ��ֵ��������������ֵ��
 * */
int main() {
    using namespace std;
    //Treap a;

    AVLTree a;
    Treap b; /*���ܲ���˵��������λȡֵ�Ѿ���������ʵ�֣�����ֵȡ��λ��δʵ��*/
    BinarySearch c;
    for(int i=1;i<2000;i++)
    {
        b.insert(i);
    }
    for(Treap::iterator it = b.begin();it != b.end();++it){
        printf("%d ",*it);
    }
    //for(int i=0;i<=1000;i++){
    //    b.insert(i);
    //}
    //printf("����\n");
    //b.inorder_print();
    //printf("\n����������ֵ");
    //for(int i=1;i<=1000;i++){
    //    printf("%d ",b.queryValue(i));
    //}
    //printf("\n����ֵ������");
    //for (int i = 1; i <= 1000; ++i) {
    //    printf("%d ",b.queryRank(i));
    //}
    //cout<<endl;
    //for(int i=1;i<=4;i++){
    //    b.insert(i);
    //}
    //printf("Insert:\n");
    //auto start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    b.insert(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    a.insert(x);
    //}
    //
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    c.insert(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //
    //
    //printf("remove\n");
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    b.remove(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    a.remove(x);
    //}

    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    c.(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //a.inorder_print();
    return 0;
   
}