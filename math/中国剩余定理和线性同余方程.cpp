/*线性同余方程
@$ a_i\times x \equiv b_i (mod\ m_i)\ (1 \leq i \leq n)	$@
如果方程组有解，那么一定有无穷有无穷多解，解的全集可写为@$ x \equiv b(mod\ m)	$@的形式.
对方程逐一求解.令b = 0, m = 1;
1.@$	x \equiv b (mod\ m)	$@可写为x = b + m * t;
2. 带入第i个式子: @$	a_i(b+m*t) \equiv b_i(mod\ m_i)	$@,即@$	a_i \times m \times t \equiv b_i - a_i \times b(mod\ m_i)	$@
3.当@$ \gcd(m_i, a_i\times m)	$@无法整除@$	b_i - a_i \times b	$@时原方程组无解,否则用exgcd，求出满组条件的最小非负整数t，
	b = b + m * t, m = lcm(m, m_i)
*/

