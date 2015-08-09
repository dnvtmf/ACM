//凸包Convex Hull
//

//Graham算法O$(n\log{n})$
//写法一：按直角坐标排序
//直角坐标序比较 (水平序)
bool cmp(const Point &a, const Point &b)//先比较x，后比较x均可
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
vector<Point> Graham(vector<Point> p)
{
    int n = p.size();
    sort(p.begin(), p.end(), cmp);
    vector<Point> res(n + n + 5);
    int top = 0;
    for(int i = 0; i < n; i++)//扫描下凸壳
    {
        while(top > 1 && sgn((res[top - 1] - res[top - 2]) ^ (p[i] - res[top - 2])) <= 0) top--;
        res[top++] = p[i];
    }
    int k = top;
    for(int i = n - 2; i >= 0; i--)//扫描上凸壳
    {
        while(top > k && sgn((res[top - 1] - res[top - 2]) ^ (p[i] - res[top - 2])) <= 0) top--;
        res[top++] = p[i];
    }
    if(top > 1) top--;//最后一个点和第一个点一样, 可以不去掉, 某些计算时方便一些
    res.resize(top);
    return res;
}

//写法二：按极坐标排序
//可能由于精度问题出现RE
