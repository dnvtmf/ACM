//凸包Convex Hull
//

//Graham算法O(nlog n)
//写法一：按直角坐标排序
//直角坐标序比较 (水平序)
bool cmp(Point a, Point b)//先比较x，后比较x均可
{
    if(sgn(a.x - b.x)) return sgn(a.x - b.x) < 0;
    return sgn(a.y - b.y) < 0;
}

vector<Point> graham(Point p[], int pnum)
{
    sort(p, p + pnum, cmp);
    vector<Point> res(2 * pnum + 5);
    int i, total = 0, limit = 1;
    for(i = 0; i < pnum; i++)//扫描下凸壳
    {
        while(total > limit && sgn((res[total - 1] - res[total - 2]) ^ (p[i] - res[total - 1])) <= 0) total--;
        res[total++] = p[i];
    }
    limit = total;
    for(i = pnum - 2; i >= 0; i--)//扫描上凸壳
    {
        while(total > limit && sgn((res[total - 1] - res[total - 2]) ^ (p[i] - res[total - 1])) <= 0) total--;
        res[total++] = p[i];
    }
    if(total > 1)total--;//最后一个点和第一个点一样
    res.resize(total);
    return res;
}
//写法二：按极坐标排序
Point p0;//p0 原点集中最左下方的点
int top;
bool cmp(point p1, point p2) //极角排序函数 ， 角度相同则距离小的在前面
{
    int tmp = (p1 - p2) ^ (p0 - p2);
    if(tmp > 0) return true;
    else if(tmp == 0 && (p0 - p1) * (p0 - p1) < (p0 - p2) * (p0 - p2)) return true;
    else return false;
}

vector<Point> graham(Point p[], int pn)
{
    //p0
    for(int i = 1; i < pn; i++)
        if(p[i].x < p[0].x || (p[i].x == p[0].x && p[i].y < p[0].y))
            swap(p[i], p[0]);
    p0 = p[0];
    //sort
    sort(p + 1, p + pn);
    vector<Point> stk(pn * 2 + 5);
    int top = 0;
    stk[top++] = p[0];
    if(n > 1) stk[top++] = p[1];
    if(n > 2)
    {
        for(i = 2; i < n; i++)
        {
            while(top > 1 && ((stk[top - 1] - stk[top - 2]) ^ (p[i] - stk[top - 2])) <= 0) top--;
            stk[top++] = p[i];
        }
    }
    stk.resize(top);
    return stk;
}
