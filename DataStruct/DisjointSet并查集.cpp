//并查集 Disjoint Set
int father[MAX], rk[MAX];
void init()
{
    for(int i = 0; i < MAX; i++)
    {
        father[i] = i;
        rk[i] = 0;
    }
}
int find(int x)
{
    return father[x] == x ? x : father[x] = find(father[x]);
}
void gather(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y)	 return;
    if(rk[x] > rk[y])  father[y] = x;
    else
    {
        if(rk[x] == rk[y]) rk[y]++;
        father[x] = y;
    }
}

bool same(int x, int y)
{
    return find(x) == find(y);
}
