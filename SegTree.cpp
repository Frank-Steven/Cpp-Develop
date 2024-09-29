#include <bits/stdc++.h>
using namespace std;
template <typename Seg, typename Tag>
struct SegTree {
    Seg seg; Tag tag = Tag();
    int l, r, mid;
    SegTree *ls = NULL, *rs = NULL;
    template <typename Func>
    SegTree(int s, int e, const Func &init):
      l(s), r(e), mid(l+r>>1) {
        if(l == r) { seg = init(l); return; }
        ls = new SegTree(l,mid,init);
        rs = new SegTree(mid+1,r,init);
        seg = Seg::merge(ls->seg,rs->seg);
    }
    constexpr void release() {
        if(ls) ls->recieve(tag);
        if(rs) rs->recieve(tag);
        tag = Tag();
    }
    constexpr void recieve(const Tag &x) {
        seg.apply(x);
        tag = Tag::merge(tag,x);
    }
    void modify(int s, int e, const Tag &x) {
        if(s <= l && r <= e) { recieve(x); return; }
        release();
        if(s <= mid) ls->modify(s,e,x);
        if(e >  mid) rs->modify(s,e,x);
        seg = Seg::merge(ls->seg,rs->seg);
    }
    Seg query(int s, int e) {
        if(s <= l && r <= e) return seg;
        release();
        if(e <= mid) return ls->query(s,e);
        if(s >  mid) return rs->query(s,e);
        return Seg::merge(ls->query(s,e),rs->query(s,e));
    }
};
int main() {
    return 0;
}