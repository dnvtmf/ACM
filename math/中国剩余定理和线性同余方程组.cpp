/*线性同余方程组
	$a_i \times x \equiv b_i (\%\ m_i)\ (1 \leq i \leq n)	$
	如果方程组有解，那么一定有无穷有无穷多解，解的全集可写为$ x \equiv b(\%\ m)	$的形式.
	对方程逐一求解.令b = 0, m = 1;
	1. $x \equiv b (\%\ m)	$可写为$x = b + m \cdot t$;
	2. 带入第i个式子: $a_i(b + m \cdot t) \equiv b_i(\%\ m_i)$,即$a_i \cdot m \cdot t \equiv b_i - a_i \cdot b(\%\ m_i)$
	3. 当$\gcd(m_i, a_i \cdot m)$无法整除$b_i - a_i \cdot b$时原方程组无解, 否则用exgcd, 求出满组条件的最小非负整数t.
*/
/*中国剩余定理
	对$x \equiv a_i (\% \ m_i) (1 \leq i \leq n)$, 其中$m_1, m_2, \cdots, m_n$两两互素, $a_1, a_2, \cdots, a_n$是任意整数, 则有解:
	$M = \prod{m_i}, b = \sum_i^n{a_i M_i^{-1} M_i} (M_i = M / m_i, M_i^{-1}$ 是 $M_i$ 关于 $m_i$ 的逆元)
*/
int gcd(int a, int b);
int getInv(int x, int mod);
pair<int, int> linear_congruence(const vector<int> &A, const vector<int> &B, const vector<int> &M)
{
    //初始解设为表示所有整数的$x \equiv 0(\%\ 1)$
    int x = 0, m = 1;
    for(int i = 0; i < A.size(); i++)
    {
        int a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
        if(b % d != 0) return make_pair(0, -1);//无解
        int t = b / d * getInv(a / d, M[i] / d) % (M[i] / d);
        x = x + m * t;
        m *= M[i] / d;
    }
    return make_pair(x % m, m);
}
