///分数规划  Fractional Programming
//source: <<最小割模型在信息学竞赛中的应用>>
/*
一般形式: $\min{\{\lambda = f( \overrightarrow{x}) = \frac{a(\overrightarrow{x})}{b(\overrightarrow{x})}\}}(\overrightarrow{x} \in S, \forall \overrightarrow{x} \in S, b(\overrightarrow{x}) > 0)$
	其中解向量$\overrightarrow{x}$在解空间S内, $a(\overrightarrow{x})$与$b(\overrightarrow{x})$都是连续的实值函数。
	解决分数规划问题的一般方法是分析其对偶问题，还可进行参数搜索(parametric search)，即对答案进行猜测， 在验证该猜测值的最优性, 将优化问题转化为判定性问题或者其他优化问题.
	构造新函数:$\displaystyle g(\lambda)=\min{\{a(\overrightarrow{x}) - \lambda \cdot b(\overrightarrow{x})\}}(\overrightarrow{x} \in S)$
	函数性质:(单调性) $g(\lambda)$是一个严格递减函数， 即对于$\lambda_1 < \lambda_2$, 一定有$g(\lambda_1) > g(\lambda_2)$.
	(Dinkelbach定理) 设$\lambda^*$为原规划的最优解， 则$g(\lambda)=0$当且仅当$\lambda = \lambda^*$.
	设$\lambda^*$为该优化的最优解， 则:@$$\left\{ \begin{array}{c}
		g(\lambda)=0 \Leftrightarrow \lambda = \lambda^*\\
		g(\lambda)<0 \Leftrightarrow \lambda > \lambda^*\\
		g(\lambda)>0 \Leftrightarrow \lambda < \lambda^*
	\end{array}\right.$$@
	由该性质， 就可以对最优解$\lambda^*$进行二分查找。
	上述是针对最小化目标函数的分数规划，实际上对于最大化目标函数也一样适用.
*/
///0-1分数规划 0-1 fractional programming
/*是分数规划的解向量$\overrightarrow{x}$满足$\forall x_i \in \{0,1\}$, 即一下形式：@$$\min{\{ \lambda = f(x) = \frac{\sum_{e \in E}{w_e x_e}}{\sum_{e \in E}{1 \cdot x_e}} = \frac{\overrightarrow{w} \cdot \overrightarrow{x}}{\overrightarrow{c} \cdot \overrightarrow{x}} \}}$$@
	其中, $\overrightarrow{x}$表示一个解向量, $x_e \in\{0, 1\}$, 即对与每条边都选与不选两种决策, 并且选出的边集组成一个s-t边割集. 形式化的, 若$x_e = 1$， 则$e \in C$, $x_e = 0$, 则$e \not \in C$.
*/
