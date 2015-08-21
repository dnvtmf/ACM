///素数 Prime
///涮素数
int prim[NUM], prim_num;
//$O(n\log{n})$
void pre_prime()
{
    prim_num = 0;
    for(int i = 2; i < NUM; ++i)
        if(!prim[i])
        {
            prim[prim_num++] = i;
            for(int j = i + i; j < NUM; j += i) prim[j] = 1;
        }
}

//$O(n)$
void pre_prime()
{
    prim_num = 0;
    for(int i = 2; i < NUM; ++i)
    {
        if(!prim[i]) prim[prim_num++] = i;
        for(int j = 0; j < prim_num && i * prim[j] < NUM; ++j)
        {
            prim[i * prim[j]] = 1;
            if(i % prim[j] == 0) break;
        }
    }
}

//区间素数
/*要获得区间[L, U]内的素数, L和U很大, 但U - L不大, 那么, 先线性涮出1到$\sqrt{2147483647} \leq 46341$之间所有的素数, 然后在通过已经涮好的素数涮出给定区间的素数
*/

///素数判定
//试除法: 略过偶数, 试除2到$\sqrt{n}$间的所有数$O(\sqrt{n})$
bool isPrime(int n)
{
    if(n % 2 == 0)return n == 2;
    for(int i = 3; i * i <= n; i += 2)
        if(n % i == 0)
            return false;
    return true;
}
//简单测试: 根据费马小定理p是素数, 则有$a^{(p-1)} \equiv 1 (\% p)$, 通过选取[0, p-1]间的任意整数a, 如果测试结果不满足上述定理, 则p是合数, 否则, p可能是素数
//Miller_Rabin $O(\log{n})$
int qpow(int x, int k, int mod) {}
//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true, 不一定返回false
bool check(LL a, LL n, LL x, LL t)
{
    LL ret = qpow(a, x, n);
    LL last = ret;
    for(int i = 1; i <= t; i++)
    {
        ret = mult_mod(ret, ret, n);
        if(ret == 1 && last != 1 && last != n - 1) return true; //合数
        last = ret;
    }
    if(ret != 1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true. (可能是伪素数, 但概率极小)
//合数返回false;

bool Miller_Rabin(LL n)
{
    if(n < 2)return false;
    if(n == 2)return true;
    if((n & 1) == 0) return false; //偶数
    LL x = n - 1;
    LL t = 0;
    while((x & 1) == 0) {x >>= 1; t++;}
    int check_time = 50;
    for(int i = 0; i < check_time; i++)
    {
        LL a = rand() % (n - 1) + 1;
        if(check(a, n, x, t))
            return false;//合数
    }
    return true;
}
