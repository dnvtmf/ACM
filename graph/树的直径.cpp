///树的直径
//树的直径是指树的最长简单路
/*方法一: $O(|E|)$
两遍BFS, 先任选一个起点找到最长路的终点, 再从终点进行BFS, 第二次找到的最长路即为树的直径.
*/
int dist[MAXV];
int bfs(int s)
{
    memset(dist, -1, sizeof(dist));
    queue<int> que;
    dist[s] = 0;
    que.push(s);
    int mx = 0, ed = s;
    while(!que.empty())
    {
        int u = que.front(); que.pop();
        for(int i = head[u]; ~i; i = e[i].next)
        {
            if(dist[e[i].to] != -1) continue;
            dist[e[i].to] = dist[u] + 1;
            if(dist[e[i].to] > mx) mx = dist[ed = e[i].to];
            que.push(e[i].to);
        }
    }
    return ed;
}

/*方法二: $O(|E|)$
树的直径为某个点的最长距离与次长距离之和
*/
