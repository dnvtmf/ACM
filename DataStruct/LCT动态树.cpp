///动态树问题(Dynamic Tree Problems)
///数据结构: (Link-cut Tree LCT)
//LCT = 树链剖分 + Splay
//功能: 支持对树的分割, 合并, 对某个点到它的根的路径的某些操作, 以及对某个点的子树进行的某些操作. (同时维护树的形态)
/*定义:
    如果刚刚执行了对某个点的Access操作, 则称一个点被访问过;
    结点v的子树中, 如果最后被访问访问的结点在子树w中, 这里w是v的儿子, 那么称w是v的Preferred Child. 如果最后被访问的结点是v本身, 则v没有Preferred Child.
    每个结点到它的Preferred Child的边称作Preferred Edge.
    由Preferred Edge连接成的不可再延伸的路径称为Preferred Path.
    这棵树就被划分成若干条Preferred Path, 对于每一条Preferred Path, 用其结点的深度做关键字, 用Splay Tree树维护它, 称这棵树为 Auxiliary Tree.
    用 Path Parent 来记录每棵 Auxiliary Tree 对应的 Preferred Path 中的最高点的父亲结点, 如果这个 Preferred Path 的最高点就是根结点, 那么令这棵 Auxiliary Tree 的 Path Parent 为 null.
    Link-Cut Trees 就是将要维护的森林中的每棵树 T 表示为若干个 Auxiliary Tree, 并通过 Path Parent 将这些 Auxiliary Tree 连接起来的数据结构.
*/

#define ls son[x][0]
#define rs son[x][1]
#define is(x) (x==son[fa[x]][1])
#define isroot(x) (x!=son[fa[x]][0]&&x!=son[fa[x]][1])
#define N 100010
#define inf 0x3f3f3f3f
using namespace std;
int pos[N], n, m;
char ttt[10];
struct LCT
{
    int son[N][2], fa[N], cnt;
    bool flag[N];
    int stack[N], top;
    void joint(int x, int y, int d) {fa[x] = y, son[y][d] = x;}
    void reverse(int x)
    {
        flag[x] ^= 1;
        swap(ls, rs);
    }
    void pushdown(int x)
    {
        if(flag[x])
        {
            reverse(x);
            flag[ls] ^= 1, flag[rs] ^= 1;
            flag[0] = 0;
        }
    }
    int newnode()
    {
        cnt++;
        son[cnt][0] = son[cnt][1] = fa[cnt] = 0;
        return cnt;
    }
    void pushpath(int x)
    {
        for(top = 0; !isroot(x); x = fa[x])stack[++top] = x;
        stack[++top] = x;
        for(int i = top; i; i--)pushdown(stack[i]);
    }
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], i = is(x), t = son[x][!i];
        if(!isroot(y))joint(x, z, is(y));
        else fa[x] = z;
        joint(t, y, i), joint(y, x, !i);
        fa[0] = son[0][0] = son[0][1] = 0;
    }
    void splay(int x)
    {
        pushpath(x);
        int y, z;
        while(!isroot(x))
        {
            y = fa[x], z = fa[y];
            if(isroot(y)) {rotate(x); break;}
            rotate(is(x) == is(y) ? y : x), rotate(x);
        }
    }
    void access(int x)
    {
        int p = 0;
        while(x)
        {
            splay(x);
            rs = p, p = x, x = fa[x];
        }
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        flag[x] = 1;
        pushdown(x);
    }
    void link(int x, int y)
    {
        makeroot(x);
        fa[x] = y;
    }
    void cut(int x, int y)
    {
        makeroot(y);
        access(x);
        splay(x);
        ls = fa[y] = 0;
    }
    int findroot(int x)
    {
        while(fa[x])x = fa[x];
        return x;
    }
} lct;
/*
//无向图的写法
struct LCT
{
    int ch[NUM][2], fa[NUM];
    bool rev[NUM];
    int sz[NUM];
    stack<int> stk;
    void init()
    {
    }
    inline bool IsRoot(int x)
    {
        return !fa[x] || (ch[fa[x]][0] != x && ch[fa[x]][1] != x);
    }
    inline int Dir(int x) {return ch[fa[x]][1] == x;}
    inline void setCh(int x, int x_fa, int d)
    {
        ch[x_fa][d] = x;
        if(x) fa[x] = x_fa;
    }
    inline void push_down(int x)
    {
        if(rev[x])
        {
            swap(ch[x][0], ch[x][1]);
            rev[ch[x][0]] ^= 1;
            rev[ch[x][1]] ^= 1;
            rev[x] = 0;
        }
    }
    inline void push_up(int x)
    {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    }
    inline void Rotate(int x)
    {
        int y = fa[x], d = Dir(x);
        if(IsRoot(y)) fa[x] = fa[y];
        else setCh(x, fa[y], Dir(y));
        setCh(ch[x][!d], y, d);
        setCh(y, x, !d);
        push_up(y);
    }
    inline void Splay(int x)
    {
        int y = x;
        while(1)
        {
            stk.push(y);
            if(IsRoot(y)) break;
            y = fa[y];
        }
        while(!stk.empty())
        {
            push_down(stk.top());
            stk.pop();
        }
        while(!IsRoot(x))
        {
            int y = fa[x];
            if(IsRoot(y)) Rotate(x);
            else if(Dir(x) == Dir(y))
                Rotate(y), Rotate(x);
            else
                Rotate(x), Rotate(x);
        }
        push_up(x);
    }
    inline int Access(int x)
    {
        int y = 0;
        for(; x; x = fa[x]) Splay(x), ch[x][1] = y, push_up(y = x);
        return y;
    }
    inline void MakeRoot(int x)
    {
        Access(x);
        Splay(x);
        rev[x] ^= 1;
        push_down(x);
    }
    inline void Link(int x, int x_fa)
    {
        MakeRoot(x_fa);
        MakeRoot(x);
        setCh(x, x_fa, 1);
    }
    inline void Cut(int x, int x_fa)
    {
        MakeRoot(x_fa);
        Access(x);
        Splay(x);
        ch[x][0] = fa[x_fa] = 0;
        push_up(x);
    }
    inline int Query(int x, int root)
    {
        MakeRoot(root);
        Access(x);
        Splay(x);
        return sz[ch[x][0]];
    }
} lct;*/
//有向图的写法
/*操作:
    Access(x): 使结点x到根结点的路径成为新的Preferred Path.
    FindRoot(x): 返回结点x所在树的根结点.
    Link(x, y): 使结点x成为结点y的新儿子. 其中x是一棵树的根结点, 且x和y属于两棵不同的子树.
    Cut(x): 删除x与其父亲结点间的边.
*/
struct LCT
{
    int ch[NUM][2], pre[NUM], bef[NUM];
    int sz[NUM];
    void init()
    {
        memset(ch, 0, sizeof(ch));
        memset(pre, 0, sizeof(pre));
        memset(bef, 0, sizeof(bef));
        memset(sz, 0, sizeof(sz));
    }
    void push_up(int x)
    {
        sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
    }
    void Rotate(int x)
    {
        int y = pre[x], c = (ch[y][0] == x);
        ch[y][!c] = ch[x][c];
        pre[ch[x][c]] = y;
        pre[x] = pre[y];
        if(pre[y]) ch[pre[y]][ch[pre[y]][1] == y] = x;
        ch[x][c] = y;
        pre[y] = x;
        push_up(y);
    }
    void Splay(int x)
    {
        int rt;
        for(rt = x; pre[rt]; rt = pre[rt]);
        if(rt != x)
        {
            bef[x] = bef[rt];
            bef[rt] = 0;
            while(pre[x]) Rotate(x);
        }
        push_up(x);
    }
    void Access(int x)
    {
        for(int fa = 0; x; x = bef[x])
        {
            Splay(x);
            bef[ch[x][1]] = x;
            bef[fa] = 0;
            pre[ch[x][1]] = 0;
            ch[x][1] = fa;
            pre[fa] = x;
            fa = x;
            push_up(x);
        }
    }
    void Cut(int x)
    {
        Access(x);
        Splay(x);
        pre[ch[x][0]] = 0;
        ch[x][0] = 0;
        push_up(x);
    }
    void Link(int x, int x_fa)
    {
        Splay(x);
        bef[x] = x_fa;
        Access(x);
    }
    int Query(int x)
    {
        Access(x);
        Splay(x);
        return sz[ch[x][0]];
    }
} lct;
