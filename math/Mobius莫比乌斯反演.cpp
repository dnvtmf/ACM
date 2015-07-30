///莫比乌斯反演 Mobius
//mobius函数
/*@$$ \mu(x) = \left\{ \begin{array}{l l}
		1 & x= 1\\
		(-1)^r & x = p_1 \cdot p_2 \cdots p_r, \mbox{其中}p_i(i = 1, 2, \cdots r)\mbox{是素数}\\
		0 &\mbox{其他}
		\end{array} \right.$$@
*/
//莫比乌斯反演
//@$$ F(n) = \sum_{d|n}{f(d)} \Leftrightarrow f(n) = \sum_{d|n}{\mu (d) F(\frac{n}{d})}	$$@
//@$$\sum_{d|n}{\mu(d)} = \left\{ \begin{array}{l l} 1 &n=1 \\ 0 & n \neq 1\end{array} \right. $$@
//$\displaystyle\sum_{d|n}{\varphi(d)} = n, \varphi(d)$为欧拉函数
//$\displaystyle \varphi(n) = n\sum_{d|n}{\mu(d)/d}$

//使用1
/*
	$\displaystyle \sum{\gcd(i, j) == D} (1 \leq i \leq a, 1 \leq j \leq b, a \leq b)$, 即求gcd(i, j)等于d的对数, $\lfloor x \rfloor$表示下取整
	$\displaystyle \sum_{i=1}^{a}{\sum_{j=1}^{b}{\gcd(i,j) == D}}$
	$\displaystyle \Rightarrow \sum_{i=1}^{\lfloor \frac{a}{D} \rfloor}{\sum_{j=1}^{\lfloor \frac{b}{D} \rfloor}{gcd(i, j) == 1}}$
	$\displaystyle \Rightarrow \sum_{i=1}^{\lfloor \frac{a}{D} \rfloor}{\sum_{d|gcd(i,j)}{\mu(d)}}$, 使用mobius函数和的性质替换gcd(i, j)==1
	$\displaystyle \Rightarrow \sum_{d=1}^{\lfloor \frac{a}{D} \rfloor}{\displaystyle \mu(d) \lfloor \frac{\lfloor \frac{a}{D} \rfloor}{d} \rfloor \cdot \lfloor \frac{\lfloor \frac{b}{D} \rfloor}{d}\rfloor} , d | gcd(i, j) \Leftrightarrow d|i \cup d | j$
	$\displaystyle D == 1, \sum_{d=1}^{a}{\mu(d)\cdot \lfloor \frac{a}{d} \rfloor \cdot \lfloor \frac{b}{d} \rfloor}$
==> sum(d=1 -> [a/D]){μ(d)*[[a/D]/d]*[[b/D]/d]},  d|\gcd(i, j) <==> (d|i) \cup (d|j)
*/

//使用2
/*
	$\displaystyle \sum_{i=1}^{a}{\sum_{j=1}^{b}{\gcd(i,j)}}, a\leq b$
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}{\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}{d \cdot (\gcd{(i, j)} == 1)}}}$
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{d' =1}^{\lfloor \frac{a}{d} \rfloor}{d \cdot \mu(d')\cdot \lfloor \frac{a}{dd'} \rfloor \cdot \lfloor \frac{b}{dd'} \rfloor}}$, 使用1
	$\displaystyle \Rightarrow \sum_{d=1}^{a}{\sum_{d|D}{d\cdot \mu(\frac{D}{d}) \cdot \lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor}}, D = dd'$
	$\displaystyle \Rightarrow \sum_{D=1}^{a}{\lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor \cdot (id\cdot \mu)(D)}$
	$\displaystyle \Rightarrow \sum_{D=1}^{a}{\lfloor \frac{a}{D} \rfloor \cdot \lfloor \frac{b}{D} \rfloor \cdot \varphi(D)}, \ id \cdot \mu = \varphi$
*/

///积性函数
//定义在正整数集上的函数$f(n)$(称为算术函数), 若$\gcd(a, b) = 1$时有$f(a) \cdot f(b) = f(a\cdot b)$, 则称$f(x)$为积性函数。
//一个显然的性质: (非恒等于零的) 积性函数$f(n)$必然满足$f(1)=1$.
//定义逐点加法$(f + g)(n) = f(x)+g(x), f(x\cdot g) = f(x) \cdot g(x)$.
//一个比较显然的性质: 若$f,g$均为积性函数，则$f\cdot g$也是积性函数。
//积性函数的求值: $n = \prod{p_i^{a_i}}$ 则$f(n) = \prod{f(p_i^{a_i})}$, 所以只要解决$n = p^a$时$f(n)$的值即可.

//常见积性函数有:
//恒为1的常函数$1(n) = 1$,
//恒等函数$id(n) = n$,
//单位函数$\varepsilon(n) = (n==1)$, (这三个都是显然为积性)
//欧拉函数$\varphi(n)$(只要证两个集合相等就能证明积性)
//莫比乌斯函数$\mu(n)$ (由定义也是显然的)
//$\mu \cdot id = \varphi$
void pre_mobius()
{
    mu[1] = 1;
    for(int i = 2; i < NUM; i++)
        if(!mu[i])
        {
            mu[i] = -1;
            for(int j = i + i; j < NUM; j += i)
                if((j / i) % i == 0)
                    mu[j] = 2;
                else
                {
                    if(mu[j] == 0) mu[j] = -1;
                    else mu[j] = -mu[j];
                }
        }
        else if(mu[i] == 2 || mu[i] == -2) mu[i] = 0;
}
