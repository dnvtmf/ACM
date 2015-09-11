///伸展树Splay
//均摊复杂度O(log n) 最坏复杂度O(n)
/*操作
1. 旋转: 左右旋, 将左（右）孩子变为根
2. spaly: 将结点x旋转至根y处
3. find: 同二叉树查找, 查找成功后splay
4. remove: 查找x, 如果x无孩子或一个孩子, 删除x, splay（x）的根结点; x有两个孩子, 用x的后继y代替x, splay（y)
5. join, split合并, 分解数.
6. 区间操作: [a, b], 将a-1 splay至根处, b+1至根的右孩子处, 那根的右孩子的左子树表示区间[a, b]
*/
const int NUM = 1000000 + 10;
struct Splay_node
{
    int ch[2], fa;
    int key;
    int len;
    bool flag;
    LL val, sum;
    void malloc(int _key)
    {
        ch[0] = ch[1] = fa = 0;
        key = _key;
        len = 1;
        flag = false;
        val = sum = 0;
    }
};
struct Splay
{
    Splay_node *e;
    int tot;
    int root;
    Splay()
    {
        e = new Splay_node[NUM];
        tot = 0;
        root = -1;
    }
    ~Splay()
    {
        delete []e;
    }
    void push_down(int x)//标记下传
    {
        if(e[x].flag)
        {
            int y = e[x].ch[0];
            if(y)
            {
                e[y].flag = true;
                e[y].val = e[x].val;
                e[y].sum = e[y].val * e[y].len;
            }
            y = e[x].ch[1];
            if(y)
            {
                e[y].flag = true;
                e[y].val = e[x].val;
                e[y].sum = e[y].val * e[y].len;
            }
            e[x].flag = false;
        }
    }
    void push_up(int x)//标记上传
    {
        e[x].sum = e[x].val;
        e[x].len = 1;
        if(e[x].ch[0])
        {
            e[x].sum += e[e[x].ch[0]].sum;
            e[x].len += e[e[x].ch[0]].len;
        }
        if(e[x].ch[1])
        {
            e[x].sum += e[e[x].ch[1]].sum;
            e[x].len += e[e[x].ch[1]].len;
        }
    }
    //旋转操作: c = 0: 左旋, 将父节点旋转到结点x的左儿子; c = 1: 右旋, 将父节点旋转到结点x的右儿子
    void rot(int x, int c)
    {
        int y = e[x].fa, z = e[y].fa;
        push_down(y), push_down(x);
        e[y].ch[!c] = e[x].ch[c];
        if(e[x].ch[c]) e[e[x].ch[c]].fa = y;
        e[y].fa = x;
        if(z) e[z].ch[e[z].ch[1] == y] = x;
        e[x].ch[c] = y;
        e[x].fa = z;
        push_up(y);
        if(y == root) root = x;
    }
    //splay操作: 将结点x旋转到结点fa下面
    void splay(int x, int fa)
    {
        int y, z;
        push_down(x);
        while((y = e[x].fa) != fa)
        {
            z = e[y].fa;
            if(z == fa) rot(x, e[y].ch[0] == x);//单旋
            else
            {
                if(e[z].ch[0] == y)
                {
                    if(e[y].ch[0] == x) rot(y, 1), rot(x, 1);//一字旋
                    else rot(x, 0), rot(x, 1);//之字旋
                }
                else
                {
                    if(e[y].ch[1] == x) rot(y, 0), rot(x, 0);//一字旋
                    else rot(x, 1), rot(x, 0);//之字旋
                }
            }
        }
        push_up(x);
    }
    void insert(int key)
    {
        int x = ++tot;
        e[x].malloc(key);
        int y = root;
        if(y == -1)
        {
            root = x;
            e[x].fa = 0;
            return ;
        }
        while(true)
        {
            if(e[y].key < key)
            {
                if(e[y].ch[1]) y = e[y].ch[1];
                else
                {
                    e[y].ch[1] = x;
                    e[x].fa = y;
                    splay(x, 0);
                    return ;
                }
            }
            else if(e[y].key > key)
            {
                if(e[y].ch[0]) y = e[y].ch[0];
                else
                {
                    e[y].ch[0] = x;
                    e[x].fa = y;
                    splay(x, 0);
                    return ;
                }
            }
            else
                return ;
        }
    }
    int find(int key)
    {
        int x = root;
        while(e[x].key != key)
        {
            x = e[x].ch[e[x].key < key];
            if(!x)//没有找到
                return -1;
        }
        return x;
    }
    void update(int L, int R, LL val)
    {
        splay(find(L - 1), 0);
        splay(find(R + 1), root);
        int x = e[e[root].ch[1]].ch[0];
        e[x].flag = true;
        e[x].val = val;
        e[x].sum = val * e[x].len;
    }
    LL query(int L, int R)
    {
        splay(find(L - 1), 0);
        splay(find(R + 1), root);
        int x = e[e[root].ch[1]].ch[0];
        return e[x].sum;
    }
};
