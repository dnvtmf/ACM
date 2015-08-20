///最大公约数gcd
/*$\gcd(a, b)$的性质
    $\gcd(0, 0) = 0, \gcd(a, b) = \gcd(b, a), \gcd(a, b) = \gcd(-a, b), \gcd(a, b) = \gcd(|a|, |b|), \gcd(a, 0) = |a|$
    $\gcd(a, ka) = |a|, (k \in Z), \gcd(a, b) = n\gcd(a, b), \gcd(a, \gcd(b, c)) = \gcd(\gcd(a, b), c)$
    gcd递归定理: $\gcd(a, b) = \gcd(b, a\% b)$
    最大公倍数$lcm(a, b) = \frac{ab}{\gcd(a, b)}$
    n个数的gcd和lcm, 记第i个数@$$a_i = \prod_{k=1}^{l}{p_k ^ {g_{ik}}} $$@, 则@$$\gcd(a_1, a_2, \cdots, a_n) = \prod_{k=1}^{l}{p_k^{\min{\{g_{1k}, g_{2k}, \cdots, g_{nk}}\}}}$$@, @$$lcm(a_1, a_2, \cdots, a_n) = \prod_{k=1}^{l}{p_k^{\max{\{g_{1k}, g_{2k}, \cdots, g_{nk}\}}}}$$@.
    一段区间[l, r]$(r = l \to n)$的gcd最多变化log次
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
//x的通解为x0 + b/gcd(a, b) * k
int solve(int a, int b, int c)
{
    int g = exgcd(a, b, x, y), t = b / g;
    if(c % g) return -1;//c % gcd(a, b) != 0无解
    int x0 = x * c / g;
    x0 = ((x0 % t) + t) % t;
    int y0 = (c - a * x0) / b;
    return x0;
}
//2. 求解a关于p的逆元
//

/*题目:
1.  给n个数, q个询问, 每个询问查询区间[l, r]中每个子区间的区间gcd之和, 即查询$\displaystyle \sum_{i=l}^{r}{ \sum_{j=i}^{r}{\gcd(a_i, a_{i+1}, \cdots , a_j)}}.( 1 \leq n , q \leq 10^4)$
    来源: 2015年多校第八场1002, hdu5381	 The sum of gcd
    标签: gcd, 莫队, ST, 二分
    做法: 由于以l为左端点的所有区间中, 它们的gcd最多变化$\log{a_l}$次, 并且gcd是递减的. 因此用ST表预处理, 可以在$O(1)$时间内求出任意区间的gcd, 然后用二分求出对于每个左端点l和每个右端点r, 找出每种gcd的范围, 这样就可以在$\log{N}$时间内求出任意以l为左端点, 或以r为右端点, 到某位置的所有gcd之和, 即$\sum_{i=l}^{r}{\gcd(a_l, a_{l+1}, \cdots, a_i}$, 最后离线询问, 用莫队求解. 时间复杂度: $O(N \log^2{N})$.
*/
