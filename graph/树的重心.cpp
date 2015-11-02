///树的重心
/*
定义:
	找到一个点, 其所有的子树中最大的子树节点数最少, 那么这个点就是这棵树的重心, 删去重心后, 生成的多棵树尽可能平衡.
性质:
	树中所有点到某个点的距离和中, 到重心的距离和是最小的; 如果有两个重心, 那么他们的距离和一样.
	把两个树通过一条边相连得到一个新的树, 那么新的树的重心在连接原来两个树的重心的路径上.
	把一个树添加或删除一个叶子, 那么它的重心最多只移动一条边的距离.
应用:
	树的重心在树的点分治中有重要的作用, 可以避免 $N^2$ 的极端复杂度(从退化链的一端出发), 保证 $N\log{N}$ 的复杂度.
求法:
	利用树型dp可以很好地求树的重心.
*/

int sz[NUM];//每棵子树中的结点数
int mx_cnt[NUM], root;//每个结点的儿子所在子树的最大结点数. root为所求重心
void getCenter(int u, int fa = -1)
{
    //sz[u] = 1;
    mx_cnt[u] = 0;
    for(int i = head[u]; ~i; i = e[i].next)
    {
        if(e[i].to == fa) continue;
        getCenter(e[i].to, u);
        //sz[u] += sz[e[i].to];
        mx_cnt[u] = max(mx_cnt[u], sz[e[i].to]);
    }
    mx_cnt[u] = max(mx_cnt[u], n - sz[u]);
    if(mx_cnt[u] < mx_cnt[root]) root = u;
}
