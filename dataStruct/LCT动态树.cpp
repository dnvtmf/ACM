///动态树问题(Dynamic Tree Problems)
///数据结构: (Link-cut Tree LCT)
//功能: 支持对树的分割, 合并, 对某个点到它的根的路径的某些操作, 以及对某个点的子树进行的某些操作. (同时维护树的形态)
/*定义:
	如果刚刚执行了对某个点的access操作, 则称一个点被访问过;
	结点v的子树中, 如果最后被访问访问的结点在子树w中, 这里w是v的儿子, 那么称w是v的Preferred Child. 如果最后被访问的结点是v本身, 则v没有Preferred Child.
	每个结点到它的Preferred Child的边称作Preferred Edge.
	由Preferred Edge连接成的不可再延伸的路径称为Preferred Path.
	这棵树就被划分成若干条Preferred Path, 对于每一条Preferred Path, 用其结点的深度做关键字, 用Splay Tree树维护它, 称这棵树为 Auxiliary Tree.
	用 Path Parent 来记录每棵 Auxiliary Tree 对应的 Preferred Path 中的最高点的父亲结点, 如果这个 Preferred Path 的最高点就是根结点, 那么令这棵 Auxiliary Tree 的 Path Parent 为 null.
	Link-Cut Trees 就是将要维护的森林中的每棵树 T 表示为若干个 Auxiliary Tree, 并通过 Path Parent 将这些 Auxiliary Tree 连接起来的数据结构.
*/
/*操作:
	parent(v): 返回结点v的父亲, 如果是根结点, 返回null.
	access(v): 将结点v到根结点的路径变为新的Preferred Path.  如果路径上经过的某个结点 u 并不是它的父亲 parent(u) 的 Preferred Child, 那么由于 parent(u) 的 Preferred Child 会变为 u , 原本包含 parent(u) 的 Preferred Path 将不再包含结点 parent(u) 及其之上的部分.
	find_root(v): 返回结点v所属的树的根结点. 根结点一定是 v 所属的 Auxiliary Tree 的最小结点, 我们先把 v 旋转到它所属的 Auxiliary Tree 的根. 再从 v 开始, 沿着 Auxiliary Tree 向左走, 直到不能再向左, 这个点就是我们要找的根结点. 由于使用的是 Splay Tree 数据结构保存 Auxiliary Tree, 我们还需要对根结点进行 Splay 操作.
	link(v, w): 合并v和w所属的树, 通过添加边<w, v>, 使w成为v的父亲. 先访问 v , 然后修改 v 所属的 Auxiliary Tree 的 Path Parent 为 w, 然后再次访问 v.
	cut(v): 将v所属树分割为两棵子树, 通过删边<parent(v), v>.  先访问 v, 然后把 v 旋转到它所属的 Auxiliary Tree 的根, 然后再断开 v 在它的所属 Auxiliary Tree 中与它的左子树的连接, 并设置.
	make_root(v): 使v成为所属树的树根, 相当于翻转从v到root(v)路径上所有边的方向.
*/
//无向图的写法
struct LCT
{
    int ch[NUM][2], fa[NUM], pathparent[NUM];
    bool rev[NUM];
    int step[NUM];
    inline void init()
    {
        memset(fa, 0, sizeof(fa));
        memset(ch, 0, sizeof(ch));
        memset(pathparent, 0, sizeof(pathparent));
        memset(rev, 0, sizeof(rev));
        memset(step, 0, sizeof(step));
    }
    inline void Rev(int x)
    {
        if(!x) return ;
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    inline void push_down(int x)
    {
        if(!rev[x]) return ;
        Rev(ch[x][0]);
        Rev(ch[x][1]);
        rev[x] = 0;
    }
    inline void P(int x)
    {
        if(fa[x]) P(fa[x]);
        push_down(x);
    }
    inline void push_up(int x)
    {
        step[x] = step[ch[x][0]] - 1;
    }
    inline void Rot(int x, int c)//c = 0, 左旋,  c = 1, 右旋
    {
        int y = fa[x], z = fa[y];
        ch[y][!c] = ch[x][c];
        if(ch[x][c]) fa[ch[x][c]] = y;
        fa[x] = z;
        if(z) ch[z][ch[z][1] == y] = x;
        ch[x][c] = y;
        fa[y] = x;
        push_up(y);
    }
    inline void Splay(int x)//将x旋转至所属树的根
    {
        P(x);
        int rt = x;
        for(; fa[rt]; rt = fa[rt]);
        if(rt != x)
        {
            pathparent[x] = pathparent[rt];
            pathparent[rt] = 0;
            while(fa[x]) Rot(x, ch[fa[x]][0] == x);
        }
        push_up(x);
    }
    inline void Access(int x)//打通到根结点的路径
    {
        int pa = 0;
        for(; x; x = pathparent[x])
        {
            Splay(x);
            pathparent[ch[x][1]] = x;
            pathparent[pa] = 0;
            fa[ch[x][1]] = 0;
            ch[x][1] = pa;
            fa[pa] = x;
            pa = x ;
            push_up(x);
        }
    }
    inline void make_rt(int x)//使x称为所属树的根
    {
        Access(x);
        Splay(x);
        Rev(x);
    }
    inline void Cut(int v)//分割所属树, 通过删边<fa[v], v>
    {
        make_rt(u);
        Access(v);
        Splay(v);
        fa[ch[v][0]] = 0;
        ch[v][0] = 0;
        push_up(v);
    }
    inline void Link(int v, int w)//合并v所属树和w所属树, 通过连边<w, v>, (w成为v的父结点)
    {
        make_rt(v);
        pathparent[v] = u;
    }
    inline int Query(int x)
    {
        return step[x];
    }
};
//有向图的写法
