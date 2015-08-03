///最大公约数gcd
/*$\gcd(a, b)$的性质
 $\gcd(0, 0) = 0, \gcd(a, b) = \gcd(b, a), \gcd(a, b) = \gcd(-a, b), \gcd(a, b) = \gcd(|a|, |b|), \gcd(a, 0) = |a|$
 $\gcd(a, ka) = |a|, (k \in Z), \gcd(a, b) = n\gcd(a, b), \gcd(a, \gcd(b, c)) = \gcd(\gcd(a, b), c)$
 gcd递归定理: $\gcd(a, b) = \gcd(b, a\% b)$
 最大公倍数$lcm(a, b) = \frac{ab}{\gcd(a, b)}$
 */
//欧几里得算法$O(\log{n})$
//递归
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
//循环
int gcd(int a, int b)
{
    int t;
    while(b) t = a % b, a = b, b = t;
    return a;
}
//小数的gcd
//EPS控制精度
double fgcd(double a, double b)
{
    if(-EPS < b && b < EPS) return a;
    return fgcd(b, fmod(a, b));
}
///扩展欧几里得算法
void exgcd(int a, int b, int &g, int &x, int &y)
{
    if(b) exgcd(b, a % b, g, y, x), y -= a / b * x;
    else x = 1, y = 0, g = a;
}
//应用
//1. 求解ax + by = c的x的最小正整数解
int solve(int a, int b, int c)
{
    int g = exgcd(a, b, x, y), t = b / g;
    if(c % g) return -1;//c % gcd(a, b) != 0无解
    int x0 = x * c / g;
    x0 = ((x0 % t) + t) % t;
    int y0 = c - a * x0;
    return x0;
}
//2. 求解a关于p的逆元
//
