///因式分解Factorization
///唯一分解理论
/*
所有正整数N皆可表示为素数之积, 即$\displaystyle N = \prod_{i = 1}^{m}{p_i ^ {k_i}, p_i}$是素数.
因子的性质:
	1. 因子个数函数$\tau$定义为正整数n的所有正因子个数, 记为$\tau(n)$, 则$\displaystyle \tau(n) = \prod_{i=0}^{m}{(k_i + 1)}$
	2. 因子和函数$\sigma$定义为整数n的所有正因子之和, 记为$\sigma(n)$, 则$\displaystyle \sigma(n) = \prod_{i=1}^{m}{\frac{p_i^{k_i + 1} - 1}{p_i - 1}}$
	3. 因子和函数$\sigma$和因子个数函数$\tau$是乘性函数.
	4. 设$\displaystyle a = \prod_{i=1}^{m}{p_i^{x_i}}, b = \prod_{i=1}^{m}{p_i^{y_i}}$, 则@$$
	\gcd(a, b) = \prod_{i=1}^{m}{\min{(x_i, y_i)}}$$@, @$$
	lcm(a, b) = \prod_{i=1}^{m}{\max{(x_i, y_i)}}
	$$@
	5. 质因数个数: 10^5以内的数质因数至多7个, 10^6以内的数的质因数至多8个, 10^9以内的数的质因数至多10个
*/
///分解质因数
//暴力试除法, $O(\sqrt(N))$
int prim[NUM], tot;//素数表
vector<P> FAC(int n)
{
    vector<P> fac;
    fac.clear();
    for(int i = 0; i < tot && prim[i] * prim[i] <= n; ++i)
    {
        if(n % prim[i]) continue;
        int cnt = 0;
        while(n % prim[i] == 0)
        {
            ++cnt;
            n /= prim[i];
        }
        fac.push_back(P(prim[i], cnt));
    }
    if(n > 1) fac.push_back(P(n, 1));
    return fac;
}

int facs[NUM];
int find_fac(int n)
{
    int cnt = 0;
    for(int i = 2; i * i <= n; i += 2)
    {
        while(!(n % i))
        {
            n /= i;
            facs[cnt++] = i;
        }
        if(i == 2) --i;
    }
    if(n > 1) facs[cnt++] = n;
    return cnt;
}
///预处理1~n间所有数的约数 $O(n\log{n})$
vector<int> facs[NUM];
int prim[NUM], tot;
void pre_fac()
{
    for(int i = 2; i < NUM; ++i)
    {
        if(prim[i]) continue;
        prim[tot++] = i;
        facs[i].push_back(i);
        for(int j = i + i; j < NUM; j += i)
        {
            prim[j] = 1;
            facs[j].push_back(i);
        }
    }
}
///pollard_rho启发式方法 $O(\sqrt[4]{n})$
//对较大的数整数进行分解
/*
选取[2, n - 1]间的随机数, 通过随机函数$x = (x ^ 2 + c) \% n$, 如果序列出现循环, 则退出; 否则计算$p = \gcd(x_{i-1}, x_i)$, 如果p = 1, 则继续直到p > 1为止, 若p = n, 则n是素数, 否则p是n的一个约数, 并递归分解p和n/p.
当p为素数用pollard_rho较为耗时, 所以可以先用miller_rabin判断p是否为素数.

*/
LL factor[100];//质因数分解结果(刚返回时是无序的)
int tol;//质因数的个数. 数组小标从0开始
LL mult_mod(LL a, LL b, LL c)
{
    a %= c;
    b %= c;
    LL ret = 0;
    while(b)
    {
        if(b & 1) {ret += a; ret %= c;}
        a <<= 1;
        if(a >= c)a %= c;
        b >>= 1;
    }
    return ret;
}
LL gcd(LL a, LL b)
{
    if(a == 0)return 1;
    if(a < 0) return gcd(-a, b);
    while(b)
    {
        LL t = a % b;
        a = b;
        b = t;
    }
    return a;
}

LL Pollard_rho(LL x, LL c)
{
    LL i = 1, k = 2;
    LL x0 = rand() % x;
    LL y = x0;
    while(1)
    {
        i++;
        x0 = (mult_mod(x0, x0, x) + c) % x;
        LL d = gcd(y - x0, x);
        if(d != 1 && d != x) return d;
        if(y == x0) return x;
        if(i == k) {y = x0; k += k;}
    }
}
//对n进行素因子分解
void findfac(LL n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++] = n;
        return;
    }
    LL p = n;
    while(p >= n)p = Pollard_rho(p, rand() % (n - 1) + 1);
    findfac(p);
    findfac(n / p);
}


//枚举约数 $O(\sqrt{n})$
void DIV(int n)
{
    vector<int> d;
    int i;
    for(i = 1; i * i < n; ++i)
        if(n % i == 0)
        {
            d.push_back(i);
            d.push_back(n / i);
        }
    if(i * i == n) d.push_back(i);
}
