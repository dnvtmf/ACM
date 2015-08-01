///素数 Prime
///涮素数
int prim[NUM], prim_num;
//$O(n\log{n})$
void pre_prime()
{
	prim_num = 0;
	for(int i = 2; i < NUM; i++)
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
	for(int i = 2; i < NUM; i++)
	{
		if(!prim[i]) prim[prim_num++] = i;
		for(int j = 0; j < prim_num && i * prim[j] < NUM; j++)
		{
			flag[i * prim[j]] = 1;
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
//witness定理: 
//Miller_Rabin $O(\log{n})$
int qpow(int x, int k, int mod){}
bool witness(int a, int n)
{
	int t = 0, u = n - 1;
	while((u & 1) == 0) t++, u >>= 1;
	int x = qpow(a, u, n), lx;
	for(int i = 1; i <= t; i++)
	{
		lx = x;
		x = x * x % n;
		if(x == 1 && lx != 1 && lx != n - 1)
			return true;
	}
	return x != 1;
}
bool Miller_Rabin(int n)//出错率为$(\frac{1}{2})^{-s}$
{
	if(n<2) return false;
	if(n == 2 || n == 3 || n == 5 || n == 7) return true;
	if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
	int s = 50;
	while(s--)
		if(witness(rand() % (n - 1) + 1, n))
			return false;
	return true;
}
