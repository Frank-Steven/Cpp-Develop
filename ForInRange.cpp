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
    for_r(1,10,[&](int i) {
        for_r(1,10,[&](int j) {
            cout << i*j << " ";
        });
        cout << "\n";
    });
    return 0;
}