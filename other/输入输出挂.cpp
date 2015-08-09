//cin 比 scanf 慢，scanf比getchar慢，同样cout慢于printf慢于putchar
#include <stdio.h>
typedef long long ll;
inline bool getint(int &num)
{
    bool flag = 0; num = 0;
    char ch = getchar();
    if(ch == EOF)return false;
    while(ch == ' ' || ch == '\n')ch = getchar();
    if(ch == '-') flag = 1, ch = getchar();
    while('0' <= ch && ch <= '9') num = num * 10 + ch - '0', ch = getchar();
    num =  flag ? -num : num;
    return true;
}
inline bool getll(ll &num)
{
    bool flag = 0; num = 0;
    char ch = getchar();
    if(ch == EOF)return false;
    while(ch == ' ' || ch == '\n')ch = getchar();
    if(ch == '-')flag = 1, ch = getchar();
    while('0' <= ch && ch <= '9') num = num * 10 + ch - '0', ch = getchar();
    num =  flag ? -num : num;
    return true;
}
inline bool getdouble(double &num)
{
    bool flag = 0;
    double _dec = 0.1;
    char ch = getchar();
    num = 0.0;
    if(ch == EOF)return false;
    while(ch == ' ' || ch == '\n')ch = getchar();
    if(ch == '-')flag = 1, ch = getchar();
    while('0' <= ch && ch <= '9')num = num * 10 + ch - '0', ch = getchar();
    if(ch == '.')
    {
        ch = getchar();
        while('0' <= ch && ch <= '9')num += _dec * (ch - '0'), _dec *= 0.1, ch = getchar();
    }
    num = flag ? -num : num;
    return true;
}

struct Tfai
{
    static const int buffer_sz = 17000000;
    char s[buffer_sz], *p;
    void build() {p = s; fread(s, 1, buffer_sz, stdin);}
    template<class Tsqy>
    inline void operator()(Tsqy &x)
    {
        bool ok = false;
        while(*p < 48 && *p != '-')++p;
        if(*p == '-')++p, ok = true;
        x = 0;
        while(47 < *p)x = x * 10 + *(p++) - 48;
        if(ok)x = -x;
    }
} scan;
template<class T>
inline void putint(T num)
{
    if(num < 0)putchar('-'), num = -num;
    if(num > 9)
        putint(num / 10);
    putchar(num % 10 + '0');
}
