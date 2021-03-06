/*区间的rmq问题
 * 在一维数轴上，添加或删除若干区间[l,r]， 询问某区间[ql, qr]内覆盖了多少个完整的区间
 * 做法：离线，按照右端点排序，然后按照左端点建立线段树保存左端点为l的区间个数，
 *      接着按排序结果从小到大依次操作，遇到询问时，查询比ql大的区间数
 * 遇到不能改变查询顺序的题，应该用可持久化线段树
 */
/*数组区间颜色数查询
    问题: 给定一个数组,要求查询某段区间内有多少种数字
    解决: 将查询离线, 按右端点排序; 从左到右依次扫描, 扫描到第i个位置时, 将该位置加1, 该位置的前驱(上一个出现一样数字的位置)减1, 然后查询所有右端点为i的询问的一个区间和[l, r].
*/
/*数组区间数字种类数查询(带修改, 在线)
    问题: 给定一个数组, 查询某区间内有多少种数字, 要求在线, 并且带修改操作
    解决: 利用该数字上一次出现的位置pre, 将问题转化为求该区间[L, R]内有多少个数字的pre小于区间左端点L. 然后用树套树解决. $O(|Q|\log^2{n})$
*/
/*求$b_{lr} = \sum_{i=l}^{r}{(i - l + 1) \cdot a_i}~(1 \leq l \leq r \leq n)$的最大值
    令$s1_k = \sum_{i=1}^{k}{a_i}, s2_k = \sum_{i=1}^{k}{ia_i}$, 则$b_{lr} = s2_r - s2_{l-1} - (l - 1) \cdot (s1_r - s1_{l-1})$,
    若r为确定, 则$b_{lr} = s2_r - (s2_{l-1} - (l-1) \cdot s1_{l-1} + (l-1) \cdot s1_r) = s2_r - (y_l + s1_r * x_l)$, 其中$y_l = s2_{l-1} - (l-1)\cdot s1_{l-1}, x_l = l - 1$.
    问题转化为求$y_l + s1_r \cdot x_l$的最小值.(见下)
*/
/*平面点集, 最大化(最小化)目标函数
    问题: 给n个点(x, y)和k, 求$z = x + k \cdot y$的最大(小)值.
    解决: 维护一个上(下)凸壳(单调队列), 在凸壳上二分查找最大值, 即对于上凸壳, 其边的斜率是严格递减的, 而求得最大值的点恰好是斜率大于等于-k的线段的中点.
 */
double get_min(double k, Point stk[], int top)
{
    double kk = -k;
    if(top == 1) return x[0] + k * y[0];
    if(kk < get_k(x[0], y[0], x[1], y[1]))
        return x[0] + k * y[0];
    int l = 1, r = top - 1, mid, ans = 0;
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if((x[mid - 1] -  x[mid])/ (y[mid - 1], y[mid]) <= kk)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return x[ans] + k * y[ans];
}
