/*群
定义: 给定一个非空集合G及G上的二元运算 $\ast$, 如果满足:
	1. 封闭性
	2. 结合律成立
	3. 存在幺元e
	4. G中每个元素都存在逆元.
	则称G关于运算 $\ast$ 作为一个群, 简称G是一个群, 记作 $<G, \ast>$.
若群满足交换律, 则称为交互群, 或Abel群.
性质:
	1. $e^{-1} = e$
	2. G中幺元唯一, 每个元的逆元唯一.
	3. G中消去律成立, 即对 $\forall a, b, c \in G$, 若 ab=bc 或ba = ca, 则必有 b = c.
	4. $\forall a, b \in G$, 有$(ab)^{-1} = b^{-1} a^{-1}$.
设 G 是一个群, e为其幺元, 对 $a \in G$, n为正整数, 定义:
	1. $a^0 = e$
	2. $a^n = a^{n-1} \ast a$
	3. $a^{-n} = (a^{-1})^n$
性质: $a^m a^n = a^{m+n}, (a^m)^n = a^{mn}$, m, n是整数.
若H是G的非空子集, $<H, \ast>$ 也是一个群, 则称 $<H, \ast>$ 是 $<G, \ast>$ 的一个子群.
*/
/*置换群
定义: 有限集和A上的一个双射(一一对应) $\sigma$ 称为A上的一个置换.
	使集合A上的任何元不动的置换, 成为A上的恒等置换, 即为I. 即对 $\forall x \in A$, 均有 $I(x) = x$.
	存在逆置换. 置换的乘法$\tau(\sigma(x)) = (\tau \cdot \sigma)(x)$. 置换的乘法满足结合律.
定理: 设 $S_n$ 为n元集合A上的所有置换构成的集合, 对置换的乘法构成一个 n! 阶的群, 称为n次对称群.

定义: 设 $\sigma$ 是A上的一个置换, 若存在A中k个元素 $a_1, a_2, \cdots, a_k$, 使得 $\sigma(a_1) = a_2, \sigma(a_2) = a_3, \cdots, \sigma(a_{k_1}) = a_k, \sigma(a_k) = a_1$, 且对A中其他元素x, 均有 $\sigma(x) = x$, 则称 $\sigma$ 为一个长为k的循环, 简称k-循环或循环, 记为 $(a_1 a_2 \cdots a_k)$.

定理: 任一置换可分解为若干个不相交的循环. (且这种表示是唯一的, 除了循环的次序可以交换外)
例: 置换 (6 5 7 4 1 2 3) 可分解为循环 (1 6 2 5)(3 7)(4)

定义: 长度为2的循环称为对换.
定理: 任意的循环均可表为一些对换的乘积.
推论: 任一置换均可表为一些对换的乘积. (置换表为对换的乘积的表法不唯一, 但是对换个数的奇偶性不变.)
定义: 分解为兑换的个数为偶(奇)数个的置换称为偶(奇)置换.
两置换的奇偶性与其乘积的奇偶性的关系:
	偶 $\times$ 偶 = 偶, 奇 $\times$ 奇 = 奇, 奇 $\times$ 偶 = 奇, 偶 $\times$ 奇 = 奇.
定理: 设 $A_n$ 为n元集A上的全体偶置换构成的集合, n > 1, 则对置换的乘法, $A_n$ 构成一个 $\frac{n!}{2}$ 阶的$S_2$的子群, 称为n次交代群.
置换的格式: 用符号 $(k)^{c_k}$ 表示 $\sigma$ 中k-循环出现了 $c_k$ 次, 则 $\sigma$ 的结式为: $(1)^{c_1} (2)^{c_2} \cdots (n)^{c_n}$.
给定n次对称群 $S_n$, 令
	$[(1)^{c_1} (2)^{c_2} \cdots (n)^{c_n}] = \{\sigma | \sigma \in S_n, \sigma$ 的格式为 $(1)^{c_1} (2)^{c_2} \cdots (n)^{c_n}\}$.
	称以上的集合为 $S_n$ 的一个共轭类.
显然有, $\displaystyle \sum_{k=1}^{n}{k c_k} = n$
定理: 对n次对称群 $S_n$ @$$
	|[(1)^{c_1} (2)^{c_2} \cdots (n)^{c_n}]| = \frac{n!}{c_1! c_2! \cdots c_n! 1^{c_1} 2^{c_2} \cdots n^{c_n}}$$@
*/
/*Burnside引理
等价关系: 满足自反性, 对称性, 传递性的关系称为等价关系.
定义: 设R是集合A上的等价关系, $a \in A$, 称 $[a] = {x | x \in A \cap <a, x> \in R}$ 为a关于R的等价类, 简称含a的等价类, a称为代表元.
性质: $[a] \neq \varnothing; \cup_{x \in A}[x] = A; a \in [b] \Leftrightarrow [a] = [b]; a \not \in [b] \Leftrightarrow [a] \cap [b] = \varnothing$
k不动置换类: 若k是1到n中的某个整数, G中使k保持不变的置换全体, 记为 $G_k$, 叫做G中使k保持不动的置换类.
	$G_k$ 是G的一个子群.
定理: $|[k]||G_k| = |G|, k = 1, 2, 3, \cdots n$

Burnside引理: 设G是 $N={1, 2, \cdots, n}$ 的一个置换群, G在N上可引出不同的等价类, 其中不同等价类的个数为: @$$
		\frac{1}{|G|}\sum_{\tau \in G}{c_1(\tau)}$$@
	其中, $c_1(\tau)$ 是置换 $\tau$ 中1-循环个数.
*/
/*Polya定理
Polya定理: 设 $G=\{a_1, a_2, \cdots, a_g\}$ 是n个对象的置换群, 用m种颜色给这n个对象着色, 则本质上不同的着色方案数为: @$$
	\frac{1}{|G|}\{m^{c(a_1)} + m^{c(a_2)} + \cdots + m^{c(a_g)}\}$$@
	其中 $c(a_i)$ 为置换 $\sigma_i$ 中所含的不相交的循环的个数
*/
/*母函数型的Polya定理
设N是n个对象的集合, G是N上的置换群, 用m种色 $b_1, b_2, \cdots, b_m$ 对n个对象着色, 则着色方案的列举可为: @$$
	P = \frac{1}{|G|}\sum_{\sigma \in G}{s_1^{c_1(\sigma)} s_2^{c_2(\sigma)} \cdots s_n^{c_n(\sigma)}}$$@
	其中 $c_k(\sigma)$, 为 $\sigma$中k-循环的个数, 令 @$$
		s_k = b_1^k + b_2^k + \cdots b_m^k, k = 1, 2, \cdots, n$$@
	展开P后合并同类项后, $b_1^{i_1} b_2^{i_2} \cdots b_m^{i_m}$ 前的系数即为 $i_1$个对象涂 $b_i$ 色, $i_2$个对象涂 $b_2$ 色, $\cdots$,  $i_m$个对象涂 $b_m$ 色的本质不同的着色方案数, 其中 $i_1 + i_2 + \cdots + i_m = n$.
*/
