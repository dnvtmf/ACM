///伸展树Splay
//均摊复杂度O(log n) 最坏复杂度O(n)
/*操作
1. 旋转: 左右旋, 将左（右）孩子变为根
2. spaly: 将结点x旋转至根y处
3. find: 同二叉树查找, 查找成功后splay
4. remove: 查找x, 如果x无孩子或一个孩子, 删除x, splay(x)的根结点; x有两个孩子, 用x的后继y代替x, splay(y)
5. join, split合并, 分解树.
6. 区间操作: [a, b], 将a-1 splay至根处, b+1至根的右孩子处, 那根的右孩子的左子树表示区间[a, b]
*/
const int NUM = 1000000 + 10;
struct Splay
{
    int fa[NUM], ch[NUM][2];
    int key[NUM];
    int sum[NUM];
    int len[NUM];
    int tot, root;
    void init()
    {
        tot = 0;
        root = 0;
    }
    void push_down(int p) {}
    void push_up(int p)
    {
        sum[p] = len[p];
        if(ch[p][0]) sum[p] += sum[ch[p][0]];
        if(ch[p][1]) sum[p] += sum[ch[p][1]];
    }
    void Rot(int x)
    {
        int y = fa[x], z = fa[y];
        int c = (ch[y][0] == x);
        push_down(y), push_down(x);
        ch[y][!c] = ch[x][c];
        if(ch[x][c]) fa[ch[x][c]] = y;
        if(z) ch[z][ch[z][1] == y] = x;
        fa[x] = z;
        ch[x][c] = y;
        fa[y] = x;
        push_up(y);
        if(root == y) root = x;
    }

    void splay(int x, int pa)
    {
        int y, z;
        push_down(x);
        while((y = fa[x]) != pa)
        {
            z = fa[y];
            if(z == pa) Rot(x);
            else if((ch[z][0] == y) == (ch[y][0] == x))
                Rot(y), Rot(x);
            else
                Rot(x), Rot(x);
        }
        push_up(x);
    }

    int find(int _key)
    {
        int p = root;
        while(p)
        {
            if(key[p] == _key) break;
            else if(key[p] > _key) p = ch[p][0];
            else p = ch[p][1];
        }
        if(p) splay(p, 0);
        return p;
    }

    int insert(int _key, int _len)
    {
        int x = ++tot;
        ch[x][0] = ch[x][1] = 0;
        key[x] = _key;
        len[x] = _len;
        sum[x] = _len;
        int p = root;
        if(!p) root = x, fa[x] = 0;
        else
        {
            while(true)
            {
                int c = key[p] < _key;
                if(ch[p][c]) p = ch[p][c];
                else
                {
                    ch[p][c] = x;
                    fa[x] = p;
                    break;
                }
            }
            splay(x, 0);
        }
        return x;
    }

    void erase(int x)
    {
        splay(x, 0);
        int a = ch[x][0];
        int b = ch[x][1];
        if(a) fa[a] = 0;
        if(b) fa[b] = 0;
        if(!a)
        {
            root = b;
            return;
        }
        if(!b)
        {
            root = a;
            return ;
        }
        while(ch[a][1]) a = ch[a][1];
        ch[a][1] = b;
        fa[b] = a;
        splay(a, 0);
        root = a;
    }
    int lower_bound(int _key)
    {
        int x = -1, p = root;
        while(p)
        {
            if(_key > key[p]) p = ch[p][1];
            else p = ch[x = p][0];
        }
        if(x > 0) splay(x, 0);
        return x;
    }
} sp;

