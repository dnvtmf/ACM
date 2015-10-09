///二分搜索
//对于某些满足单调性质的数列, 或函数, 可以二分搜索答案, 在$O(\log{n})$时间内求解
//如f(x) = 1 (x <= y) = 0 (x > y), 可以二分搜索出分界值y
//注意: l%2 == 0, r = l + 1时, (l + r)/2 == l 此处易出现死循环
int binary_search(int l, int r)
{
    int mid;
    int ans = l;
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if(f(mid))
        {
            r = mid - 1;//视情况定
            ans = mid;
        }
        else
            l = mid + 1;
    }
    return ans;
}
///三分搜索
//对于满足抛物线性质的数列或函数, 可以三分答案, 在$O(\log{n})$ 时间内求解
//方便于求(抛物线)的最值
//注意: l % 3 == 0, r = l + 1 | l + 2时, (l + l + r) / 3 == l 容易出现死循环
int three_search(int l, int r)
{
    int ll, rr;
    while(l + 2 < r)
    {
        ll = (l + l + r) / 3;
        rr = (l + r + r) / 3;
        if(f(ll) < f(rr))
            r = rr;
        else
            l = ll;
    }
    return min(f(l), f(r), f(l + 1));
}

