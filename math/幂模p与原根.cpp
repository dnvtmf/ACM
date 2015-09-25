///幂模p与原根primitive root
//a模p的次数(或阶)指$e_p(a)=($使得$a^e\equiv 1 (\% p)$的最小指数$e \geq 1$)
//(次数整除性质), 设a是不被素数p整除的整数, 假设$a^n \equiv 1(\% p)$, 则次数$e_p(a)$整除n, 特别地, 次数$e_p(a)$总整除p-1.
//原根: 具有最高次数$e_p(g) = p - 1$的数g被称为模p的原根
//原根定理: 每个素数p都有恰好$\phi(p - 1)$个原根
//求最小原根: 原根分布较广, 而且最小的原根通常也比较小, 可以从小到大通过枚举每个正整数来快速的寻找一个原根. 对于一个待检查的p, 对于p-1的每一个素因子a, 检查$g^{(p-1)/a} \equiv 1 (\% p)$是否成立, 如果成立则不是.
//1e9 + 7的最小原根为5, 1e9 + 7的最小原根为13
LL qpow(LL x, LL k, LL mod);
bool g_test(LL g, LL p, vector<LL> &factor)
{
    for(int i = 0; i < (int)factor.size(); i++)
        if(qpow(g, (p - 1) / factor[i], p) == 1)
            return false;
    return true;
}
LL primitive_root(LL p)
{
    vector<LL> factor;
    //求p-1的素因子
    LL tmp = p - 1;
    for(LL i = 2; i * i <= tmp; i++)
        if(tmp % i == 0)
        {
            factor.push_back(i);
            while(tmp % i == 0) tmp /= i;
        }
    if(tmp != 1) factor.push_back(tmp);
    LL g = 1;
    while(true)
    {
        if(g_test(g, p, factor))
            return g;
        g++;
    }
}

/*无理数的模幂
求 $\lceil (a + b\sqrt{c})^n \mod m \rceil, (a - 1)^2 < b^2 c < a^2, n > 0, m > 0$.
令 $S_n = (a + b \sqrt{c})^n + (a - b \sqrt{c})^n$
由于 $a - 1 < b\sqrt{c} < a$, 所以 $0 < (a - b \sqrt{c})^n < 1$.
所以 $S_n$ 即为所求的值, 且由于 $S_n$ 展开后带根号的项相互抵消, $S_n$ 是整数.
关于 $S_n$ 的递推式:
    $[(a + b\sqrt{c}) + (a - b\sqrt{c})]S_n$
$=[(a + b\sqrt{c}) + (a - b\sqrt{c})][(a + b\sqrt{c})^n + (a - b\sqrt{c})^n]$
$=(a+b\sqrt{c})^{n+1} + (a - b\sqrt{c})^{n+1} + (a + b\sqrt{c})(a - b\sqrt{c})^n + (a - b\sqrt{c})(a + b\sqrt{c})^n$
$= S_{n+1} + (a^2 - b^2 c)[(a + b\sqrt{c})^{n - 1} + (a - b\sqrt{c})^{n - 1}]$
$= S_{n+1} + (a^2 - b^2 c)S_{n-1}$
即$2aS_n = S_{n+1} + (a^2 - b^2 c)S_{n-1} \Rightarrow S_{n+1} = 2aS_n + (b^2 c - a^2)S_{n-1}$
然后可以用矩阵快速幂快速求解.

相关题目: hdu 4565 So Easy
*/
