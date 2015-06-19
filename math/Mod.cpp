/*
 模(Module)
 1. 基本运算
	Add: (a + b) % p = (a % p + b % p) % p
	Subtract:(a - b) % p = ((a%p - b%p)%p + p)%p
	Multiply:(a * b) % p = ((a % p) * (b % p)) % p
	Dvidive: (a / b) % p = (a * @$b^{-1}$@) % p @$b^{-1}$@是b关于p的逆元
	Power: @$(a ^ b) \% p = ((a \% p) ^ b) \% p	 $@
 2. 推论
    若@$ a \equiv b (\%p), c \equiv d(\%p)	$@,则@$	(a+c) \equiv (b+d)(\%p), (a-c) \equiv (b-d)(\%p),
		(a*c) \equiv (b*d)(\%p), (a/c) \equiv (b/d)(\%p)	$@
	
 3. 费马小定理
	若p是素数，对任意正整数x,有 @$ x^p \equiv x (\% p) $@.
 4. 欧拉定理
	若p与x互素, 则有@$ x^{\phi (p)} \equiv 1 (\% p)	$@.
 5. n!
	p是素数, @$n! = a\ p^e, e = (n/p + n/p^2 + n/p^3 + \cdots) $@(a不能被p整除)
	威尔逊定理：(p-1)! @$ \equiv $@ -1 (%p)
	n!中不能被p整除的数的积:@$ n! = (p - 1)!^{(n/p)} \times (n\  mod\ p)! $@
	n!中能被p整除的项为:p, 2p, 3p, ... , (n/p)p, 除以p得到1,2,3,...,n/p(问题从缩减到n/p)
	在O(p)时间内预处理除0 <= n < p范围内中的n! mod p的表
	可在@$	O(\log_p n)	$@时间内算出答案
	若不预处理,复杂度为@$	O(p\ \log_p n)	$@
 */
int fact[MAX_P];//预处理n! mod p的表.O(p)
//分解@$	n!=a\ p^e	$@.返回a % p. @$	O(\log_p n)	$@
int mod_fact(int n, int p, int &e)
{
	e = 0;
	if(n == 0) return 1;
	//计算p的倍数的部分
	int res = mod_fact(n / p, p, e);
	e += n/p;
	//由于@$ (p-1)! \equiv -1 $@,因此只需知n/p的奇偶性	
	if(n / p % 2) return res * (p - fact[n%p]) % p;
	return res * fact[n % p] % p;
}
