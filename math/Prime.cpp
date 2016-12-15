///素数 Prime
/*素数定理
    设素数分布函数$\pi(n)$为小于等于n的素数个数, 则有以下近似:@$$
    \lim_{n \to \infty}{\frac{\pi(n)}{n / \ln{n}}} = 1
    $$@.
素数计数函数$\pi(m)$, 计算方法:
令$\displaystyle {\sqrt[{3}]{m}}\leq y \leq {\sqrt {m}}$, 并令$n=\pi (y)$,则有:
@$$ \pi (m)=\Phi (m,n)+n-1-P_{2}{(m,n)} \pi (m)=\Phi (m,n) + n-1-P_{2}(m,n) $$@
令$p_1, p_2, \ldots, p_n$表示前n个素数, 则$\Phi (m, n)$表示质因数大于$p_n$的不大于 $m$ 的自然数个数. 有:
@$${\displaystyle \Phi (m,0)=\lfloor m\rfloor } \Phi (m,0)=\lfloor m\rfloor$$@
@$${\displaystyle \Phi (m,b)=\Phi (m,b-1)-\Phi \left({\frac {m}{p_{b}}},b-1\right)} \Phi (m,b)=\Phi (m,b-1)-\Phi \left({\frac {m}{p_{b}}},b-1\right)$$@
$P_k (m, n)$ 表示质因数的个数为 $k$ 且都大于 $p_n$ 的不大于 $m$ 的自然数个数, 有
@$${\displaystyle P_{2}(m,n)=\sum _{y<p\leq {\sqrt {m}}}\left(\pi \left({\frac {m}{p}}\right)-\pi (p)+1\right)} P_{2}(m,n)=\sum _{y<p\leq {\sqrt {m}}}\left(\pi \left({\frac {m}{p}}\right)-\pi (p)+1\right)$$@
*/
/*伪素数
    如果n是一个合数, 并且$a ^ {n - 1} \equiv 1 (\mod n)$, 则说n是一个基为a的伪素数.
*/
///涮素数
int prime[NUM], prime_num;
//$O(n\log{n})$
void pre_prime()
{
	prime_num = 0;
	for(int i = 2; i < NUM; ++i) {
		if(prime[i]) continue;
		prime[prime_num++] = i;
		for(int j = i + i; j < NUM; j += i) prime[j] = 1;
	}
}

//$O(n)$
void pre_prime()
{
	prime_num = 0;
	for(int i = 2; i < NUM; ++i) {
		if(!prime[i]) prime[prime_num++] = i;
		for(int j = 0; j < prime_num && i * prime[j] < NUM; ++j) {
			prime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
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
	while(t--) {
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
	while(test_num--) {
		LL a = rand() % (n - 1) + 1;//产生1~n-1之间的随机数
		if(check(a, n, u, t))
			return false;//合数
	}
	return true;
}

//求 $10^11$ 以内的素数个数
const int NUM = 22000010;
const int MAXM = 40000, MAXN = 300;
bitset<NUM> flag;
int prime[1500000], num;
int phi[MAXN][MAXM];
void init()
{
	memset(phi, -1, sizeof(phi));
	for(int i = 2; i < NUM; ++i) {
		if(!flag[i])  prime[num++] = i;
		for(int j = 0; j < num && prime[j] * i < NUM; ++j) {
			flag[i * prime[j]] = 1;
			if(i % prime[j] == 0) {
				break;
			}
		}
	}
	for(int i = 0; i < MAXM; ++i) phi[0][i] = i;
	for(int i = 1; i < MAXN; ++i) {
		for(int j = 0; j < MAXM; ++j) {
			phi[i][j] = phi[i - 1][j] - phi[i - 1][j / prime[i - 1]];
		}
	}
}
//$pi(x)$ denoted the number of prime numbers less than or equal than x
LL pi(LL x)
{
	return upper_bound(prime, prime + num, x) - prime;
}
//$\Phi(x)$ denoted the number of natural numbers not greater than m which are divisible by no p_i(p_1, p_2, ..., p_2 is the first n primes)
LL Phi(LL m, LL n)
{
	if(n == 0) return m;
	if(prime[n - 1] >= m) return 1;
	if(m < MAXM && n < MAXN) return phi[n][m];
	return Phi(m, n - 1) - Phi(m / prime[n - 1], n - 1);
}

LL solve(LL x)
{
	if(x < NUM) return pi(x);
	LL ans = 0;
	LL n = 0;
	while(1ll * prime[n] * prime[n] * prime[n] < x) {
		++ans;
		++n;
	}
	ans += Phi(x, n) - 1;
	while(1ll * prime[n] * prime[n] <= x) {
		ans -= solve(x / prime[n]) - solve(prime[n]) + 1;
		++n;
	}
	return ans;
}
