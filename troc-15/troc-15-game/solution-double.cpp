#include <iostream>
#include <vector>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef vector<int> vi;

constexpr int ITER = 10000;

vector <double> cnt[2];
double ans[2], done[2];
// Done[i] = probability of player i has done


#include <complex>
const long double PI_LD = 3.14159265358979323846264338327950288419716939937510L;
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, PI_LD / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
            auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
            C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

vd conv(const vd& a, const vd& b) {
    if (a.empty() || b.empty()) return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,0,sz(b)) in[i].imag(b[i]);
    fft(in);
    trav(x, in) x *= x;
    rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

int main(){
  int n, tmpd, a, b;
  cin >> n >> tmpd >> a >> b;
  double d = tmpd;

  vd rolls(tmpd+1);
  for(int i = 1;i <= tmpd;i++) rolls[i] = 1.0/d;

  cnt[0] = vd(n-1);
  cnt[0][a-1] = 1.0;
  cnt[1] = vd(n-1);
  cnt[1][b-1] = 1.0;

  for(int i = 1;i <= ITER;i++){
    for(int j = 0;j <= 1;j++){
      vd ret = conv(cnt[j], rolls);
      done[j] += ret[n-1];
      ans[j] += ret[n-1]*(1.0-done[!j]);
      int m = ret.size();
      // Put ret in cnt[j]
      for(int k = 0;k < n-1;k++)
        cnt[j][k] = ret[k] + (2*(n-1)-k < m ? ret[2*(n-1)-k] : 0.0);
    }
  }
  cout << ans[0] << endl;
}
