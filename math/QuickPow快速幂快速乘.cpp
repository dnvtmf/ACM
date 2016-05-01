//快速幂, 快速模幂
LL qpow(LL x, LL k, LL mod)
{
    LL ans = 1;
    x %= mod;
    while(k)
    {
        if(k & 1) ans = ans * x % mod;
        x = x * x  % mod;
        k >>= 1;
    }
    return ans;
}
LL qpow(LL x, LL k, LL mod)
{
    LL ans = 1;
    for(x %= mod; k; k >>= 1, x = x * x % mod)
        if(k & 1) ans = ans * x % mod;
    return ans;
}
//快速模乘$a \times b \% mod$
//用于$a \times b$可能爆LL
LL mod_mult(LL a, LL b, LL mod)
{
    LL res = 0;
    if(a >= mod) a %= mod;
    while(b)
    {
        if(b & 1)
        {
            res += a;
            if(res += mod) res -= mod;
        }
        a <<= 1;
        if(a >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}

LL qmult(LL a, LL b, LL mod)
{
    LL res = 0;
    for(a %= mod; b; b >>= 1, (a += a) %= mod)
        if(b & 1)(res += a) %= mod;
    return res;
}
