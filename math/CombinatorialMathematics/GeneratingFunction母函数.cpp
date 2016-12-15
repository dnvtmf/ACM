///母函数 Generating Function
/*普通母函数:
定义: 给定一个无穷序列$(a_0, a_1, a_2, \cdots , a_n, \cdots)$(简记为{$a_n$}), 称函数@$$f(x) = a_0 + a_1x^1 + a_2 x^2 + \cdots + a_n x^n + \cdots = \sum_{i=1}^{\infty}{a_i x^i}$$@为序列$\{a_n\}$的普通母函数
常见普通母函数:
	序列$(C_n^0, C_n^1, C_n^2, \cdots , C_n^n)$的普通母函数为$f(x) = (1+x)^n$
	序列$(1, 1, \cdots , 1, \cdots )$的普通母函数为$f(x) = \frac{1}{1-x}$
	序列$(C_{n-1}^0, -C_n^1, C_{n+1}^2, \cdots , (-1)^kC_{n+k-1}^k, \cdots )$的普通母函数为$f(x)=(1+x)^{-n}$
	序列$(C_0^0, C_2^1, C_4^2, \cdots , C_{2n}^n, \cdots , )$的普通母函数为$f(x)=(1-4x)^{-1/2}$
	序列$(0, 1\times 2 \times 3, 2\times 3\times 4, \cdots , n\times (n+1) \times (n+2), \cdots)$的普通母函数为$\frac{6}{(1-x)^4}$
*/
/*指数母函数
定义: 称函数@$$
	f_e(x) = a_0 + a_1 \frac{x^1}{1!} + a_2 \frac{x^2}{2!} + \cdots + a_n \frac{x^n}{n!} + \cdots = \sum_{n=0}^{\infty}{a_n \frac{x^n}{n!}}$$@
	为序列$(a_0, a_1, \cdots , a_n, \cdots)$的指数母函数。
常见指数母函数为:
	序列$(1, 1, \cdots , 1, \cdots)$的指数母函数为$f_e(x) = e^x$
	序列$(P_n^0, P_n^1, \cdots , P_n^n)$的指数母函数为$f_e(x)=(1+x)^n$, n是整数.
	序列$(P_0^0, P_2^1, P_4^2, \cdots , P_{2n}^n, \cdots)$的指数母函数为$f_e(x) = (1-4x)^{-1/2}$
	序列$(1, \alpha , {\alpha}^2, \cdots , {\alpha}^n , \cdots)$的指数母函数为$f_e(x) = e^{\alpha x}$
*/
/*
指数母函数和普通母函数的关系: 对同一序列的$\{a_n\}$的普通母函数$f(x)$和指数母函数$f_e(x)$有:@$$f(x) = \int_{0}^{\infty}{e^{-s}f_e(sx){\rm d}s}$$@

母函数的基本运算:
	设A(x), B(x), C(x)分别是序列$(a_0, a_1, \cdots, a_r, \cdots), (b_0, b_1, \cdots , b_r, \cdots ),(c_0,c_1, \cdots ,c_r, \cdots)$的普通(指数)母函数, 则有:
	C(x) = A(x) + B(x) 当且仅当对所有的i, 都有$c_i = a_i + b_i(i=0,1,2,\cdots ,r, \cdots).$
	C(x) = A(x)B(x) 当且仅当对所有的i, 都有$c_i=\sum_{k=0}^{i}{a_k b_{i-k}}(i=0,1,2,\cdots , r,\cdots )$.
*/
/*母函数在组合排列上的应用
	从n个不同的物体中允许重复地选取r个物体, 但是每个物体出现偶数次的方式数.
	@$$f(x) = (1+x^2 + x^4 + \cdots )^n = (\frac{1}{1-x^2})^n = \sum_{r=0}^{\infty}{C_{n+r-1}^{r} x^{2r}}$$@
	故答案为$a_r = C_{n+r-1}^{r}$
*/
