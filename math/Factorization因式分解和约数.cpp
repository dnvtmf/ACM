///因式分解Factorization
///唯一分解理论
/*
所有正整数N皆可表示为素数之积, 即$\displaystyle N = \prod_{i = 1}^{m}{p_i ^ {k_i}, p_i}$是素数.
因子的性质:
	1. 因子个数函数$\tau$定义为正整数n的所有正因子个数, 记为$\tau(n)$, 则$\displaystyle \tau(n) = \prod_{i=0}^{m}{(k_i + 1)}$
	2. 因子和函数$\sigma$定义为整数n的所有正因子之和, 记为$\sigma(n)$, 则$\displaystyle \sigma(n) = \prod_{i=1}^{m}{\frac{p_i^{k_i + 1} - 1}{p_i - 1}}$
	3. 因子的k次方的和为: $\displaystyle \sum_{d|n}{d^k} = \prod_{i=1}^{m}{\sum_{j=0}^{k_i}{p_i^j}}$
	4. 因子和函数$\sigma$和因子个数函数$\tau$是乘性函数.
	5. 设$\displaystyle a = \prod_{i=1}^{m}{p_i^{x_i}}, b = \prod_{i=1}^{m}{p_i^{y_i}}$, 则@$$
	\gcd(a, b) = \prod_{i=1}^{m}{\min{(x_i, y_i)}}$$@, @$$
	lcm(a, b) = \prod_{i=1}^{m}{\max{(x_i, y_i)}}
	$$@
	6. 质因数个数: 10^5以内的数质因数至多7个, 10^6以内的数的质因数至多8个, 10^9以内的数的质因数至多10个
*/
///分解质因数
//暴力试除法, $O(\sqrt{N})$
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
LL qmult(LL a, LL b, LL mod)
{
    a %= mod;
    b %= mod;
    LL res = 0;
    while(b)
    {
        if(b & 1) if((res += a) >= mod) res -= mod;
        if((a <<= 1) >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}
inline LL gcd(LL a, LL b)
{
    while(b) {swap(b, a = a % b);}
    if(a >= 0) return a;
    else return -a;
}

LL Pollard_rho(LL n, LL c)
{
    LL i = 1, k = 2;
    LL x = rand() % n;//0 ~ n - 1
    LL y = x;
    while(1)
    {
        //x = (qmult(x, x, n) + n - 1) % n;
        x = (x * x + c) % n;
        LL d = gcd(y - x, n);
        if(d != 1 && d != n) return d;
        if(y == x) return n;
        if(++i == k) y = x, k += k;
    }
}
//对n进行素因子分解
long long factor[110];//乱序返回
int factor_num;
void FindFactor(LL n)
{
    if(n == 0) return ;
    if(Miller_Rabin(n))//测试n是否是素数
    {
        factor[factor_num++] = n;
        return ;
    }
    LL p = n;
    int c = 107;//一般取107左右
    while(p >= n) p = Pollard_rho(p, c--);//值变化, 防止死循环
    FindFactor(p);
    FindFactor(n / p);
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
