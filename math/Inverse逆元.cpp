///逆元inverse
//定义：如果$a \cdot b \equiv 1 (\% MOD)$, 则b 是a的逆元(模逆元， 乘法逆元）
//a的逆元存在条件：gcd(a, MOD) == 1
//性质：逆元是积性函数，如果$c = a \cdot b$, 则 $inv[c] = inv[a] \cdot inv[b] \% MOD$
//方法一：	循环找解法(暴力）
//$O(n)$  预处理inv[1-n]：$O(n^2)$
LL getInv(LL x, LL MOD)
{
    for(LL i = 1; i < MOD; i++)
        if(x * i % MOD == 1)
            return i;
    return -1;
}

//方法二： 费马小定理和欧拉定理
//费马小定理:$ a^{(p-1)} \equiv 1(\% p) $, 其中p是质数, 所以a的逆元是$a^{(p - 2)}\%p$
//欧拉定理:$ x^{\phi(m)} \equiv 1 (\% m)$ x与m互素, m是任意整数
//$O(\log{n})$(配合快速幂), 预处理inv[1-n]：$O(n\log{n})$
LL qpow(LL x, LL k, LL MOD) {....}
LL getInv(LL x, LL MOD)
{
    //return qpow(x, euler_phi(MOD) - 1, MOD);
    return qpow(x, MOD - 2, MOD);//MOD是质数
}

//方法三：扩展欧几里得算法
//扩展欧几里得算法可解决  $ a \cdot x + b \cdot y = gcd(a, b) $
//所以$a \cdot x \% MOD = gcd(a, b) \% MOD (b = MOD)$
//$O(\log{n})$, 预处理inv[1-n]：$O(n\log{n})$
inline void exgcd(LL a, LL b, LL &g, LL &x, LL &y)
{
    if(b) exgcd(b, a % b, g, y, x), y -= (a / b) * x;
    else g = a, x = 1, y = 0;
}

LL getInv(LL x, LL mod)
{
    LL g, inv, tmp;
    exgcd(x, mod, g, inv, tmp);
    return g != 1 ? -1 : (inv % mod + mod) % mod;
}

//方法四：积性函数
//已处理inv[1] -- inv[n - 1], 求inv[n]， (MOD > n) (MOD为质数,不存在逆元的i干扰结果)
//$MOD = x \cdot n - y(0 \leq y < n) \Rightarrow x \cdot n = y (\% MOD) \Rightarrow x \cdot n \cdot inv[y] = y \cdot inv[y] = 1 (\%MOD)$
//所以$inv[n] = x \cdot inv[y] (x = MOD - MOD / n, y =  MOD \% n)$
//$O(\log{n})$ 预处理inv[1-n]：$O(n)$
LL inv[NUM];
void inv_pre(LL mod)
{
    inv[0] = inv[1] = 1LL;
    for(int i = 2; i < NUM; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
LL getInv(LL x, LL mod)
{
    LL res = 1LL;
    while(x > 1)
    {
        res = res * (mod - mod / x) % mod;
        x = mod % x;
    }
    return res;
}
//方法五：积性函数+因式分解
//预处理出所有质数的的逆元，采用exgcd来实现素数$O(\log{n})$求逆
//采用质因数分解， 可在$O(\log{n})$求出任意一个数的逆元
//预处理$O(n\log{n})$, 单个$O(\log{n})$
