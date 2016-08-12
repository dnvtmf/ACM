///反演与卷积
/*
反演: 如果有两个函数 $f$ 和 $g$ 满足 $$ f(n) = \sum_k{a_{n,k} g(k)} $$, 则已知 $f$ 求 $g$ 的过程称为反演.
*/

///二项式反演
//$$ f(n) = \sum_{i=0}^{n}{C_n^i g(i)} ~\Leftrightarrow ~ g(n) = \sum_{i = 0}^{n} { (-1)^{n-i} C_n^i f(i) }$$
///莫比乌斯反演 Mobius
//mobius函数
/**$$ \mu(x) = \left\{ \begin{array}{l l}
		1 & x= 1\\
		(-1)^r & x = p_1 \cdot p_2 \cdots p_r, \mbox{其中}p_i(i = 1, 2, \cdots r)\mbox{是素数}\\
		0 &\mbox{其他}
		\end{array} \right.$$
*/
/**莫比乌斯反演
形式一: $$ F(n) = \sum_{d|n}{f(d)} \Leftrightarrow f(n) = \sum_{d|n}{\mu (d) F(\frac{n}{d})}	$$
形式二: $$ F(n) = \sum_{n|d}{f(d)} \Leftrightarrow f(n) = \sum_{n|d}{\mu (\frac{d}{n}) F(d)} $$
$$\sum_{d|n}{\mu(d)} = \left\{ \begin{array}{l l} 1 &n=1 \\ 0 & n \neq 1\end{array} \right. $$
$\displaystyle\sum_{d|n}{\phi(d)} = n, \phi(d)$为欧拉函数
$\displaystyle \frac{\phi(n)}{n} = \sum_{d|n}{\frac{\mu(d)}{d}}$ */

//使用1
/*
	$\displaystyle \sum{\gcd(i, j) == D} (1 \leq i \leq a, 1 \leq j \leq b, a \leq b)$, 即求gcd(i, j)等于d的(i, j)对数, $\lfloor x \rfloor$表示下取整
	$\displaystyle \sum_{i=1}^{a}{\sum_{j=1}^{b}{\gcd(i,j) == D}}$
	$\displaystyle \Rightarrow \sum_{i=1}^{\lfloor \frac{a}{D} \rfloor}{\sum_{j=1}^{\lfloor \frac{b}{D} \rfloor}{gcd(i, j) == 1}}$
	$\displaystyle \Rightarrow \sum_{d=1}^{\lfloor \frac{a}{D} \rfloor}{\sum_{d|gcd(i,j)}{\mu(d)}}$, 使用mobius函数和的性质替换gcd(i, j)==1
	$\displaystyle (\sum_{i}^{a}{\sum_{j}{b}{\sum_{d| gcd(i, j)}{1}}} = \lfloor \frac{a}{d} \rfloor \lfloor \frac{b}{d} \rfloor)$
	$\displaystyle \Rightarrow \sum_{d=1}^{\lfloor \frac{a}{D} \rfloor}{\displaystyle \mu(d) \lfloor \frac{\lfloor \frac{a}{D} \rfloor}{d} \rfloor \cdot \lfloor \frac{\lfloor \frac{b}{D} \rfloor}{d}\rfloor} , d | gcd(i, j) \Leftrightarrow d|i \cup d | j$
	$\displaystyle D == 1, \sum_{d=1}^{a}{\mu(d)\cdot \lfloor \frac{a}{d} \rfloor \cdot \lfloor \frac{b}{d} \rfloor}$
*/

//使用2
/*
	$\displaystyle \sum_{i=1}^{a}{\sum_{j=1}^{b}{\gcd(i,j)}}, a\leq b$
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}{\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}{d \cdot (\gcd{(i, j)} == 1)}}}$
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{d' =1}^{\lfloor \frac{a}{d} \rfloor}{d \cdot \mu(d')\cdot \lfloor \frac{a}{dd'} \rfloor \cdot \lfloor \frac{b}{dd'} \rfloor}}$, 使用1
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{d|D}{d\cdot \mu(\frac{D}{d}) \cdot \lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor}}, D = dd'$
	$\displaystyle \Rightarrow \sum_{D=1}^{a}{\lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor \cdot (id\cdot \mu)(D)}$
	$\displaystyle \Rightarrow \sum_{D=1}^{a}{\lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor \cdot \phi(D)}, \ id \cdot \mu = \phi$
*/

///积性函数
/*
定义在正整数集上的函数$f(n)$(称为算术函数), 若$\gcd(a, b) = 1$时有$f(a) \cdot f(b) = f(a\cdot b)$, 则称$f(x)$为积性函数。
一个显然的性质: (非恒等于零的) 积性函数$f(n)$必然满足$f(1)=1$.
定义逐点加法$(f + g)(n) = f(x) + g(x), f(x\cdot g) = f(x) \cdot g(x)$.
一个比较显然的性质: 若$f,g$均为积性函数，则$f\cdot g$也是积性函数。
积性函数的求值: $n = \prod{p_i^{a_i}}$ 则$f(n) = \prod{f(p_i^{a_i})}$, 所以只要解决$n = p^a$时$f(n)$的值即可.

常见积性函数有:
恒为1的常函数$1(n) = 1$,
恒等函数$id(n) = n$,
单位函数$\varepsilon(n) = (n==1)$, (这三个都是显然为积性)
欧拉函数$\phi(n)$(只要证两个集合相等就能证明积性)
莫比乌斯函数$\mu(n)$ (由定义也是显然的)
因子个数函数$\tau$
因子和函数$\sigma$
$\mu \cdot id = \phi$
*/
void pre_mobius(int mu[], int prime[], int &cnt)
{
	mu[1] = 1;
	cnt = 0;
	for(int i = 2; i < NUM; ++i) {
		if(!prime[i]) {
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < cnt && i * prime[j] < NUM; ++j) {
			prime[i * prime[j]] = 1;
			if(i % prime[j]) mu[i * prime[j]] = -mu[i];
			else {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
}

///Dirichlet卷积
/*
对两个算术函数$f, g$, 定义其Dirichlet卷积为新函数 $ f * g $. 满足
$$ (f * g)(n) = \sum_{d|n}{ f(d) g( \frac{n}{d} ) } = \sum_{ab = n}{ f(a) g(b) } $$
一些性质:
交换律, $f * g = g * f$
结合律, $(f * g) * h = f * (g * h)$
单位元, $f * \varepsilon = f$
对逐点加法的分配律, $f * (g + h) = f * g + f * h$

重要性质: 若$f, g$均为积性函数, 则$f * g$也是积性函数. (展开式子即可证明)
n的约数个数$d(n)$可以写成$d(n) = (1*1)(n)$; 约数和$\sigma(n)$可以写成$\sigma(n) = (1 * id)(n)$, 由上面的性质可知这两个函数均是积性函数.

重要性质: $\displaystyle \sum_{d|n}{\mu(d)} = [n == 1]$, 即$1 * \mu = \varepsilon$. (可用二项式定理证明)
重要性质: $\displaystyle \sum_{d|n}{\phi(d)} = n$, 即$1 * \phi = id$. (n是质数时显然成立, 再由积性得证)
*/
//$O(n\log{n})$ 预处理Dirichlet卷积
//若已知$f(i), g(i), i = 1, 2, \dots, n$的值，则可以在$O(n\log{n})$时间内计算出$(f * g)(i), i = 1, 2, \dots, n$.
void dirichlet(int f[], int g[], int fg[], int n)
{
	//for(int i = 1; i <= n; ++i) fg[i] = 0;
	for(int i = 1; i * i <= n; ++i)
		for(int j = i; i * j <= n; ++j)
			if(i == j) fg[i * j] += f[i] * g[i];
			else fg[i * j] += f[i] * g[j] + f[j] * g[i];
}
