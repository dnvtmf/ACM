///快速傅里叶变换FFT(Fast Fourier Transformation)
//F常被用来为多项式乘法加速, 即在$O(n\log{n})$复杂度内完成多项式乘法
//也需要用FFT算法来解决需要构造多项式相乘来进行计数的问题
//#incldue <complex>
//typedef std::complex<double> Complex;
struct Complex//复数类, 可以直接用STL库中的complex<double>
{
    double r, i;
    Complex(double _r = 0.0, double _i = 0.0) {r = _r, i = _i;}
    Complex operator + (const Complex &b) const {return Complex(r + b.r, i + b.i);}
    Complex operator - (const Complex &b) const {return Complex(r - b.r, i - b.i);}
    Complex operator * (const Complex &b) const
    {
        return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
    double real() {return r;}
    double image() {return i;}
};
void brc(vector<Complex> &p, int N)
{
    int i, j, k;
    for(i = 1, j = N >> 1; i < N - 2; i++)
    {
        if(i < j) swap(p[i], p[j]);
        k = N >> 1;
        while(j >= k) j -= k, k >>= 1;
        if(j < k) j += k;
    }
}
void FFT(vector<Complex> &p, int N, int op)//op = 1表示DFT傅里叶变换, op=-1表示傅里叶逆变换
{
    brc(p, N);
    for(int h = 2; h <= N; h <<= 1)
    {
        int i = h >> 1;
        Complex unit(cos(PI * 2.0 * op / h), sin(PI * 2.0 * op / h));
        for(int j = 0; j < N; j += h)
        {
            Complex w(1.0, 0.0);
            for(int k = j; k < i + j; k++)
            {
                Complex u = p[k], t = w * p[k + i];
                p[k] = u + t;
                p[k + i] = u - t;
                w = w * unit;
            }
        }
    }
}
//Polynomial multiplication多项式相乘$\overrightarrow{X} \times \overrightarrow{Y} = \overrightarrow{Z}$
void polynomial_multi(const vector<int> &a, const vector<int> &b, vector<int> &res, int n)
{
    int N = 1;
    int i = 0;
    while(N < n + n) N <<= 1;//FFT的项数必须是2的幂
    vector<Complex> A(N, Complex(0.0)), B(N, Complex(0.0)), D(N);
    for(i = 0; i < (int)a.size(); i++)A[i] = Complex(a[i], 0.0);
    for(i = 0; i < (int)b.size(); i++) B[i] = Complex(b[i], 0.0);
    FFT(A, N, 1);
    FFT(B, N, 1);
    for(i = 0; i < N; i++) D[i] = A[i] * B[i];
    FFT(D, N, -1);
    for(i = 0, res.clear(); i < N; i++) res.PB(round(D[i].real() / N));
}

/*
应用1: 给一个01串S, 求有多少对(i, j, k)$(i < j < k)$使$S_i = S_j = S_k = 1$, 且j - i = k - j
*/
