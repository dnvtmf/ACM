///素数 Prime
/*素数定理
    设素数分布函数$\pi(n)$为小于等于n的素数个数, 则有以下近似:@$$
    \lim_{n \to \infty}{\frac{\pi(n)}{n / \ln{n}}} = 1
    $$@.
*/
/*伪素数
    如果n是一个合数, 并且$a ^ {n - 1} \equiv 1 (\mod n)$, 则说n是一个基为a的伪素数.
*/
///涮素数
int prim[NUM], prim_num;
//$O(n\log{n})$
void pre_prime()
{
    prim_num = 0;
    for(int i = 2; i < NUM; ++i)
    {
        if(prim[i]) continue;
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

//Miller_Rabin $O(test_num \cdot \log{n})$
int qpow(int x, int k, int mod) {}
//以a为基, $n - 1 = 2^t u, (t \geq 1 and u is odd)$, 通过$a^{n-1} \equiv 1 (\mod n)$验证n是不是合数
//一定是合数返回true, 不一定返回false
bool witness(LL a, LL n, LL u, LL t)
{
    LL res = qpow(a, u, n);//$a^u (\mod n)$
    LL last = res;
    while(t--)
    {
        //res = qmult(res, res, n);
        res = res * res % n;
        if(res == 1 && last != 1 && last != n - 1) return true; //合数
        last = res;
    }
    return res != 1;
}

//是素数返回true(可能是伪素数, 但概率极小, 至多为$2^{-test_num}$), 合数返回false.
bool Miller_Rabin(LL n, int test_num = 50)
{
    if(n < 2)return false;
    if(n == 2)return true;
    if((n & 1) == 0) return false; //偶数
    LL u = n - 1;
    LL t = 0;
    while((u & 1) == 0) {u >>= 1; ++t;}
    while(test_num--)
    {
        LL a = rand() % (n - 1) + 1;//产生1~n-1之间的随机数
        if(check(a, n, u, t))
            return false;//合数
    }
    return true;
}
