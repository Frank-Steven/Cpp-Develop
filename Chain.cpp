#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Chain {
    template <typename N>
    class Mgr {
    public:
        int tot, p; N *head, *tail, *cur;
        Mgr() {
            head = new N(this);
            tail = new N(this);
            tail->prev = head;
            head->next = tail;
            tot = 0, p = -1, cur = head;
        }
        ~Mgr() {
            while (head->next) {
                head = head->next;
                delete head->prev;
            }
            delete head;
        }
        N* get_node(const int &pos) {
            while (pos >= tot) tail->prev->insert(T());
            const int& disHead = pos + 1;
            const int& disTail = tot - pos - 1;
            const int& disCur = abs(pos - p);
            if (disCur > disHead || disCur > disTail) {
                if (disHead < disTail) p = -1, cur = head;
                else p = tot, cur = tail;
            }
            while (pos < p) p--, cur = cur->prev;
            while (pos > p) p++, cur = cur->next;
            return cur;
        }
        class NodeProxy {
        private: N* node;
        public:
            NodeProxy(N* _node) : node(_node) {}
            T* operator->() { return &(node->data); }
            T& operator*() { return node->data; }
            &operator T() { return node->data; }
            void operator= (const T &_data) { node->data = _data; }
            void insert(const T &_M_data) { node->insert(_M_data); }
            void remove() { node->remove(); }
        };
        NodeProxy operator[](const int &pos) { return NodeProxy(get_node(pos)); }
    };
    class Node {
    public:
        Node *prev, *next; T data; Mgr<Node> *from;
        Node(){} Node(Mgr<Node> *_from):prev(nullptr), next(nullptr), from(_from) {}
        void insert(const T &_data) {
            from->tot++;
            Node *p = new Node(from);
            p->data = _data;
            p->prev = this;
            p->next = next;
            next->prev = p;
            next = p;
        }
        void remove() {
            from->tot--;
            from->p--;
            from->cur = prev;
            prev->next = next;
            next->prev = prev;
            delete this;
        }
    };
    Mgr<Node> data;
public:
    Chain() {}
    int size() { return data.tot; }
    auto operator[](const int &pos) { return data[pos]; }
};

struct node {
    int x, y;
};

int main() {
    Chain<node> c;
    c[10]->y = 9;          // 修改第10个元素的y值
    cout << c[10]->x << " " << c[10]->y << endl; // 输出第10个元素的x和y值
    
    c[9].insert({2, 28}); // 在第9项后插入新的元素
    cout << c[10]->x << " " << c[10]->y << endl; // 输出插入后的第10个元素的x和y值

    c[10].remove();       // 删除第10项
    cout << c[10]->x << " " << c[10]->y << endl; // 输出删除后的第10个元素的x和y值

    Chain<int> ch;
    ch[10] = 100;
    cout << ch[10] << '\n';
    ch[9].insert(10);
    cout << (ch[11]>ch[10]?"great\n":"small\n");
    cout << ch[10] << '\n';
    ch[10].remove();
    cout << ch[10] << '\n';
    return 0;
}
