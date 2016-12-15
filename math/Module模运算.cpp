/*
 模(Module)
 1. 基本运算
	Add: $(a + b) \pmod{p} = (a \pmod{p} + b \pmod{p}) \pmod{p}$
	Subtract:(a - b) % p = ((a%p - b%p)%p + p)%p
	Multiply:(a * b) % p = ((a % p) * (b % p)) % p
	Dvidive: (a / b) % p = (a * $b^{-1}$) % p, $b^{-1}$是b关于p的逆元
	Power: $(a ^ b) \pmod{p} = ((a \pmod{p}) ^ b) \pmod{p}$

	对一个数连续取模, 有效的取模次数小于$O(\log{n})$
 2. 推论
    若$ a \equiv b \bmod{p}, c \equiv d \bmod{p}$, 则 $(a+c) \equiv (b+d) \bmod{p}, (a-c) \equiv (b-d) \bmod{p},
		(a c) \equiv (b d)\bmod{p}, (a/c) \equiv (b/d)\bmod{p}$

 3. 费马小定理
	若p是素数, 对任意正整数x, 有 $ x^p \equiv x \bmod{p}$.
	注意 $x \equiv 1 \bmod{p}$ 的情况
 4. 欧拉定理
	若p与x互素, 则有$ x^{\phi (p)} \equiv 1 \bmod{p}$.
 5. $n! = a p^e, \gcd (a, p) == 1, p$ 是素数
	$e = (n/p + n/p^2 + n/p^3 + \cdots) $(a不能被p整除)
	威尔逊定理：$ (p-1)! \equiv -1 \bmod{p}$(当且仅当p是素数)
	n!中不能被p整除的数的积: $ n! = (p - 1)!^{(n/p)} \times (n\pmod{p})! $
	n!中能被p整除的项为: $p, 2p, 3p, \cdots , (n/p)p$, 除以p得到$1, 2, 3, \cdots , n/p$(问题从缩减到n/p)
	在O(p)时间内预处理除$0 \leq n < p$范围内中的n! mod p的表
	可在$O(\log_p n)$时间内算出答案
	若不预处理,复杂度为$O(p\log_p{n})$
 */
int fact[MAX_P];//预处理n! mod p的表.$O(p)$
//分解$n!=a\ p^e$.返回a % p. $O(\log_p{n})$
int mod_fact(int n, int p, int& e)
{
    e = 0;
    if(n == 0) return 1;
    //计算p的倍数的部分
    int res = mod_fact(n / p, p, e);
    e += n / p;
    //由于$ (p-1)! \equiv -1 $,因此只需知n/p的奇偶性
    if(n / p % 2) return res * (p - fact[n % p]) % p;
    return res * fact[n % p] % p;
}

/*
 6. $n! = t (p^c) ^ u, \gcd (t, p^c) == 1, p$是素数
	1 ~ n中不能被p整除的项模$p^c$,以$p^c$为循环节, 预处理出$n! \pmod{p^c}$的表
	1 ~ n中能被p整除的项, 提取 n/p 个p出来, 剩下阶乘(n/p)!, 递归处理
	最后, t还要乘上$p^u$
 */
LL fact[NUM];
LL qpow(LL x, LL k, LL mod);
inline void pre_fact(LL p, LL pc)//预处理$n! \pmod{p^c}$, $O(p^c)$
{
    fact[0] = fact[1] = 1;
    for(int i = 2; i < pc; i++)
    {
        if(i % p) fact[i] = fact[i - 1] * i % pc;
        else fact[i] = fact[i - 1];
    }
}
//分解$n! = t (p^c) ^ u, n! \pmod{p^c} = t \cdot p^u \pmod{p^c})$
inline void mod_factorial(LL n, LL p, LL pc, LL& t, LL& u)
{
    for(t = 1, u = 0; n; u += (n /= p))
        t = t * fact[n % pc] % pc * qpow(fact[pc - 1], n / pc, pc) % pc;
}
/*
 7. 大组合数求模，mod不是质数
	求$ C_n^m \pmod{mod}$
	1) 因式分解:$ mod = p_1^{c_1} p_2^{c_2} \cdots p_k^{c_k}$
	2) 对每个因子$ p^c $, 求$\displaystyle C_n^m \pmod{p^c} = \frac{n! \pmod{p^c}}{ m! \pmod{p^c} (n-m)! \pmod{p^c}} \pmod{p^c}$
	3) 根据中国剩余定理求解答案(注: 逆元采用扩展欧几里得求法)
 */
LL fact[NUM];
LL prim[NUM], prim_num;
LL pre_prim();
LL pre_fact(LL p, LL pc);
LL mod_factorial(LL n, LL p, LL pc, LL& t, LL& u);
LL qpow(LL x, LL k, LL mod);
LL getInv(LL x, LL mod);

LL C(LL n, LL m, LL mod)
{
    if(n < m) return 0;
    LL p, pc, tmpmod = mod;
    LL Mi, tmpans, t, u, tot;
    LL ans = 0;
    int i, j;
    //将mod因式分解,$ mod = p_1^{c_1} p_2^{c_2} \cdots p_k^{c_k}  $
    for(i = 0; prim[i] <= tmpmod; i++)
        if(tmpmod % prim[i] == 0)
        {
            for(p = prim[i], pc = 1; tmpmod % p == 0; tmpmod /= p)
                pc *= p;
            //求$   C_n^k \pmod{p^c}  $
            pre_fact(p, pc);
            mod_factorial(n, p, pc, t, u);//n!
            tmpans = t;
            tot = u;
            mod_factorial(m, p, pc, t, u);//m!
            tmpans = tmpans * getInv(t, pc) % pc;//求逆元: 采用扩展欧几里得定律
            tot -= u;
            mod_factorial(n - m, p, pc, t, u);//(n - m)!
            tmpans = tmpans * getInv(t, pc) % pc;
            tot -= u;
            tmpans = tmpans * qpow(p, tot, pc) % pc;
            //中国剩余定理
            Mi = mod / pc;
            ans = (ans + tmpans * Mi % mod * getInv(Mi, pc) % mod) % mod;
        }
    return ans;
}

/*
 8. 大组合数求模, mod是素数, Lucas定理
	Lucas定理: $C_n^m \pmod{mod} = C_{n/mod}^{m/mod} \cdot C_{n \pmod{mod}}^{m \pmod{mod}} \pmod{mod}$
	采用$O(n)$方法预处理0 ~ n-1的 $ n! \pmod{mod} $和每个数的逆元, 则可在$O(\log{n})$时间求出$ C_n^k \pmod{mod} $
*/
LL fact[NUM], inv[NUM];
void Lucas_init(LL mod);//预处理
LL Lucas(LL n, LL m, LL mod) //mod是质数
{
    LL a, b, res = 1LL;
    while(n && m)
    {
        a = n % mod, b = m % mod;
        if(a < b) return 0LL;
        res = res * fact[a] % mod * getInv(fact[b] * fact[a - b] % mod, mod) % mod;
        n /= mod, m /= mod;
    }
    return res;
}

