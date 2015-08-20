///滚动哈希算法 $O(n + m)$
//使用于求字符串s在字符串t中出现的位置或次数 可以简单的推到二维的情况
//哈希函数$H(S) = (s_1 B^{m-1} + s_2 B^{m-2} + \cdots + s_m B^0) \% h$, 其中字符串$S = s_1s_2\cdots c_m, m = |S|$, B为基数, $1 < B < h$且h与b互素
//$H(s_{k-1}s_{k}\cdots s_{k + m - 1}) = (H(s_k s_{k+1} \cdots s_{k+m}) - s_k B^m + s_{k+m}) \% h$
//单hash一般足够, 也可以使用双hash
//常用h: $10^9+7, 10^9+9$, B取比字符集大的一个素数.
//注意: 将要hash的每一个字符应该至少从1开始编号, 即不能为0.

//应用1: 在许多字符串中寻找与目标串相同的字符串的个数
LL B = 71, mod = 1000000007;
int cal(string s, string t)//查询s的子串是t的个数
{
    int lens = s.length(), lent = t.length();
    if(lent > lens) return 0;
    LL BN = 1, hasht = 0, hashs = 0;
    for(int i = 0; i < lent; i++) hasht = (hasht * B + (t[i] - 'a' + 1)) % mod, BN = BN * B % mod;
    for(int i = 0; i < lent; i++) hashs = (hashs * B + (t[i] - 'a' + 1)) % mod;
    int cnt = (hasht == hashs);
    for(int i = lent; i < lens; i++)
    {
        hashs = (hashs * B + (s[i] - 'a' + 1)) % mod - BN * (s[i - lent] - 'a' + 1) % mod;
        hashs = (hashs % mod + mod) % mod;
        if(hashs == hasht) cnt++;
    }
    return hashs;
}
