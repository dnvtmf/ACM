///欧拉函数 (Euler's totient function)
/*
对正整数n, 欧拉函数是小于或等于n的数中与n互质的数的数目
通式：$\phi(n) = n(1-\frac{1}{p_1}) (1-\frac{1}{p_2}) \cdots (1-\frac{1}{p_k})$, 其中$p_1, p_2, \cdots , p_k$ 为n的所有质因数, n是不为0的整数.
$\phi(1) = 1$ (唯一和1互质的数(小于等于1)就是1本身);
$\phi(p) = p-1, p$为素数
若n是质数p的k次幂, $\phi(n) = p^k - p^{k-1} = (p-1)p^{k-1}$, 因为除了p的倍数外，其他数都跟n互质。
欧拉函数是积性函数——若m, n互质, $\phi(mn)=\phi(m) \phi(n)$.
当n为奇数时, $\phi(2n) = \phi(n)$.
*/
///欧拉定理: 对任何两个互质的正整数$a, m, m \geq 2$有 $a^{\phi(m)} \equiv 1(\% m)$
///费马小定理(Fermat's little theorem): 当p是质数时, 为: $a^{p-1} \equiv 1(\% p)$
///(广义欧拉定理)降幂公式: $A^x = A^{x \% \phi(C) + \phi(C)} \% C$, $(x > \phi(C))$

//求欧拉函数
int Euler(int n)
{
	int euler = n;
	for(int i = 1; i < primen; i++)
		if(n % prime[i]) {
			euler = euler / prime[i] * (prime[i] - 1);
		}
	return euler;
}
//预处理 $O(N\log{N})$
int euler[NUM];
int Euler()
{
	euler[1] = 1;
	for(int i = 2; i < NUM; ++i) {
		if(euler[i]) continue;
		for(int j = i; j < NUM; j += i) {
			if(euler[j]) euler[j] = euler[j] / i * (i - 1);
			else euler[j] = j / i * (i - 1);
		}
	}
}
//预处理 $O(N)$
int euler[NUM], prime[NUM], prime_cnt;
int Euler()
{
	prime_cnt = 0;
	euler[1] = 1;
	for(int i = 2; i < NUM; ++i) {
		if(!euler[i]) {
			prime[prime_cnt++] = i;
			euler[i] = i - 1;
		}
		for(int j = 0; j < prime_cnt && i * prime[j] < NUM; ++j) {
			prime[i * prime[j]] = 1;
			if(i % prime[j] == 0) {
				euler[i * prime[j]] = euler[i] * prime[j];
				break;
			}
			euler[i * prime[j]] = euler[i] % prime[j];
		}
	}
}
