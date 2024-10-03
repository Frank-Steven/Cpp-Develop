#include <bits/stdc++.h>
using namespace std;
template <typename S, typename L>
struct node {
    int pri, size;
    S seg, val; L tag;
    node *ls = NULL, *rs = NULL;
    void release() {
        if(ls) ls->recieve(tag);
        if(rs) rs->recieve(tag);
        tag = L();
    }
    void recieve(const L &v) {
        seg.apply(v); val.apply(v);
        tag = L::merge(tag,v);
    }
    void flush() {
        seg = val, size = 1;
        if(ls) seg = S::merge(ls->seg,seg), size += ls->size;
        if(rs) seg = S::merge(seg,rs->seg), size += rs->size;
    }
    static node *merge(node *l, node *r) {
        if(!l || !r) return (l?l:r);
        if(l->pri > r->pri) {
            l->rs = merge(l->rs,r);
            return l->flush(), l;
        } else {
            r->ls = merge(l,r->ls);
            return r->flush(), r;
        }
    }
    void print(string lbase = "", string rbase = "", bool r = 0) {
    	string tmp;
        if(lbase.size() == 0) tmp = "";
    	else if(r) tmp = rbase, tmp[tmp.size()-1] = '/';
		else tmp = lbase, tmp[tmp.size()-1] = '\\';
		if(rs) rs->print(rbase+"  |",rbase+"   ",1);
	    cout << tmp << "--" << val << "-[" << seg << "]-(" << tag << ")-<" << size << ">-{" << pri << "}\n";
		if(ls) ls->print(lbase+"   ",lbase+"  |",0);
    }
    static void Print(node *x) { if(x) x->print(); }
    node(const S &x) : pri(rand()), size(1), val(x), tag() { flush(); }
    void modify(int s, int e, const L &v, int _begin = 1) {
        if(s <= _begin && size <= e-_begin+1) { recieve(v); return; }
        release();
        if(ls && s <= get_size(ls)) ls->modify(s,e,v,_begin);
        if(s <= _begin+get_size(ls) && _begin+get_size(ls) <= e) val.apply(v);
        if(rs && e >= _begin+get_size(ls)+1) rs->modify(s,e,v,_begin+get_size(ls)+1);
        flush();
    }
    S query(int s, int e, int _begin = 1) {
        if(s <= _begin && size <= e-_begin+1) return seg;
        release();
        if(ls && s <= get_size(ls) && e > _begin+get_size(ls))
            return S::merge(S::merge(ls->query(s,e,_begin),val),rs->query(s,e,_begin+get_size(ls)));
        if(s <= get_size(ls)) return ls->query(s,e,_begin);
        if(rs && e >= _begin+get_size(ls)+1) return rs->query(s,e,_begin+get_size(ls)+1);
    }
    pair<node*,node*> split(const S &v) {
        release();
        if(val <= v) {
            auto split = ls ? ls->split(v) : pair<node*,node*>{NULL,NULL};
            ls = split.second; flush();
            return {split.first, this};
        } else {
            auto split = rs ? rs->split(v) : pair<node*,node*>{NULL,NULL};
            rs = split.first; flush();
            return {this, split.second};
        }
        throw("ERR");
    }
    pair<node*,node*> split(int k) {
        release();
        if(k <= get_size(ls)) {
            auto split = ls->split(k);  
            ls = split.second; flush();
            return {split.first, this};
        } else if(k > get_size(ls) + 1) {
            auto split = rs->split(k-get_size(ls)-1);
            rs = split.first; flush();
            return {this, split.second};
        } else {
            return {this, NULL};
        }
        throw("ERR");
    }
};
template <typename S, typename L>
int get_size(node<S,L> *x) { return x?x->size:0; }
    struct tag {
        int a, b;
        tag() : a(0), b(0) {}
        tag(int _a, int _b) : a(_a), b(_b) {}
        static tag merge(const tag &l, const tag &r) { return tag(l.a+r.a,l.b+r.b); }
    };
        struct seg {
        int a, b;
        seg() : a(0), b(0) {}
        seg(int _a, int _b) : a(_a), b(_b) {}
        void apply(const tag &v) { a += v.a, b += v.b; }
        static seg merge(const seg &l, const seg &r) { return seg(l.a + r.a, l.b + r.b); }
    
        // 重写比较操作符
        bool operator==(const seg &r) const { return a == r.a && b == r.b; }
        bool operator!=(const seg &r) const { return !(*this == r); }
        bool operator<(const seg &r) const { return a < r.a || (a == r.a && b < r.b); }
        bool operator<=(const seg &r) const { return *this < r || *this == r; }
        bool operator>(const seg &r) const { return !(*this <= r); }
        bool operator>=(const seg &r) const { return !(*this < r); }
    };
    ostream& operator<<(ostream& os, const seg& s) { return os << "(" << s.a << "," << s.b << ")"; }
    ostream& operator<<(ostream& os, const tag& t) { return os << "(" << t.a << "," << t.b << ")"; }
int main() {
    // 创建一个空树
    node<seg, tag>* root = NULL;

    // 插入节点
    root = node<seg, tag>::merge(root, new node<seg, tag>(seg(1, 2)));
    root = node<seg, tag>::merge(root, new node<seg, tag>(seg(3, 4)));
    root = node<seg, tag>::merge(root, new node<seg, tag>(seg(5, 6)));
    root = node<seg, tag>::merge(root, new node<seg, tag>(seg(7, 8)));

    // 初始打印树的结构
    cout << "Initial tree structure:\n";
    node<seg, tag>::Print(root);  // 使用静态Print方法安全打印树结构

    // 修改节点的值
    cout << "\nAfter modifying range (1, 3) with tag (1, 2):\n";
    root->modify(1, 3, tag(1, 2));
    node<seg, tag>::Print(root);  // 再次打印树结构以查看修改后的状态

    cout << "\nAfter modifying range (2, 4) with tag (3, 4):\n";
    root->modify(2, 4, tag(3, 4));
    node<seg, tag>::Print(root);  // 再次打印树结构以查看修改后的状态

    // 分割树
    cout << "\nSplitting tree at position 3:\n";
    auto split1 = root->split(3);
    cout << "Tree after split:\n";
    node<seg, tag>::Print(root);  // 打印主树结构
    cout << "\nFirst split tree:\n";
    node<seg, tag>::Print(split1.first);  // 打印第一部分
    cout << "\nSecond split tree:\n";
    node<seg, tag>::Print(split1.second);  // 打印第二部分

    // 进一步分割第一部分
    cout << "\nSplitting first part at value (2, 3):\n";
    auto split2 = split1.first->split({2, 3});
    cout << "First split part after further split:\n";
    node<seg, tag>::Print(split1.first);  // 打印分割后的第一部分
    cout << "\nFirst part of split2:\n";
    node<seg, tag>::Print(split2.first);  // 打印第二次分割的第一部分
    cout << "\nSecond part of split2:\n";
    node<seg, tag>::Print(split2.second);  // 打印第二次分割的第二部分

    // 合并分割后的部分
    cout << "\nMerging split2 parts back:\n";
    root = node<seg, tag>::merge(split2.first, split2.second);
    node<seg, tag>::Print(root);  // 打印最终合并后的树结构

    // 释放内存（根据实际情况，可能需要添加释放内存的逻辑，防止内存泄漏）

    return 0;
}
