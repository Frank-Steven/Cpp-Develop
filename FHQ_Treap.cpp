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
	    cout << tmp << "--" << val << "-[" << seg << "]-(" << tag << ")-<" << size << ">----{" << pri << "}\n";
		if(ls) ls->print(lbase+"   ",lbase+"  |",0);
    }
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
};
template <typename S, typename L>
int get_size(node<S,L> *x) { return x?x->size:0; }
struct dat {
    int sum, siz;
    static dat merge(const dat &x, const dat &y) {
        return {x.sum+y.sum, x.siz+y.siz};
    }
    void apply(const dat &x) {
        sum += x.sum*siz;
    }
    friend ostream &operator<< (ostream &o, const dat &d) {
        return o<<d.sum, o;
    }
    bool operator<= (const dat &x) const {
        return tie(sum,siz)<=tie(x.sum,x.siz);
    }
};
int main() {
    
    return 0;
}