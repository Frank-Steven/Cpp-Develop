#include <bits/stdc++.h>
using namespace std;
template <typename _Ty, typename Func>
constexpr void for_r(_Ty s, _Ty e, const Func &f) {
    _Ty i;
    if(s < e) {
        for(i = s; i <= e - 4; i += 4) {
            f(i);
            f(i + 1);
            f(i + 2);
            f(i + 3);
        }
        for(; i <= e; ++i) f(i);
    } else {
        for(i = s; i >= e + 4; i -= 4) {
            f(i);
            f(i - 1);
            f(i - 2);
            f(i - 3);
        }
        for(; i >= e; --i) f(i);
    }
}
int main() {
    timeb _t;
    ftime(&_t);
    int s = (long)_t.time*1000+_t.millitm;
    int ans = 0;
    for_r(1,20000,[&](int i) {
        for_r(1,20000,[&](int j) {
            ans += i*j;
        });
    });
    // for(int i = 1; i <= 20000; ++i) {
    //     for(int j = 1; j <= 20000; ++j) {
    //         ans += i*j;
    //     }
    // }
    ftime(&_t);
    cout << ans << endl;
    int e = (long)_t.time *1000 + _t.millitm;
    std::cerr << e-s << endl;
    return 0;
}