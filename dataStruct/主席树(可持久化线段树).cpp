/*
主席树(可持久化线段树, 函数式线段树)
利用线段树保持历史版本, 每次更新时新建结点再更新.
*/
struct node
{
    int ch[2];
    int val;
};
struct ChairTree
{
    int Root[MAXV], tot;
    node maxv[MAXV * 25];
    void init()
    {
        tot = 0;
        Root[0] = tot++;
        memset(maxv, -1, sizeof(maxv));
    }
    void update(int x, int l, int r, int L, int R, int val);//区间更新
    int query(int x, int l, int r, int pos);//点查询
} pt;

//pt.maxv[pt.Root[newV] = pt.tot++] = pt.maxv[pt.Root[oldV]];
void ChairTree::update(int x, int l, int r, int L, int R, int val)
{
    if(L <= l && r <= R)
    {
        maxv[x].val = max(maxv[x].val, val);
        return ;
    }
    int mid = (l + r) >> 1;
    if(L <= mid)
    {
        if(maxv[x].ch[0] == -1)
        {
            maxv[tot].val = maxv[x].val;
            maxv[x].ch[0] = tot++;
            maxv[tot].val = maxv[x].val;
            maxv[x].ch[1] = tot++;
        }
        else
        {
            maxv[tot] = maxv[maxv[x].ch[0]];
            maxv[x].ch[0] = tot++;
        }
        update(maxv[x].ch[0], l, mid, L, R, val);
    }
    if(R > mid)
    {
        if(maxv[x].ch[1] == -1)
        {
            maxv[tot].val = maxv[x].val;
            maxv[x].ch[0] = tot++;
            maxv[tot].val = maxv[x].val;
            maxv[x].ch[1] = tot++;
        }
        else
        {
            maxv[tot] = maxv[maxv[x].ch[1]];
            maxv[x].ch[1] = tot++;
        }
        update(maxv[x].ch[1], mid + 1, r, L, R, val);
    }
    maxv[x].val = -1;
}

//x = pt.Root[pt.queryV]
int ChairTree::query(int x, int l, int r, int pos)
{
    if(l <= pos && pos <= r && maxv[x].val > 0) return maxv[x].val;
    int mid = (l + r) >> 1;
    if(pos <= mid) return query(maxv[x].ch[0], l, mid, pos);
    else return query(maxv[x].ch[1], mid + 1, r, pos);
}
