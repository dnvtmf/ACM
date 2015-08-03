///字典数 Trie
struct Trie
{
    Trie *next[26];//根据字符集的大小变化
    int cnt;//字符串个数, 根据应用变化
    Trie()
    {
        memset(next, 0, sizeof(next));
        cnt = 0;
    }
};
Trie *root = NULL;
void clearTrie(Trie *p)//清空整棵字典树
{
	if(p)
	{
		for(int i = 0; i < 26; i++)
			clearTrie(p->next[i]);
		delete p;
	}
}
void initTrie()
{
    clearTrie(root);
    root = new root;
}
//将字符串str加入字符串中
void createTrie(char str[])
{
    int i = 0, id;
    Trie *p = root;
    while((id = str[i] - 'a') >= 0)//得到该字符的编号
    {
        if(p->next[id] == NULL)
        {
            p->next[id] = new Trie;
        }
        p = p->next[id];
    }
    p->cnt++;
}
//查询某字符串是否在字典树中
bool findTrie(char str[])
{
    int i = 0, id;
    Trie *p = root;
    while((id = str[i++] - 'a') >= 0)
	{
        p = p->next[id];
        if(p == NULL) return false;
	}
	return p->cnt > 0;
}
//从字典树中删除一个字符串
void deleteTrie(char str[])
{
	int i = 0, id;
	Trie *p = root;
	while((id = str[i++] - 'a') >= 0)
	{
		p = p->next[id];
		if(p == NULL) return ;
	}
	if(p->cnt) p->cnt--;
}

