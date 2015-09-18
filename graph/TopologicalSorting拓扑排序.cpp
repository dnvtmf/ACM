///拓扑排序 (Topological Sorting)
//有向无环图 $O(|E| + |V|)$
/*算法:
	1. 选择没有前驱(入度为0)的顶点v, 并输出
	2. 删除从v出发的所有有向边
	3. 重复前两步, 直至没有入度为0的顶点
	4. 如果最后还剩下一些顶点, 这该图不是DAG
*/
const int MAXV = 1000;
int V;//顶点数
int deg[MAXV];//入度
int ans[MAXV];//拓扑排序结果
bool TopoSort()
{
    int top = 0, tail = 0;
    for(int i = 0; i <= V; ++i)
    {
        if(deg[i] == 0)
            ans[top++] = i;
    }
    while(tail < top)
    {
        for(int i = head[tail++]; ~i; i = e[i].next)
        {
            if(--deg[e[i].to] ==  0)
                ans[top++] = e[i].to;
        }
    }
    return top == V;
}
