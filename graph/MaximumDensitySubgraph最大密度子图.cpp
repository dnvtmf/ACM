///最大密度子图 a Maximum Density Subgraph
/*
定义:
	定义无向图$G=(V, E)$的密度(density)D 为该图的边数$|E|$与该图的点数$|V|$的比值$\displaystyle D = \frac{|E|}{|V|}$.
	给一个无向图$G=(V, E)$, 其中具有最大密度的子图$G'=(V', E')$, 称为最大密度子图(maximum density subgraph), 即最大化$\displaystyle D' = \frac{|E'|}{|V'|}$.
*/
/*
做法:
	先转化为分数规划, 在转化为最小割即可.
*/
