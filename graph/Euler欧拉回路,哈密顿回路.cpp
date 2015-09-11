///欧拉回路 Euler
/*
定义: 寻找一条回路, 经过且仅经过一次所有边, 最后回到出发点
存在的充要条件: 1. 该图是连通的 2. 无向图, 度数为奇数的顶点的个数为0; 有向图, 每个顶点入度等于出度
构造算法: $O(|E|)$
	1. 深度搜索, 得出一条回路.
	2. 如果该回路不是欧拉回路, 则沿该回路回溯, 找到一个没有搜索过的顶点, 重复步骤1, 然后将新回路加入答案中.
定义欧拉路径: 寻找一条简单路径, 经且仅经过所有边一次
存在条件: 连通, (无向图)度数为奇数的顶点个数为0或2, (有向图)只有两个顶点入度不等于出度, 且一个入度比出度大1, 另一个小1.
*/
#define MAXE
int ans[MAXE], ansi;//ansi等于V表示存在欧拉回路
bool vis[2 * MAXE];
void dfs(int u)
{
    for(int i = head[u]; ~i; i = e[i].next)//链式前向星存储
    {
        if(vis[i]) continue;
        vis[i ^ 1] = vis[i] = true;//标记当前边及反向边
        dfs(e[i].to);
        ans[ansi++] = i;//沿回溯道路将经过的每个点加入答案
    }
}
///有向图欧拉路径
int in[MAX_V], out[MAX_V];//入度和出度
int num;//已经有多少边在欧拉路径中
int pre_edge[MAX_E];//存储每一条边的上一条边
//通过入度和出度判定是否可能存在欧拉路径, 存在返回起点, 否则返回-1
int is_exist_euler()
{
    int sp = -1, tp = -1;
    bool flag = true;
    for(int i = 0; flag && i < V; ++i)
    {
        if(in[i] == out[i]) continue;
        if(in[i] - out[i] == 1)
        {
            if(tp == -1) tp = i;
            else flag = false;
        }
        else if(out[i] - in[i] == 1)
        {
            if(sp == -1) sp = i;
            else flag = false;
        }
        else flag = false;
    }
    if(!flag) return -1;
    if(sp < 0 && tp >= 0) return - 1;
    if(sp >= 0 && tp < 0) return -1;
    if(sp < 0 && tp < 0)
    {
        int i = 0;
        while(sp == -1)
        {
            if(head[i] != -1)
            {
                sp = i;
            }
            i++;
        }
    }
    if(!flag)
        sp = -1;
    return sp;
}
int find_path(int u, int pree)
{
    //寻找以u为起点的一条边
    int i;
    while(head[u] != -1)
    {
        i = head[u];
        pre_edge[i] = pree;//加入改变进欧拉路径
        pree = i;
        head[u] = e[i].next;//将已经访问过的边去掉
        u = e[i].v;//要访问的下一个结点
        num++;
    }
    return pree;//访问当前路径最后一条边
}
//存在欧拉路径返回最后一条边的编号, 否则返回-1
int oula_path()
{
    int st = is_exist_euler();//判断是否可能存在欧拉路径
    if(st == -1) return -1;
    num = 0;
    int ed = find_path(st, -1);//找到基础路径
    int ei = ed;
    while(ei >= 0)
    {
        if(head[e[ei].u] != -1)
        {
            pre_edge[ei] = find_path(e[ei].u, pre_edge[ei]);//寻找环
        }
        ei = pre_edge[ei];
    }
    if(num != E)//可能存在其他连通块
        return -1;
    return ed;
}
///哈密顿回路(Hamilton)
/*
定义: 寻找一条回路, 经且仅经过每个顶点一次, 最后回到出发点.
存在的充分条件: 任意两个不同顶点的度数和大于等于顶点数V.
构造算法: $O(|V|^2)$
	1. 任找两个相邻顶点S, T
	2. 分别向两头扩展至无法扩展为止, 称头尾结点为S, T
	3. 若S, T不相邻, 在路径$S \to T$中找到结点$V_i$, 其中$V_i$与T相邻, V$_{i+1}$与S相邻, 令$S \to T $变为$S \to V_i \to T \to V_{i+1}$.
	4. ($S \to T$已为回路)若$S\to T$中顶点个数不为V, 找$S \to T$中找到顶点$V_i$, 其中$V_i$与一个未访问过得顶点相邻, 从$V_i$处断开(S为$V_i$, T为$V_{i+1}$,重复2.
*/
#define MAXV
int V;
int ans[MAXV];
bool G[MAXV][MAXV];//邻接矩阵存储
bool vis[MAXV];

void Hamilton()
{
    int s = 1, t;
    int ansi = 2;
    int i, j;
    memset(vis, false, sizeof(vis));
    for(i = 1; i <= V; i++) if(G[s][i]) break;
    t = i;
    ans[0] = s, ans[1] = t;
    while(1)
    {
        while(1)
        {
            for(i = 1; i <= V; i++)
                if(G[t][i] && !vis[i])
                {
                    ans[ansi++] = i;
                    vis[i] = true;
                    t = i;
                    break;
                }
            if(i > V)break;
        }
        reverse(ans, ans + ansi);
        swap(s, t);
        while(1)
        {
            for(i = 1; i <= V; i++)
                if(G[t][i] && !vis[i])
                {
                    ans[ansi++] = i;
                    vis[i] = true;
                    t = i;
                    break;
                }
            if(i > V)break;
        }
        if(!G[s][t])
        {
            for(i = 1; i < ansi - 2; i++)if(G[s][ans[i + 1]] && G[ans[i]][t]) break;
            t = ans[++i];
            reverse(ans + i, ans + ansi);
        }
        if(ansi == V)return ;
        for(j = 1; j <= V; j++)
            if(!vis[j])
                for(i = 1; i < ansi - 2; i++)if(G[ans[i]][j])break;
        s = ans[i - 1];
        t = j;
        reverse(ans, ans + i);
        reverse(ans + i, ans + ansi);
        ans[ansi++] = j;
        vis[j] = true;
    }
}
