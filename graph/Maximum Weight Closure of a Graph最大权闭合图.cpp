///最大权闭合图 Maximum Weight Closure of a Graph
/*定义:
定义一个有向图G(V, E)的闭合图(closure)是该有向图的一个点集, 且该点集的所有出边都还指向该点集. 即闭合图内的任意点的任意后继也一定在闭合图中. 更形式化地说, 闭合图是这样的一个点集$V' \in V$，满足对于$\forall u \in V'$引出的$\forall <u,v> \in E$, 必有$v \in V'$成立. 还有一种等价定义为: 满足对于$\forall <u, v> \in E$ , 若有$u \in V'$成立，必有$v \in V'$成立, 在布尔代数上这是一个"蕴含(imply)"的运算. 按照上面的定义，闭合图是允许超过一个连通块的.给每个点v分配一个点权$w_v$(任意实数, 可正可负). 最大权闭合图(maximum weight closure), 是一个点权之和最大的闭合图，即最大化$\displaystyle \sum_{v\in V'}{w_v}$.
*/
/*转化为最小割模型$G_N(V_N, E_N)$
在原图点集的基础上增加源s和汇t; 将原图每条有向边$<u, v> \in E>$替换为容量为$c(u, v) = \infty$的有向边$<u, v> \in E_N$; 增加连接源s到原图每个正权点$v(w_v > 0)$的有向边$<s, v> \in E_N$, 容量为$c(s, v) = w_v$, 增加连接原图每个负权点$v(w_v < 0)$到汇t的有向边$<v, t> \in E_N$, 容量为$c(v, t) = -w_v$. 其中, 正无限$\infty$定义为任意一个大于$\sum_{v\in V}{|w_v|}$的整数。更形式化地, 有:@$$ V_N = V \cup \{s, t\} $$@@$$	E_N = E \cup \{<s, v> | v \in V, w_v > 0\} \cup \{<v, t> | v \in V, w_v < 0\}$$@@$$	\left\{ \begin{array}{l l}
			c(u, v) = \infty &<s, v> \in E \\
			c(s, v) = w_v & w_v > 0 \\
			c(v, t) = -w_v & w_v < 0
		\end{array} \right.$$@
	当网络N的取到最小割时, 其对应的图G的闭合图将达到最大权.
*/
