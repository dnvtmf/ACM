///随机化二叉树Treap
//数组版
struct node
{
    int key;
    int ch[2], fix;
};
struct Treap
{
    node *p;
    int size, root;
    Treap()
    {
        p = new node[NUM];
        srand(time(0));
        size = -1;
        root = -1;
    }
    ~Treap() {delete []p;}
    void rot(int &x, int op)//op = 0 左旋, op = 1右旋
    {
        int y = p[x].ch[!op];
        p[x].ch[!op] = p[y].ch[op];
        p[y].ch[op] = x;
        x = y;
    }
    //如果当前节点的优先级比根大就旋转, 如果当前节点是根的左儿子就右旋如果当前节点是根的右儿子就左旋.
    void insert(int tkey, int &k = root)
    {
        if(k == -1)
        {
            k = ++size;
            p[k].ch[0] = p[k].ch[1] = -1;
            p[k].key = tkey;
            p[k].fix = rand();
        }
        else if(tkey < p[k].key)
        {
            insert(tkey, p[k].ch[0]);
            if(p[p[k].ch[0]].fix > p[k].fix)
                rot(k, 1);
        }
        else
        {
            insert(tkey, p[k].ch[1]);
            if(p[p[k].ch[1]].fix > p[k].fix)
                rot(k, 0);
        }
    }
    void remove(int tkey, int &k)//把要删除的节点旋转到叶节点上, 然后直接删除
    {
        if(k == -1) return ;
        if(tkey < p[k].key)
            remove(tkey, p[k].ch[0]);
        else if(tkey > p[k].key)
            remove(tkey, p[k].ch[1]);
        else
        {
            if(p[k].ch[0] == -1 && p[k].ch[1] == -1)
                k = -1;
            else if(p[k].ch[0] == -1)
                k = p[k].ch[1];
            else if(p[k].ch[1] == -1)
                k = p[k].ch[0];
            else if(p[p[k].ch[0]].fix < p[p[k].ch[1]].fix)
            {
                rot(k, 0);
                remove(tkey, p[k].ch[0]);
            }
            else
            {
                rot(k, 1);
                remove(tkey, p[k].ch[1]);
            }
        }
    }
};
//指针版
