///线性规划
/*标准形式
  有n个变量, m个线性不等式
  @$$\max y = \sum_{j = 1}^{n}{c_j x_j}$$@
  约束条件:
  @$$ \sum_{j=1}^{n}{a_{ij} x_j} = b_i, i = 1, 2, \cdots , m$$@
  @$$ x_j \geq 0, j = 1, 2, \cdots, m$$@
  用矩阵形式表示为:
  最大化$C^T X$, 满足约束$AX = B,\ X \geq 0$, 其中C, X为n为行向量, B为m维列向量, A为$m \times n$的矩阵

  转化为标准形式:
  1. 最小化目标函数: 目标函数中的系数取负, 即令C等于-C.
  3. 有不等式线性约束: 大于等于线性约束减去一个新的松弛变量, 小于等于约束加上一个新的松弛变量.
  4. 没有非负约束: $x_i \in ( -\infty, +\infty )$, 则用$x_i' - x_i''$代替原变量$x_i$
    $x_i \in (-\infty, 0]$, 同样用$x_i' - x_i''$代替原变量$x_i$, 并添加一个不等式线性约束$x_i' - x_i{''} \leq 0$
  注: 约束条件不能是小于或大于形式的不等式.
  例:  $\max y = 3x_1 - x_2 - x_3$
    s.t.  $x_1 - 2x_2 + x_3 \leq 11$
        $-4x_1 + x_2 + 2x_3 \geq 3$
        $-2x_1 + x_3 = 1$
        $x_i \geq 0, i = 1, 2, 3$
    转化为标准形式为:
    $\max y = 3x_1 - x_2 - x_3$
    s.t.  $x_1 - 2x_2 + x_3 + x_4 = 11$
        $-4x_1 + x_2 + 2x_3 - x_5 = 3$
        $-2x_1 + x_3 = 1$
        $x_i \geq 0, i = 1, 2, 3, 4, 5$
*/
/*单纯形方法
  1. 把一般的线性规划问题表示为标准形式
  2. 任选一初始可行解
  3. 用这个基本可行解中的非基本变量表示出基本变量和目标函数
  4. 根据目标函数表达式中的非基本变量的系数的符号, 选择一个有负系数的非基本变量来变成基本变量, 增加这个非基本变量的值, 直到基本变量之一变成零.
  5. 重复第3, 4步, 直到目标函数的表达式中的非基本变量的系数全部为正为止.

  单纯形方法之表格法:
  以基本变量为行, 非基本变量和解为列. 即用非基本变量表示基本变量的表达式中, 将常数写在右边, 带变量的写在左边, 其系数和常数构成的一个$m \times n$的表格.
  表格之间的变换(单纯形方法第4步):
  如果选择的第i个基本变量和第j个非基本变量交换, 则称系数$a_{ij}$为枢纽, 包含枢纽的行为枢行, 包含枢纽的列为枢列.
  1. 把枢纽换为它的倒数
  2. 把枢行的所有元都除以枢纽
  3. 把枢列的所有元都除以枢纽且反号.
  4. 对于表格中的其他元$a_{pq} (p \neq i, q \neq j)$换为$a_{pq} - (a_{pj} \frac{a_{iq}}{a_{ij}})$, 将$w_p$换为$w_p - a_{pj} \frac{w_i}{a_{ij}}$

  二阶段法:
  第一阶段: 构造新的线性规划问题:
    最大化: $\displaystyle \ z = -\sum_{i=1}^{m}{y_i}$
    约束条件: $ \displaystyle \sum_{j=1}^{n}{a_{ij} x_j} + y_i = b_i, (i = 1, 2, \cdots, m)$
        $\displaystyle  x_j \geq 0, (j = 1, 2, \cdots, n), y_j \geq 0, (j = 1, 2, \cdots, m)$
    然后从基本可行解, $(0, 0, \cdots, 0, b_1, b_2, \cdots, b_m)$求得最优基本可行解, 如果该最优基本可行解对应的目标函数z的值小于0, 则说明原线性规划无可行解; 否则$(x_1, x_2, \cdots, x_n)$是原线性规划的基本可行解.
  第二阶段: 用第一阶段求出的基本可行解和单纯形方法求解最优基本可行解.

  特殊情况:
  1. 有无穷多个最优解: 第二阶段结束时目标函数所在行的系数至少有一个为0.
  2. 目标函数值无解(无最优可行解): 第二阶段结束时有以非基本变量所对应的列的元全部为负.
  3. 无可行解: 第一阶段结束时, 在最后的单纯形表格中, 目标函数所在的行的所有系数非负, 目标函数的值小于零时, 原问题不存在可行解.
*/
/*线性规划问题的对偶问题
  最大化:  $\displaystyle y = \sum_{i=1}^{n}{c_i x_i}$
  约束条件:   $\displaystyle \sum_{j=1}^{n}{a_{ij} x_j} \leq b_i, (i = 1, 2, \cdots, m)$
        $x_j \geq 0, (j = 1, 2, \cdots, n)$
  与
  最小化:  $\displaystyle z = \sum_{i=1}^{m}{b_i y_i}$
  约束条件:   $\displaystyle \sum_{j=1}^{m}{a_{ji} y_j} \geq c_i, (i = 1, 2, \cdots, n)$
        $y_j \geq 0, (j = 1, 2, \cdots, m)$
  称为本原问题与与其对偶问题.
  定理: 线性规划问题的对偶问题的对偶问题是本原问题.
  定理: 设$(x_1, x_2, \cdots, x_n)$与$(y_1, y_2, \cdots, y_m)$是一对互为对偶问题的线性规划问题的可行解, 恒有:@$$
      \sum_{i=1}^{n}{c_i x_i} \leq \sum_{i=1}^{m}{b_i y_i}$$@
  定理: 设$(x_1, x_2, \cdots, x_n)$与$(y_1, y_2, \cdots, y_m)$是一对互为对偶问题的线性规划问题的可行解, 且有: $\displaystyle \sum_{i=1}^{n}{c_i x_i} = \sum_{i=1}^{m}{b_i y_i}$, 则$(x_1, x_2, \cdots, x_n)$和$(y_1, y_2, \cdots, y_m)$是对应线性规划问题的最优可行解.
  定理: 如果本原问题与对偶问题之一有最优可行解, 则另一个问题也有最优可行解, 且它们的目标函数值相等.
  推论: 在本原问题的最优单纯形表中, 目标函数的松弛变量的的系数就是对偶问题的最优基本可行解.
*/
const double EPS = 1e-6, dINF = 1e15;
//最优解
#define OPTIMAL -1
//无最优解
#define UNBOUNED -2
//有无穷多个最优解
#define INFINITELY -3
//无可行解
#define INFEASIBLE -4
//找到枢纽
#define PIVOT_OK 1
inline int sgn(double x) {
  return x < -EPS ? -1 : x > EPS ? 1 : 0;
}
const int maxn = 100;
struct LinearProgramming {
  double a[maxn][maxn], w[maxn], goal[maxn], ans;
  int row[maxn], col[maxn];
  int N, m, O, n;//原变量数, 线性约束数, 松弛变量数, 非基本变量数
  //得到枢纽
  int Pivot(int &x, int &y) {
    x = -1, y = 0;
    for (int j = 0; j < n; ++j) if (sgn(a[m][j] - a[m][y]) < 0) y = j;
    if (sgn(a[m][y]) >= 0) return OPTIMAL; //已经得到最优解
    double minv = dINF, val;
    for (int i = 0; i < m; ++i) {
      val = w[i] / a[i][y];
      if (sgn(val) <= 0) continue;
      if (sgn(val - minv) < 0) {
        minv = val;
        x = i;
      }
    }
    if (x < 0) return UNBOUNED; //有可行解, 但无最优解
    return PIVOT_OK;
  }
  //单纯形方法, 第m+1行为目标函数
  int Simplex() {
    int k, x, y;
    while ((k = Pivot(x, y)) == PIVOT_OK) {
      swap(row[x], col[y]);
      double tmp = a[x][y], temp;
      for (int i = 0; i <= m; ++i) {
        if (i == x) continue;
        temp = a[i][y] / tmp;
        for (int j = 0; j < n; ++j) {
          if (j == y) continue;
          a[i][j] -= a[x][j] * temp;
        }
        w[i] -= w[x] * temp;
      }
      for (int j = 0; j < n; ++j) a[x][j] /= tmp;
      w[x] /= tmp;
      tmp = -tmp;
      for (int i = 0; i <= m; ++i) a[i][y] /= tmp;
      a[x][y] = -a[x][y];
    }
    return k;
  }
  //二阶段法解线性规划
  int solve() {
    w[m] = 0;
    for (int j = 0; j < n; ++j) col[j] = j, a[m][j] = 0;
    for (int i = 0; i < m; ++i) {
      row[i] = i + n;
      w[m] -= w[i];
      for (int j = 0; j < n; ++j) a[m][j] -= a[i][j];
    }
    int result = Simplex();
    if (result == INFEASIBLE || sgn(w[m]) < 0) return INFEASIBLE; //无可行解
    for (int j = 0, k = 0; j < n; ++j) {
      if (col[j] >= n) continue;
      col[k] = col[j];
      for (int i = 0; i < m; ++i) a[i][k] = a[i][j];
      ++k;
    }
    w[m] = 0;
    n -= m;
    for (int j = 0; j < n; ++j) a[m][j] = 0;
    for (int i = 0; i < m; ++i) {
      if (row[i] >= N) continue;
      for (int j = 0; j < n; ++j) {
        a[m][j] += goal[row[i]] * a[i][j];
      }
      w[m] += goal[row[i]] * w[i];
    }
    for (int j = 0; j < n; ++j) {
      if (col[j] < N) a[m][j] -= goal[col[j]];
    }
    result = Simplex();
    if (result == OPTIMAL) {
      for (int j = 0; j < n; ++j)
        if (sgn(a[m][j]) == 0) {
          result = INFINITELY;//无穷多个最优解
          break;
        }
    }
    ans = w[m];
    return result;
  }
} lp;
