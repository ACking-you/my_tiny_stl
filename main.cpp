#include <bits/stdc++.h>


using namespace std;
//
// Created by L_B__ on 2021/11/25.
//
/*
 * �й�˵������ȫʹ�õ�java1.7������ʵ�ַ���
 * ��������ʱ��û��ʵ�ֵ������������޷����ⲿ���ű���������
 * ʵ����ʵ�ֵ�����Ҳ���ѣ�����ͨ��ʵ��һ������������һ���ڲ��ĵ�������
 * ���һ���������࣬��C++����һ����һ���ڲ���װ�࣬Ȼ��ʵ��next�������ɣ�ʵ�ʱ���Ϊ�����������
 * �������������������������Ƶ�������������ϴ�Ķ������ģ������ݲ����
 * */
#include <functional>
#include <utility>
#include <cassert>
#ifndef MY_TINY_STL_UNORDERED_MAP_H
#define MY_TINY_STL_UNORDERED_MAP_H
namespace L_B__{
    template<typename K,typename V,typename H = std::hash<K>>
    class unordered_map {
/*��������*/
    private:
        typedef K key_t;
        typedef V val_t;
        typedef H hash_t;   //��Ӧ�Ĺ�ϣģ������
    public: struct node{//�����ڵ�
            key_t key;
            val_t val;
            node* next;
            node():key(0),val(0),next(nullptr){}
            node(key_t key,val_t val):key(key),val(val),next(nullptr){}
        };
        const float factor = 0.75f;//װ������
/*���ݶ���*/
    public:
        size_t cnt;             //�Ѿ�����ļ�ֵ����Ŀ
        size_t capacity;         //��ǰ�������
        node** map;              //һ����ϣ�����׵�ַ

/*���캯��ʵ��*/
    public:
        /*default construct*/
        unordered_map():cnt(0),capacity(64),map(nullptr)//Ĭ��cap��������Ϊ16
        {
            map = new node*[capacity];
            for(int i=0;i<capacity;i++){
                map[i] = nullptr;
            }
        }
        /*copy construct*/
        unordered_map(unordered_map& src):cnt(src.cnt),capacity(src.capacity),map(nullptr){
            assert(capacity>0);
            map = new node*[capacity];
            copy_map(map,src.map);//ί��ʵ�����
        }
        /*move construct*/
        unordered_map(unordered_map&& src):cnt(src.cnt),capacity(src.capacity),map(src.map){
            assert(capacity>0&&map!= nullptr);
            //�Ѿ��ɹ������ڴ�ת�ƣ�������ֻ��Ҫ��ԭsrc��map��ֵΪnullptr��ɷ�ֹ�����������������ڴ�
            src.map = nullptr;
        }
        /*destruct*/
        ~unordered_map(){
            destroy();
        }

/*���еĶ��⹦��ʵ��*/
    public:
        void put(key_t key,val_t val){
            if(cnt>=factor*capacity)resize();
            putVal(key,val);
        }
        void insert(node* src){
            assert(src!= nullptr);//�������Ѿ������ڴ�
            size_t index = getIndex(src->key);
            if(map[index]== nullptr){
                src->next = nullptr;
                map[index] = src;
            }else{
                src->next = map[index];
                map[index] = src;
            }
            cnt++;
        }
        void insert(std::pair<key_t,val_t> src){//ͨ����紫��pairʵ�ּ�ֵ�Դ���
            put(src.first,src.second);
        }
        val_t& get(key_t key){//�������get��ʱ��ͱ�����ڣ�����ᱻ����
            val_t * ret = getVal(key);
            assert(ret != nullptr);
            return *ret;
        }
        bool count(key_t key){
            return getVal(key) != nullptr;
        }
        void clear(){
            if(cnt == 0)
                return;
            assert(map!= nullptr);
            for(int i=0;i<capacity;i++){
                if(map[i] != nullptr)
                    del_nodes(map[i]);
                map[i] = nullptr;
            }
            cnt = 0;//��չ�ϣ������������������
        }
        size_t & size(){
            return cnt;
        }
/*������������ò���*/
    public:
        val_t& operator[](key_t key){
            val_t * val = getVal(key);
            if(val== nullptr)//����STL��ƽʱʹ��ϰ�ߣ����������key���򴴽�һƬ�ռ�洢��Ӧ��0��ֵ��
                put(key,val_t(0));
            else return *val;
            return get(key);
        }
        //������ֵ�ĸ�ֵ�����
        unordered_map& operator=(unordered_map& src){
            assert(src.map!= nullptr&&src.capacity>0);
            destroy();
            capacity = src.capacity;
            cnt = src.cnt;
            map = new node*[capacity];
            copy_map(map,src.map);
            return *this;
        }
        //������ֵ�ĸ�ֵ�����
        unordered_map& operator=(unordered_map&& src){
            destroy();
            map = src.map;
            cnt = src.cnt;
            capacity = src.capacity;

            src.map = nullptr;
            return *this;
        }
/*����Ҫ�������ĺ���*/
    public:static void del_nodes(node* src){//�ͷŵ�����
            assert(src!= nullptr);
            node *pre;
            node *cur = src;
            while (cur != nullptr) {
                pre = cur;
                cur = cur->next;
                delete pre;
            }
        }


/*һЩ�����⿪�ŵ��ڲ�ί�к���*/
    private:
        val_t * getVal(key_t key){//ͨ��getval����
            size_t index = getIndex(key);
            node* p = map[index];
            while (p!= nullptr){
                if(p->key == key)
                    return &(p->val);
                p = p->next;
            }
            return nullptr;
        }

        size_t getIndex(key_t key){
            hash_t to_hash;
            size_t code = to_hash(key);//�ö�Ӧ�Ĺ�ϣ�º����ó�hashcode
            code = code ^(code>>16);//�Ŷ�����
            return code&(capacity-1);//�����뷽ʽ�ó��±�
        }
        void putVal(key_t key,key_t val){
            size_t index = getIndex(key);
            node* tmp = map[index];
            if(tmp== nullptr){//��ǰλ��Ϊ��
                map[index] = new node(key,val);
                cnt++;
                return;
            }
            while (tmp != nullptr){
                if(tmp->key==key){//�Ѿ�����key����val���и���
                    tmp->val = val;
                    return ;
                }
                tmp = tmp->next;
            }
            //��������������ڶ�Ӧ��key����ֱ��ͷ��
            node* p = new node(key,val);
            p->next = map[index];
            map[index] = p;
            cnt++;
        }

        void resize(){//ע��ÿ��resize��Ҫrehash
            capacity <<= 1;//��������
            node** tmp = map;
            map = new node*[capacity];
            std::fill(map,map+capacity, nullptr);//C++14����ָ���޷���ʼ��Ϊ0����ҪΪnullptr
            rehash(tmp);
            delete []tmp;
        }

        void rehash(node** preTable){
            cnt = 0; //����insert�����°�size������
            assert(preTable!= nullptr);
            size_t preSize = capacity >> 1;
            for (size_t i = 0; i < preSize; ++i) {
                if(preTable[i] != nullptr){
                    node *preNode;
                    node *curNode = preTable[i];
                    while (curNode != nullptr) {
                        preNode = curNode;
                        curNode = curNode->next;
                        insert(preNode);
                    }
                }
            }
        }

        void destroy(){
            if(map == nullptr)//�����Ѿ��������
                return;
            for (size_t i = 0; i < capacity; i++) {
                if (map[i] != nullptr)
                    del_nodes(map[i]);
                map[i] = nullptr;
            }
            delete[] map;
            map = nullptr;
        }

        void copy_map(node** _dest,node** _src){
            assert(_dest!= nullptr&&_src!= nullptr);
            for(size_t i=0;i<capacity;i++){
                _dest[i] = nullptr;
                if(_src[i] != nullptr){
                    node* head = _src[i];
                    _dest[i] = new node(head->key,head->val);
                    node* p = _dest[i];
                    while (head != nullptr){
                        head = head->next;
                        if(head != nullptr){
                            p->next = new node(head->key,head->val);
                            p = p->next;
                        }
                    }
                }
            }
        }
    };
}


#endif //MY_TINY_STL_UNORDERED_MAP_H


L_B__::unordered_map<int,int> get_map(){
    return L_B__::unordered_map<int,int>();
}
int main() {
    auto check = get_map();
    L_B__::unordered_map<int,int> che;
    che = check;
    cout<<che[322343];
}