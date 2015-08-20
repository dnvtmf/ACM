///AC自动机
//kmp + Trie
const int kind = 26;
struct node
{
    node* fail;//失败指针
    node* next[kind];//Trie节点的每个子节点
    int cnt;//是否为该单词的最后一个节点
    node()
    {
        fail = NULL;
        memset(next, NULL, sizeof(next));
        cnt = 0;
    }
};
void insert(char s[], node *root)//构建Trie
{
    node *p = root;
    int i = 0, index;
    while(s[i])
    {
        index = s[i] - 'a';
        if(p->next[index] == NULL)p->next[index] = new node();
        p = p->next[index];
        i++;
    }
    p->cnt++;
}
void build_ac_automation(node *root)//构建失败指针
{
    int i;
    queue <node*> q;
    root->fail = NULL;
    q.push(root);
    while(!q.empty())
    {
        node *tmp = q.front();
        q.pop();
        node *p = NULL;
        for(i = 0; i < kind; i++)
            if(tmp->next[i])
            {
                if(tmp == root)tmp->next[i]->fail = root;
                else
                {
                    p = tmp->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            tmp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if(!p)tmp->next[i]->fail = root;
                }
                q.push(tmp->next[i]);
            }
    }
}

int query(char str[], node *root)//查询模式串中出现过多少单词
{
    int i = 0, cnt = 0, index;
    node *p = root;
    while(str[i])
    {
        index = str[i] - 'a';
        while(!p->next[index] && p != root)p = p->fail;
        p = p->next[index];
        if(!p)p = root;
        node *temp = p;
        while(temp != root)
        {
            if(temp->cnt >= 0)
            {
                cnt += temp->cnt;
                temp->cnt = -1;
            }
            else
                break;
            temp = temp->fail;
        }
        i++;
    }
    return cnt;
}

//数组版本
int fail[NUM], next[NUM][26], cnt[NUM], num;
int newnode()
{
    for(int i = 0; i < 26; i++)
        next[num][i] = -1;
    cnt[num] = 0;
    return num++;
}
void init()
{
    num = 0;
    newnode();
}
void insert(char *s)
{
    int i = 0, p = 0;
    while(s[i])
    {
        if(next[p][s[i] - 'a'] == -1)next[p][s[i] - 'a'] = newnode();
        p = next[p][s[i++] - 'a'];
    }
    cnt[p]++;
}
void build()
{
    int p = 0, i;
    fail[0] = 0;
    queue<int> que;
    for(i = 0; i < 26; i++)
        if(next[0][i] == -1)
            next[0][i] = 0;
        else
        {
            fail[next[0][i]] = 0;
            que.push(next[0][i]);
        }
    while(!que.empty())
    {
        p = que.front();
        que.pop();
        for(i = 0; i < 26; i++)
            if(next[p][i] == -1)
                next[p][i] = next[fail[p]][i];
            else
            {
                fail[next[p][i]] = next[fail[p]][i];
                que.push(next[p][i]);
            }
    }
}
int query(char *s)
{
    int res = 0, i = 0, p = 0, q;
    while(s[i])
    {
        p = next[p][s[i++] - 'a'];
        q = p;
        while(q)
        {
            res += cnt[q];
            q = fail[q];
        }
    }
    return res;
}


#define MAXL
//MAXL 指匹配字符串可能的最大长度
#define MAX
//MAX指匹配字符串可能的最大数量
const int Kind = 26, Base = 'a';//Base ASCII最小的出现字符，Kind 最大字符与Base间的字符数
struct node
{
    int fail;//失败指针
    int next[Kind];
    int cnt;//
};
class AC
{
    int num;//当前结点数
    node e[MAXL];
    AC() {init();}
    void init()
    {
        num = 0;
        newnode();
    }
    int newnode()
    {
        for(int i = 0; i < Kind; i++)
            e[num].next[i] = -1;
        e[num].cnt = 0;
        return num++;
    }
    int insert(char *s)
    {
        int i, p = 0;
        for(i = 0; s[i]; i++)
        {
            if(e[p].next[s[i] - Base] == -1)e[p].next[s[i] - Base] = newnode();
            p = e[p].next[s[i] - Base];
        }
        e[p].cnt++;
        return p;
    }
    void build()
    {
        int p = 0, i;
        e[p].fail = 0;
        queue<int> que;
        for(i = 0; i < Kind; i++)
            if(e[p].next[i] == -1)
                e[p].next[i] = 0;
            else
            {
                e[e[p].next[i]].fail = 0;
                que.push(e[p].next[i]);
            }
        while(!que.empty())
        {
            p = que.front(); que.pop();
            for(i = 0; i < Kind; i++)
                if(e[p].next[i] != -1)
                {
                    e[e[p].next[i]].fail = e[e[p].fail].next[i];
                    que.push(e[p].next[i]);
                }
                else
                    e[p].next[i] = e[e[p].fail].next[i];
        }
    }
    int query(char *s)
    {
        int res = 0, i, p = 0, q;
        for(i = 0; s[i]; i++)
        {
            q = p = e[p].next[s[i] - Base];
            while(q)
            {
                res += e[q].cnt;
                q = e[q].fail;
            }
        }
        return res;
    }
};
