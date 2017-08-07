///树状数组 Binary Indexed Tree
/*
时间复杂度: 单次查询修改: $O(\log{n})$
空间复杂度: $O(n)$
*/
//单点更新和区间[1, L]求和
struct BIT {
	vector<int> sum;
	int N;
	void init(int n)
	{
		N = n + 10;
		sum.clear();
		sum.resize(N);
	}
	//在pos位置的数加上val
	inline void update(int pos, int val)
	{
		for(; pos < N; pos += pos & -pos) sum[pos] += val;
	}
	//查询[1, pos]区间中所有数的和
	inline int query(int pos)
	{
		int res = 0;
		for(; pos > 0; pos -= pos & -pos) res += sum[pos];
		return res;
	}
	//缩放整个数组: 数组中的每一个元素乘以c
	void scale(int c)
	{
		for(int i = 1; i < N; ++i) sum[i] *= val;
	}
};
//区间更新和单点查询
struct BIT {
	vector<int> v;
	int N;
	void init(int n)
	{
		N = n + 10;
		v.clear();
		v.resize(N);
	}
	//把区间[1, pos]中的每一个数加上val
	inline void update(int pos, int val)
	{
		for(; pos > 0; pos -= pos & -pos) v[pos] += val;
	}
	//区间[L, R]中的每个数加上val
	inline void update(int L, int R, int val)
	{
		update(R, val);
		update(L - 1, -val);
	}
	//查询pos位置的数的值
	inline int query(int pos)
	{
		int res = 0;
		for(; pos < N; pos += pos & -pos) res += v[pos];
		return res;
	}
};
//二维树状数组
int sum[NUM][NUM];
void update(int x, int y, int val)
{
	for(; x < NUM; x += x & -x) {
		for(int y1 = y; y1 < NUM; y1 += y1 & -y1)
			sum[x][y1] += val;
	}
}
