#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct _pointer {
    T *val = NULL;
    constexpr operator void* () const noexcept { return val; }
    T &operator[] (const size_t &_Pos) const noexcept { return val[_Pos]; }
    _pointer(T *_Src) noexcept { val = _Src; }
    _pointer() noexcept {}
    ~_pointer() { delete[] val; }
    template <typename _Ty> T *operator+ (const _Ty _Val) const { return val+_Val; }
    template <typename _Ty> T *operator- (const _Ty _Val) const { return val-_Val; }
    _pointer &operator= (T *_Src) { val = _Src; return *this; }
};
struct sized_string {
    _pointer<char> _M_arr = NULL;
    size_t _M_size;
    sized_string() {
	    _M_size = 0;
	    _M_arr = new char[_M_size+1];
        _M_arr[0] = '\0';
	} 
    sized_string(const size_t &_Size) noexcept : _M_size(_Size) {
        _M_arr = new char[_M_size+1];
        _M_arr[0] = '\0';
    }
    sized_string(const size_t &_Size, const sized_string &_Src) noexcept : _M_size(_Size) {
        _M_arr = new char[_M_size+1];
        memcpy(_M_arr, _Src._M_arr, _Src._M_size+1);
    }
    sized_string(const sized_string &_Src) noexcept : _M_size(_Src._M_size) {
        _M_arr = new char[_M_size+1];
        memcpy(_M_arr, _Src._M_arr, _Src._M_size+1);
    }
    sized_string &operator= (const sized_string &_Src) noexcept {
        _M_size = _Src._M_size;
        _M_arr = new char[_M_size+1];
        memcpy(_M_arr, _Src._M_arr, _Src._M_size+1);
        return *this;
    }
    sized_string(const size_t &_Size, const char *_Src) noexcept : _M_size(_Size) {
        _M_arr = new char[_M_size+1];
        memcpy(_M_arr, _Src, strlen(_Src)+1);
    }
    sized_string(const size_t &_Size, const char &_Src) noexcept : _M_size(_Size) {
        _M_arr = new char[_M_size+1];
        memset(_M_arr, _Src, _M_size+1);
    }
    sized_string(const char &_Src) noexcept : _M_size(1) {
        _M_arr = new char[2]{ _Src, '\0' };
    }
    sized_string(const char *_Src) noexcept : _M_size(strlen(_Src)) {
        _M_arr = new char[_M_size+1];
        memcpy(_M_arr, _Src, _M_size+1);
    }
    sized_string(const string &_Src) noexcept : _M_size(_Src.length()) {
        _M_arr = new char[_M_size+1];
        for(size_t i = 0; i < _M_size; ++i) _M_arr[i] = _Src[i];
    }
    sized_string operator+ (const sized_string &_Src) const noexcept {
        sized_string _res(_M_size+_Src._M_size, *this);
        memcpy(_res._M_arr+_M_size, _Src._M_arr, _Src._M_size+1);
        return _res;
    }
    template <typename _Ty>
    friend sized_string operator+ (const _Ty &_L_Src, const sized_string &_R_Src) noexcept {
        return sized_string(_L_Src) + _R_Src;
    }
    friend sized_string operator+ (const char* _L_Src, const sized_string &_R_Src) noexcept {
        return sized_string(strlen(_L_Src), _L_Src) + _R_Src;
    }
    char &operator[] (const size_t &_Pos) const noexcept { return _M_arr[_Pos]; }
    friend ostream &operator<< (ostream &_out, const sized_string &_Src) noexcept {
        for(size_t i = 0; i < _Src._M_size; ++i) _out << _Src._M_arr[i];
        return _out;
    }
    friend istream &operator>> (istream &_in, sized_string &_Src) noexcept {
        string _tmp;
        _in >> _tmp;
        _Src = sized_string(_tmp);
        return _in;
    }
    template <typename _Ty>
    sized_string &operator+= (const _Ty &_Src) noexcept {
        return *this = *this + _Src;
    }
    sized_string &operator+= (const char *_Src) noexcept {
        return *this = *this + _Src;
    }
    constexpr size_t size() const noexcept { return _M_size; }
};
int main() {
    sized_string a="114514", b = "91919810";
    cout << " "+a+b << endl;
    cout << a+b[3] << endl;
    cout << b[3]+a << endl;
    a[2] = 'e';
    cout << a << endl;
    return 0;
}