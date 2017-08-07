///快速傅里叶变换FFT(Fast Fourier Transformation)
/*原理:
DFT(离散傅里叶变换), 变换公式: @$$\left\{\begin{array}{l l}
    \displaystyle X(k) = \sum_{i=0}^{N - 1}{x(i)W_N^{ik}} &k=0, 1, \cdots, N - 1\\
    \displaystyle W_N = e^{-j\frac{2\pi}{N}}
    \end{array}\right.$$@
    $W_N$被称为旋转因子, 有如下性质:
    1. 对称性: $(W_N^{ik})^* = W_N^{-ik}$
    2. 周期性: $W_N^{ik} = W_N^{(i + N)k} = W_N^{i(N+k)}$
    3. 可约性: $W_N^{ik} = W_{mN}^{mik}, W_N^{ik} = W_{\frac{N}{m}}^{\frac{ik}{m}}$
    所以: $W_N^{i(N-k)} = W_N^{(N-i)k} = W_N^{-ik}, W_N^{N/2} = -1, W_N^{k + N/2} = -W_N^k$
IDFT(DFT逆变换), 变换公式: @$$x(k) = \frac{1}{N}\sum_{i=1}^{N-1}{X(i)W_N^{-ik}}$$@
(基2)FFT推导:@$$\begin{array}{r l}
X(k) = &\displaystyle \sum_{i=0}^{N-1}{x(i)W_N^{ik}} \\
    =&\displaystyle  \sum_{r=0}^{N/2 - 1}{x(2r)W_N^{2rk}} + \sum_{r=0}^{N/2-1}{x(2r+1)W_N^{(2r+1)k}} \\
    =&\displaystyle \sum_{r=0}^{N/2 -1}{x(2r)W_{N/2}^{rk}} + W_N^k\sum_{r=0}^{N/2-1}{x(2r+1)W_{N/2}^{rk}} \\
    =& \left\{\begin{array}{l l}
        \displaystyle \sum_{r=0}^{N/2-1}{x(2r)W_{N/2}^{rk}} + W_N^k\sum_{r=0}^{N/2-1}{x(2r+1)W_{N/2}^{rk}} &k < N/2 \\
        \displaystyle \sum_{r=0}^{N/2-1}{x(2r)W_{N/2}^{rk'}} - W_N^{k'}\sum_{r=0}^{N/2-1}{x(2r+1)W_{N/2}^{rk'}} &k \geq N/2, k' = k - N/2
    \end{array}\right.
\end{array}$$@
所以通过计算@$$X_1(k) = \sum_{r=0}^{N/2-1}{x(2r)W_{N/2}^{rk}}, X_2(k) = \sum_{r=0}^{N/2-1}{x(2r+1)W_{N/2}^{rk}},
    k < N/2$$@
可以计算得@$$\left\{ \begin{array}{l l}
X(k) &= X_1(k) + W_N^k X_2(k) \\
X(k + N/2) &= X_1(k) - W_N^k X_2(k)
\end{array}\right. k < N/2$$@
DFT变换满足cyclic convolution的性质, 即
定义循环卷积c=a(*)b: @$$c_r = \sum_{x+y=r(\% N)}{a_x b_y}$$@
则有: DFT(a(*)b) = DFT(a) $\cdot$ DFT(b), 所以a(*)b = DFT$^{-1}$(DFT(a) $\cdot$ DFT(b))
注意: FFT是cyclic的, 需要保证高位有足够多的0
    FFT算法限制, n必须是2的幂
    FFT是定义在复数上的, 因此与整数变换可能有精度误差
*/
///二维FFT/NTT
///先对每行进行FFT，再对每列进行FFT(即转置后对每行进行FFT再转置回来)
//FFT常被用来为多项式乘法加速, 即在$O(n\log{n})$复杂度内完成多项式乘法
//也需要用FFT算法来解决需要构造多项式相乘来进行计数的问题
//#incldue <complex>
//typedef std::complex<double> Complex;
const double PI = acos(-1.);
struct Complex { //复数类, 可以直接用STL库中的complex<double>
  double r, i;
  Complex(double _r = 0.0, double _i = 0.0) {r = _r, i = _i;}
  Complex operator + (const Complex &b) const {
    return Complex(r + b.r, i + b.i);
  }
  Complex operator - (const Complex &b) const {
    return Complex(r - b.r, i - b.i);
  }
  Complex operator * (const Complex &b) const {
    return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
  }
  double real() {return r;}
  double image() {return i;}
} FFT_A[NUM << 2], FFT_B[NUM << 2];
void FFT(Complex p[], int N, int op) { //op = 1表示DFT傅里叶变换, op=-1表示傅里叶逆变换
  //蝶形变换, 交换位置i与逆序i, 如N=2^3, 交换p[011=3]与p[110=6]
  for (int i = 0, j = 0; i < N; i++) {
    if (i > j) swap(p[i], p[j]);
    for (int l = N >> 1; (j ^= l) < l; l >>= 1);
  }
  double p0 = PI * op;
  for (int h = 2; h <= N; h <<= 1, p0 *= 0.5) {
    int hf = h >> 1;
    Complex unit(cos(p0), sin(p0));
    for (int i = 0; i < N; i += h) {
      Complex w(1.0, 0.0);
      for (int j = i; j < i + hf; j++) {
        Complex u = p[j], t = w * p[j + hf];
        p[j] = u + t;
        p[j + hf] = u - t;
        w = w * unit;
      }
    }
  }
  if (op == 1) return ;
  for (int i = 0; i < N; ++i) p[i].r /= N;
}

//Polynomial multiplication多项式相乘$\overrightarrow{X} \times \overrightarrow{Y} = \overrightarrow{Z}$
void polynomial_multi(const int a[], const int an, const int b[], const int bn,
                      int res[], int &n) {
  int N = 1;
  int i = 0;
  n = max(an, bn);
  while (N < n + n) N <<= 1; //FFT的项数必须是2的幂
  for (i = 0; i < an; ++i) FFT_A[i] = Complex(a[i], 0.0);
  for (; i < N; ++i) FFT_A[i] = Complex(0, 0);
  for (i = 0; i < bn; ++i) FFT_B[i] = Complex(b[i], 0.0);
  for (; i < N; ++i) FFT_B[i] = Complex(0, 0);
  FFT(FFT_A, N, 1);
  FFT(FFT_B, N, 1);
  for (i = 0; i < N; i++) FFT_A[i] = FFT_A[i] * FFT_B[i];
  FFT(FFT_A, N, -1);
  for (i = 0, n = N; i < N; i++) res[i] = round(FFT_A[i].real());
}

//Polynomial multiplication多项式相乘$\overrightarrow{X} \times \overrightarrow{Y} = \overrightarrow{Z}$
void polynomial_multi(const int a[], const int an, const int b[], const int bn,
                      int &res, int &n) {
  int N = 1;
  int i = 0;
  n = max(an, bn);
  while (N < n + n) N <<= 1; //FFT的项数必须是2的幂
  for (i = 0; i < an; ++i)FFT_A[i] = Complex(a[i], 0.0);
  for (; i < N; ++i) FFT_A[i] = Complex(0, 0);
  for (i = 0; i < bn; i++) FFT_B[i] = Complex(b[i], 0.0);
  for (; i < N; ++i) FFT_B[i] = Complex(0, 0);
  FFT(FFT_A, N, 1);
  FFT(FFT_B, N, 1);
  for (i = 0; i < N; i++) FFT_A[i] = FFT_A[i] * FFT_B[i];
  FFT(FFT_A, N, -1);
  for (i = 0, n = N; i < N; i++) res[i] = round(FFT_A[i].real());
}

//写法二
Complex PW[NUM * 4], IPW[NUM * 4], CPW[NUM * 4];
int N;
void initFFT(int n) {
  if (N == n) return ;
  for (N = 1; n + n > N; N <<= 1);
  for (int i = 0; i < N; ++i) {
    double ang = i * 2. * PI / N;
    double co = cos(ang);
    double si = sin(ang);
    PW[i] = Complex(co, si);
    IPW[i] = Complex(co, -si);
  }
}
void fft(Complex *a, bool inv) {
  for (int i = 0, j = 0; i < N; i++) {
    if (i > j) swap(a[i], a[j]);
    for (int l = N >> 1; (j ^= l) < l; l >>= 1);
  }
  for (int len = 2, shift = N >> 1; len <= N; len <<= 1, shift >>= 1) {
    int len2 = len >> 1;
    for (int j = 0; j < len2; ++j) {
      CPW[j] = inv ? IPW[j * shift] : PW[j * shift];
    }
    for (int i = 0; i < N; i += len) {
      for (int j = 0; j < len2; ++j) {
        const Complex u = a[i + j];
        const Complex v = a[i + j + len2] * CPW[j];
        a[i + j] = u + v;
        a[i + j + len2] = u - v;
      }
    }
  }
  if (!inv) return ;
  for (int i = 0; i < N; ++i) a[i] = a[i] * (1. / N);
}
//二维FFT
void FFT2D(Complex(&a)[mxn][mxn], bool rev) {
  for (int i = 0; i < CN; i++) FFT(a[i], rev);
  for (int i = 0; i < CN; i++) for (int j = i; j < CN; j++) swap(a[i][j], a[j][i]);
  for (int i = 0; i < CN; i++) FFT(a[i], rev);
  for (int i = 0; i < CN; i++) for (int j = i; j < CN; j++) swap(a[i][j], a[j][i]);
};
/*
应用1: 给一个01串S, 求有多少对(i, j, k)$(i < j < k)$使$S_i = S_j = S_k = 1$, 且j - i = k - j
*/


//数论变换(Number Theory Transformation, NTT)
/*NTT的推导:
0. DFT变换公式: $\displaystyle A(k) = \sum_{i=0}^{N-1}{a(i)\varpi^{ik}}$
    IDFT变换公式: $\displaystyle a(k) = N^{-1}\sum_{i=0}^{N-1}{A(i)\varpi^{-ik}}$
1. 周期性: 由于@$$\begin{array}{l r l}
    & A(k) \cdot B(k) =& C(k) \\
    \Rightarrow &\displaystyle [\sum_{i=0}^{N - 1}{a(i)\varpi^{ik}}] \cdot [\sum_{j=0}^{N-1}{b(j)\varpi^{jk}}] =& \displaystyle \sum_{i=0}^{N - 1}{c(i)\varpi^{ik}} \\
    \Rightarrow &\displaystyle \sum_{i=0}^{N-1}{\sum_{j=0}^{N-1}{a(i)b(j)\varpi^{(i+j)k}}} =& \displaystyle \sum_{i=0}^{N - 1}{(\sum_{x+y=i(\% N)}{a(x)b(y)})\varpi^{ik}} \\
    \Rightarrow &\displaystyle\sum_{j=0}^{i}{a(i)b(i - j)\varpi^{ik}} + \sum_{j=i+1}^{N-1}{a(i)b(N + i - j)\varpi^{(i+N)k}} =& \displaystyle \sum_{x+y=i(\% N)}{a(x)b(y)\varpi^{ik}}, \ (\forall i \in [0, N-1])\\
    \Rightarrow &\displaystyle \forall i \in [0, N-1], k \in [0, N-1], \varpi^{(i+N)k} =& \varpi^{ik} \\
    \Rightarrow &\displaystyle \varpi\mbox{具有周期为N的周期性, 即}\varpi^{N} = 1
\end{array}$$@
2. 求和引理: 若要实现逆变换, 则有: @$$\begin{array}{r l}
    A(k) =&\displaystyle  \sum_{i=0}^{N-1}{a(i)\varpi^{ik}} \\
    a(k) =&\displaystyle  N^{-1} \sum_{i=0}^{N-1}{[\sum_{j=0}^{N-1}{a(j)\varpi^{ij}}]\varpi^{-ik}}\\
        =&\displaystyle  N^{-1} \sum_{i = 0}^{N-1}{\sum_{j=0}^{N-1}{a(j)\varpi^{i(j-k)}}}\\
        =&\displaystyle  N^{-1} \sum_{i = 0}^{N - 1}{a(k)} + N ^ {-1} \sum_{j \neq k} {a(j) [\sum_{i=0} ^{N-1} {(\varpi^{j-k})^{i}}]}\\
\end{array}$$@
    所以, 有$\displaystyle \forall i \neq 0, \sum_{j=0}^{N-1}{(\varpi^i)^j} = \frac{(\varpi^i)^N - 1} {(\varpi^i) - 1} = \frac{(\varpi^N)^i - 1}{(\varpi^i) - 1} = 0$
    即$\varpi^N = 1$, 且$\varpi^i \neq 1(i\neq 0)$
3. FFT的分治计算:
    由$\displaystyle N=\prod_{i=1}^{m}{p_i^{k_i}}$, 令$n=p_i(i=1, 2, \cdots , m), N' = \frac{N}{n}$
    则@$$\begin{array}{r l}
        &A(k + pN') \\
    =   &\displaystyle \sum_{i=0}^{N-1}{a(i)\varpi^{i(k+pN')}} \\
    =   &\displaystyle \sum_{i=0}^{n-1}{[\sum_{j=0}^{N' - 1}{a(i+jn)\varpi^{(i+jn)(k+pN')}}]} \\
    =   &\displaystyle \sum_{i=0}^{n-1}{[\sum_{j=0}^{N' - 1}{a(i+jn)\varpi^{ik + jnk + ipN' + jpN}}]} \\
    =   &\displaystyle \sum_{i=0}^{n-1}{[\varpi^{i(k+pN')} \sum_{j=0}^{N'-1}{a(i+jn)\varpi^{jnk}}]}
    \end{array}$$@
    其中, $0 \leq k < N, 0 \leq k + pN' < N$
    现将规模为N的问题分解为n个规模为N'的子问题, 如此分治, 有:$T(N) = nT(\frac{N}{n}) + O(Nn)$, 其中n | N
    于是, 总的时间复杂度为: $\displaystyle T(N) = O(N\cdot \sum_{i=1}^{m}{(p_i k_i)})$, 若$N=2^m, T(N) = O(N\log N)$
    总结一下, 现在对某一整数N, 如果要进行再整数域上的FFT, 必须满足存在旋转因子$\varpi$, 使@$$\varpi^i\left\{\begin{array}{l l}
    \neq 1, &i = 1, 2, \cdots , N - 1\\
    = 1, &i = N
    \end{array}\right.$$@
    要在整数域了满足上述条件的, 可以是关于素数p的取模运算, 若a是在模p意义下的原根, 旋转因子为$\displaystyle a^{\frac{p-1}{N}}$, 要求N整除p - 1,最后的结果为对p取模后的答案(如果要求准确答案, 需要满足$p > \max{\{a(i), b(i), c(i)\}}(i = 0, 1, 2, \cdots , N - 1)$, 或者对不同素数p进行多次计算, 然后用中国剩余定理求解)
适合$p = 998244353 = 119\times 2^{23} + 1 (2^{23} > 8.3e6)$, 3是p的原根
p = 985661441, 3是p的原根, $(p-1)= 2^{20} * i + 1$
适合的p有很多, 枚举i, 判断(1<<K)*i + 1是否为素数即可
*/
//来源: 2015多校第三场, 1007标程
LL qpow(LL x, LL k, LL mod);
const LL mod = 998244353;
class NTT {
public:
  void solve(vector<int> &A, vector<int> &B, int n) {
    int N = 1;
    while (N < n + n) N <<= 1;
    A.resize(N, 0);
    B.resize(N, 0);
    Ntt(A, N, 1);
    Ntt(B, N, 1);
    for (int i = 0; i < N; ++i)
      A[i] = 1ll * A[i] * B[i] % mod;
    Ntt(A, N, -1);
  }
  NTT(int n = 100000) {
    N = 1;
    while (N < n + n) N <<= 1;
    wi[0] = 1, wi[1] = qpow(wroot, (mod - 1) / N, mod);
    for (int i = 2; i < N; i++)
      wi[i] = 1LL * wi[i - 1] * wi[1] % mod;
  }
private:
  static const int wroot = 3;
  int N;
  int wi[NUM << 2];
  void Ntt(vector<int> &a, int n, int op) {
    for (int i = 0, j = 0; i < n; ++i) { //蝶形变换
      if (i < j) swap(a[i], a[j]);
      for (int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
    for (int h = 2, hf = 1; h <= n; hf = h, h <<= 1) {
      int unit = op == -1 ? N - N / h : N / h;
      for (int i = 0; i < n; i += h) {
        int w = 0;
        for (int j = i; j < i + hf; j++) {
          int u = a[j], t = 1LL * wi[w] * a[j + hf] % mod;
          if ((a[j] = u + t) >= mod) a[j] -= mod;
          if ((a[j + hf] = u - t) < 0) a[j + hf] += mod;
          if ((w += unit) >= N) w -= N;
        }
      }
    }
    if (op == -1) {
      int inv = qpow(n, mod - 2, mod);
      for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv % mod;
    }
  }
} ntt;
/*分治ntt
有递推关系式: $\displaystyle a_n = \sum_{k=0}^{n-1}{k! \cdot a_{n-k}}$
分治: solve(l, r) = solve(l, mid) + deal(l, r) + solve(mid + 1, r);
deal(l, r) = $\displaystyle \sum_{k=l}^{mid}{k! \cdot a_{l + (mid - k)}}$
*/
