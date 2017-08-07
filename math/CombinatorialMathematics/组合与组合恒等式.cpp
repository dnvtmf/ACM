///组合
/*
1. 组合: 从n个不同的元素中取r个的方案数@$C_n^r$@:
	@$ C_n^r = 	\left\{
 					\begin{array}{l l}
					{\displaystyle\frac{n!}{r!(n-r)!}}, &n \geq r\\
 					1, &n \geq r = 0\\
 					0, &n < r
 					\end{array}
				\right.$@
	推论1: $C_n^r = C_n^{n-r}$
	推论2(Pascal公式): $C_n^r = C_{n-1}^r + C_{n-1}^{r-1}$
	推论3: $\displaystyle \sum_{k=0}^{n}{C_k^r} = \sum_{k=r}^{n}{C_k^r} = C_{n+1}^{r+1}$
	推论4: $\displaystyle \sum_{k=0}^{r}{C_{n + k}^{k}} = C_{n + r + 1}^{r}$
	推论5: $C_n^k C_k^r = C_n^r C_{n-r}^{k-r} (k \geq r)$.
2. 从重集$B=\{\infty \cdot b_1, \infty \cdot b_2, \dots , \infty \cdot b_n\}$的r-组合数F(n,r)为$F(n,r)=C_{n+r-1}^{r}$

3. 二项式定义
	当n是一个正整数时, 对任何x和y有:
	@$$(x+y)^n = \sum_{k=0}^n{C_n^k x^k y^{n-k}}$$@
	令y=1, 有:
	$\displaystyle (1+x)^n = \sum_{k=0}^n{C_n^k x^k} = \sum_{k=0}^n{C_n^{n-k} x^k}$
	广义二项式定理:
	广义二项式系数: 对于任何实数@$\alpha$@和整数k,有
	@$$C_{\alpha}^{K}=\left\{ \begin{array}{c l}
		\frac{\alpha (\alpha - 1) \dots (\alpha - k + 1)}{k!} & k > 0\\
		1 &k=0\\
		0 &k < 0
		\end{array}\right.
		$$@
	设@$\alpha$@是一个任意实数, 则对满足@$|\frac{x}{y}|<1$@的所有x和y, 有
	@$$ (x+y)^{\alpha} = \sum_{k=0}^{\infty}{C_{\alpha}^k x^k y^{\alpha - k}} $$@
	推论: 令@$z=\frac{x}{y}$@,则有
		@$$ (1+z)^{\alpha} = \sum_{k=0}^{\infty}{C_{\alpha}^{k}z^k}, |z|<1 $$@
		令@$\alpha = -n $@(n是正整数),有
		@$$ (1+z)^{-n} = \frac{1}{(1+z)^n} = \sum_{k=0}^{\infty}{(-1)^kC_{n+k-1}^{k}z^k} $$@
		又令z = -rz, (r为非零常数),有
		又令n=1,有
		@$$ \frac{1}{1+z}=\sum_{k=0}^{\infty}{(-1)^kz^k} $$@
		令z = -z, 有
		@$$ \frac{1}{1-z} = \sum_{k=0}^{\infty}{z^k} $$@
		令@$\alpha=\frac{1}{2}$@, 有
		@$$ \sqrt{1+z} = 1 + \sum_{k=1}^{\infty}{\frac{(-1)^{k-1}}{k \cdot 2^{2k-1}}C_{2k-2}^{k-1} z^k} $$@
4. 组合恒等式
@\begin{enumerate}
\item $\sum_{k=0}^n{C_n^k}=2^n$
\item $\sum_{k=0}^n{(-1)^kC_n^k}=0$
\item 对于正整数n和k,$$C_n^k=\frac{n}{k}C_{n-1}^{k-1}	$$
\item 对于正整数n,$$\sum_{k=0}^{n}{kC_n^k}=\sum_{k=1}^{n}{kC_n^k}=n\cdot 2^{n-1}	$$
\item 对于正整数n,$$\sum_{k=0}^{n}{(-1)^k k C_n^k}=0	$$
\item 对于正整数n,$$\sum_{k=0}^{n}{k^2 C_n^k}=n(n+1)2^{n-2}	$$
\item 对于正整数n,$$\sum_{k=0}^{n}{\frac{1}{k+1}C_n^k}=\frac{2^{n+1}-1}{n+1}	$$
\item (Vandermonde恒等式)对于正整数n,m和p,有$p\leq min{m,n}$, $$\sum_{k=0}^{p}{C_n^k C_m^{p - k}} = C_{m+n}^p	$$
\item (令p=m)对于任何正整数n,m,$$\sum_{k=0}^{m}{C_m^k C_n^k} = C_{m+n}^{m}	$$
\item (又令m=n)对于任何正整数n,$$\sum_{k=0}^{n}{(C_n^k)^2} = C_{2n}^{n}	$$
\item 对于非负整数p,q和n,$$\sum_{k=0}^{p}{C_p^k C_q^k C_{n+k}^{p+q}} = C_n^p C_n^q	$$
\item 对于非负整数p,q和n,$$\sum_{k=0}^{p}{C_p^k C_q^k C_{n+p+q-k}^{p+q}}=C_{n+p}^{p} C_{n+q}^{q}	$$
\item 对于非负整数n,k, $$\sum_{i=0}^{n}{C_i^k} = C_{n+1}^{k+1}	$$
\item 对于所有实数$\alpha$和非负整数k,$$\sum_{j=0}^{k}{C_{\alpha + j}^{j}} = C_{\alpha + k + 1}^{k}	$$
\item $$ \sum_{k=0}^{n}{\frac{2^{k+1}}{k+1}C_n^K}=\frac{3^{n+1} - 1}{n+1}	$$
\item $$ \sum_{k=0}^{m}{C_{n-k}^{m-k}} = C_{n+1}^{m}	$$
\item $$ \sum_{k=m}^{n}{C_k^m C_n^k} = C_n^m 2^{n-m}	$$
\item $$	\sum_{k=0}^{m}{(-1)^k C_n^k} = (-1)^m C_{n-1}^m	$$
%\item $$	\sum_{k=0}^{m}{C_m^n C_{n+k}^{m}} = \sum_{k=0}^{m}{C_m^k C_n^k 2^k}	$$
\end{enumerate}
@
*/
