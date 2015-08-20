///二分图的最小点权覆盖集与最大点权独立集 Minimum Weight Vertex Covering Set and Maximum Weight Vertex Independent Set in a Bipartite Graph
/*定义:
点覆盖集 (vertex covering set, VCS) 是无向图的G的一个点集, 使得该图中所有边都至少有一个端点在该集合内. 形式化的定义: 点覆盖集为 $V' \in V$, 满足对于$\forall (u, v) \in E$, 都有 $u \in V'$ 或 $v \in V'$.
点独立集 (vertex independent set, VIS) 是无向图的G的一个点集, 使得任意两个在该集合中的点在原图中都不相邻, 即导出子图为零图(没有边)的点集. 形式化的定义: 点独立集是$V' \in V$, 满足$\forall u, v \in V'$, 都有$(u, v) \not \in E$成立. 等价的定义: 点独立集为$V' \in V$, 满足$\forall (u, v) \in E$, 都有$u \in V'$与$v \in V'$不同时成立.
最小点覆盖集 (minimum vertex covering set, MinVCS) 是在无向图G中, 点数最少的点覆盖集.
最大点独立集 (maximum vertex independent set, MaxVIS) 是在无向图G中, 点数最多的点独立集.
一个带点权无向图$G = (V, E)$, 对于$\forall v \in V$, 都被分配一个非负点权$w_v$.
最小点权覆盖集 (minimum weight vertex covering set, MinWVCS) 是在带点权无向图G中, 点权之和最小的点覆盖集.
最大点权独立集 (maximum weight vertex independent set, MaxWVIS) 是在带点权无向图G中, 点权之和最大的点独立集.
带权二分图$G = (V, E)$中, 其中$V = X \cup Y, X \cap Y = \varnothing$, 且对于$\forall v \in V$, 都被分配了一个非负的权值$w_v (w_v \geq 0)$.
*/
/*二分图的最小点权覆盖集算法 Algorithm for MinWVCS in a Bipartite Graph
考虑二分图的网络流解法, 它加入了额外的源s和汇t, 将匹配以一条条$s-u-v-t$形式的流路径"串联"起来.
同样, 如上建图, 建立一个源s, 向X部每个点连边; 建立一个汇t, 从Y部每个点向汇t连边. 把二分图看做有向的, 则任意一条从s到t的路径, 一定具有$s-u-v-t$的形式. 割的性质是不存在一条从s到t的路径, 故路径上的三条边$(s, u), (u, v), (v, t)$中至少有一条在割中. 若人为的令边$(u, v)$不在最小割中, 则令其容量为正无限$c(u, v) = +\infty$, 则条件简化为 $(s, u), (v, t)$至少有一条边在最小割中, 正好和点覆盖集的形式相对应($u \in V'$或$v \in V'$).
将二分图G的最小点权覆盖向网络$N=(V_N, E_N)$的最小割模型的转化:
	在图G的基础上添加源s和汇t; 将每条二分图的边替换为容量为$c(u, v) = \infty$的有向边$(u, v) \in E_N$; 增加源s到X部的点u的有向边$(s, u) \in E_N$, 容量即为改点的权值$c(s, u) = w_u$; 增加Y部的点v到汇t有向边的$(v, t) \in E_N$, 同样容量为该点的权$c(v, t) = w_v$.
引理: 网络N的简单割[S, T]与图G的点覆盖集$V' = X' \cup Y'$存在一一对应关系: 点覆盖集中的点在网络N中相应的带权边组成一个简单割; 反之亦然, 即: @$$
		[S, T] = [{s}, X'] \cup [Y', {t}]$$@
由于最小点覆盖和最小割的优化方向一致, 故带权二分图的最小点覆盖转化为最小割模型.
复杂度: $O(MaxFlow(N))$
*/
/*二分图的最大点权独立集算法 Algorithm for MaxWVIS in a Bipartite Graph
点独立集定义重写, 可以得到其补图的点覆盖集定义. 即@$$
	\overline{u \in V' \and v \in V'} = u \in \overline{V'}\  or\  v \in \overline{V'}$$@
定理 (覆盖集与独立集互补定理): 若$\overline{V'}$为不含孤立点的任意图的一个点覆盖集当且仅当V'是该图的一个点独立集.
推论 (最优性)若V'为不含孤立点的任意图的一个最小点权覆盖集, 则$\overline{V'}$就是该图的一个最大点权独立集.
求出最大点权独立点集后还有加上反图中的孤立点才是答案.
复杂度: $O(MaxFlow(N))$
*/
