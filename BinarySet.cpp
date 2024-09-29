#include <bits/stdc++.h>
using namespace std;
template < const size_t size >
class BitSet {
    private:
    class sub {
        public:
        sub(){}
        sub(size_t pos, unsigned int *dat) {
            p = pos;
            data = dat;
        }
        operator bool () {
            return (bool) ((data[p>>5]&(1<<(p&0x1f)))>>(p&0x1f));
        }
        void operator= (const bool v) {
            data[p>>5] = (data[p>>5]&~(1<<(p&0x1f)))|((unsigned int)v<<(p&0x1f));
        }
        private:
        size_t p;
        unsigned int *data;
    } res;
    unsigned int *data;
    public:
    BitSet() {
        data = new unsigned int[(size>>5)+1];
        memset(data, 0, sizeof(unsigned int[(size>>5)+1]));
    }
    sub &operator[] (const size_t p) {
        res = sub(p,data);
        return res;
    }
};
int main() {
    BitSet<1000000000000> a;
    for(int p = 0; p < 101; ++ p) {
        a[p] = true;
        for(int i = 0; i < 101; ++ i) {
            cout << a[i];
        }
        puts("");
    }
    return 0;
}
