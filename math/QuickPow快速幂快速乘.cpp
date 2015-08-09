//快速幂, 快速模幂
LL qpow(LL x, int k, LL mod)
{
    LL ans = 1;
    while(k)
    {
        if(k & 1) ans = ans * x % mod;
        x = x * x  % mod;
        k >>= 1;
    }
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
