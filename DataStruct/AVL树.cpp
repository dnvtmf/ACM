template<class T>
class AVLTreeNode
{
public:
	T key;		//关键字
	int height;
	AVLTreeNode *ch[2];
	AVLTreeNode(T key = 0): key(key), height(1), ch {nullptr, nullptr} {}
	inline void get()
	{
		height = 0;
		if(ch[0] != nullptr)
			height = ch[0]->height;
		if(ch[1] != nullptr)
			height = max(height, ch[1]->height);
		++height;
	}
	inline int diff()
	{
		int d = 0;
		if(ch[0] != nullptr)
			d = ch[0]->height;
		if(ch[1] != nullptr)
			d -= ch[1]->height;
		return d;
	}
};

template<class T>
class AVLTree
{
private:
	AVLTreeNode<T> *root;
	void insert(AVLTreeNode<T> *&p, T key);
	void remove(AVLTreeNode<T> *&p, T key);
	void clear(AVLTreeNode<T> *&p);
	//将x->ch[d]旋转到x处
	inline void rot(AVLTreeNode<T> *&x, int d);
	//平衡AVL树
	inline void blance(AVLTreeNode<T> *&p);
public:
	AVLTree() {root = nullptr;}
	~AVLTree() {clear();}
	inline void insert(T key) {insert(root, key);}
	inline void remove(T key) {remove(root, key);}
	AVLTreeNode<T> *find(T key);
	AVLTreeNode<T> *lower_bound(T key);
	inline void clear() {clear(root);}
};

template<class T>
inline void AVLTree<T>::rot(AVLTreeNode<T> *&x, int d)
{
	AVLTreeNode<T> *y = x->ch[d];
	x->ch[d] = y->ch[!d];
	y->ch[!d] = x;
	x = y;
}

template<class T>
inline void AVLTree<T>::blance(AVLTreeNode<T> *&p)
{
	int d = p->diff();
	if(d == 2) {
		if(p->ch[0]->diff() == 1) {
			rot(p, 0);
			p->ch[1]->get();
			p->get();
		}
		else {
			rot(p->ch[0], 1);
			rot(p, 0);
			p->ch[0]->get();
			p->ch[1]->get();
			p->get();
		}
	}
	else if(d == -2) {
		if(p->ch[1]->diff() == -1) {
			rot(p, 1);
			p->ch[0]->get();
			p->get();
		}
		else {
			rot(p->ch[1], 0);
			rot(p, 1);
			p->ch[0]->get();
			p->ch[1]->get();
			p->get();
		}
	}
}
template<class T>
void AVLTree<T>::insert(AVLTreeNode<T> *&p, T key)
{
	if(p == nullptr) {
		p = new AVLTreeNode<T>(key);
	}
	if(key == p->key) {
	}
	else if(key < p->key) {
		insert(p->ch[0], key);
	}
	else {
		insert(p->ch[1], key);
	}
	blance(p);
}
template <class T>
void AVLTree<T>::remove(AVLTreeNode<T> *&p, T key)
{
	if(p == nullptr)
		return ;
	if(key < p->key)
		remove(p->ch[0], key);
	else if(key > p->key)
		remove(p->ch[1], key);
	else {
		if(p->ch[0] != nullptr && p->ch[1] != nullptr) {
			AVLTreeNode<T> *q = p->ch[1];
			while(q->ch[0] != nullptr) q = q->ch[0];
			p->key = q->key;
			remove(p->ch[1], q->key);
		}
		else {
			AVLTreeNode<T> *tmp = p;
			if(p->ch[0] == nullptr)
				p = p->ch[1];
			else if(p->ch[1] == nullptr)
				p = p->ch[0];
			delete tmp;
			tmp = nullptr;
		}
	}
	if(p != nullptr)
		blance(p);
}


template<class T>
AVLTreeNode<T> *AVLTree<T>::find(T key)
{
	AVLTreeNode<T> *p = root;
	while(p != nullptr && p->key != key) {
		if(key < p->key)
			p = p->ch[0];
		else
			p = p->ch[1];
	}
	return p;
}
template<class T>
AVLTreeNode<T> *AVLTree<T>::lower_bound(T key)
{
	AVLTreeNode<T> *p = root, *res = nullptr;
	while(p != nullptr) {
		if(p->key >= key) {
			res = p;
			p = p->ch[0];
		}
		else
			p = p->ch[1];
	}
	return res;
}
template<class T>
void AVLTree<T>::clear(AVLTreeNode<T> *&p)
{
	if(p == nullptr) return ;
	clear(p->ch[0]);
	clear(p->ch[1]);
	delete p;
	p = nullptr;
}
