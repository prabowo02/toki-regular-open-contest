#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

const int MAXS = 30005;
const int MAXP = 1005;

int n;
char s[MAXS];
int a[MAXS];
long long m;
int p;

namespace FFT {

const int MAXN = 1 << 20;

typedef complex<double> ftype;
const double pi = acos(-1);
ftype w[MAXN];

void init_fft() {
  for(int i = 0; i < MAXN; i++)
    w[i] = polar(1., 2 * pi * i / MAXN);
}

template<typename T>
void fft(T *in, T *out, int n, int k) {
  if(n == 1) {
    *out = *in;
    return;
  }
  int t = MAXN / n;
  n /= 2;
  fft(in, out, n, 2 * k);
  fft(in + k, out + n, n, 2 * k);
  for (int i = 0, j = 0; i < n; i++, j += t) {
    ftype t = w[j] * out[i + n];
    out[i + n] = out[i] - t;
    out[i] = out[i] + t;
  }
}

const int sz = 16, msk = (1 << 16) - 1;

vector<int> mul(vector<int> a, vector<int> b) {
  int ans_sz = a.size() + b.size() - 1;
  int n = 1 << 32 - __builtin_clz(a.size() + b.size());

  a.resize(n, 0); b.resize(n, 0);

  vector<ftype> A(n), B(n);
  for(int i = 0; i < n; i++) {
    A[i] = ftype(a[i] & msk, a[i] >> sz);
    B[i] = ftype(b[i] & msk, b[i] >> sz);
  }
  vector<ftype> nA(n), nB(n);
  ftype w = polar(1., 2 * pi / n);
  fft(A.data(), nA.data(), n, 1);
  fft(B.data(), nB.data(), n, 1);

  ftype im2 = {0, 2}, im = {0, 1};
  
  for (int i = 0; i < n; i++) {
    ftype lA = (nA[i] + conj(nA[(n - i) % n])) / 2.;
    ftype gA = (nA[i] - conj(nA[(n - i) % n])) / im2;
    ftype lB = (nB[i] + conj(nB[(n - i) % n])) / 2.;
    ftype gB = (nB[i] - conj(nB[(n - i) % n])) / im2;
    A[i] = lA * lB + im * gA * gB;
    B[i] = lA * gB + gA * lB;
  }
  
  fft(A.data(), nA.data(), n, 1);
  fft(B.data(), nB.data(), n, 1);
  reverse(begin(nA) + 1, end(nA));
  reverse(begin(nB) + 1, end(nB));

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    long long a = llround(nA[i].real() / n) % MOD;
    long long b = llround(nB[i].real() / n) % MOD;
    long long c = llround(nA[i].imag() / n) % MOD;

    ans[i] = (a + (b << sz) + (c << 2 * sz)) % MOD;
  }

  ans.resize(ans_sz);
  return ans;
}

vector<int> add(vector<int> a, vector<int> b) {
  int n = a.size();

  a.resize(n, 0); b.resize(n, 0);

  vector<ftype> A(n), B(n);
  for(int i = 0; i < n; i++) {
    A[i] = ftype(a[i] & msk, a[i] >> sz);
    B[i] = ftype(b[i] & msk, b[i] >> sz);
  }
  vector<ftype> nA(n), nB(n);
  ftype w = polar(1., 2 * pi / n);
  fft(A.data(), nA.data(), n, 1);
  fft(B.data(), nB.data(), n, 1);

  ftype im2 = {0, 2}, im = {0, 1};
  
  for (int i = 0; i < n; i++) {
    ftype lA = (nA[i] + conj(nA[(n - i) % n])) / 2.;
    ftype gA = (nA[i] - conj(nA[(n - i) % n])) / im2;
    ftype lB = (nB[i] + conj(nB[(n - i) % n])) / 2.;
    ftype gB = (nB[i] - conj(nB[(n - i) % n])) / im2;
    A[i] = lA + lB;
    B[i] = gA + gB;
  }
  
  fft(A.data(), nA.data(), n, 1);
  fft(B.data(), nB.data(), n, 1);
  reverse(begin(nA) + 1, end(nA));
  reverse(begin(nB) + 1, end(nB));

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    long long a = llround(nA[i].real() / n) % MOD;
    long long b = llround(nB[i].real() / n) % MOD;
    long long c = llround(nA[i].imag() / n) % MOD;

    ans[i] = (a + (b << sz) + (c << 2 * sz)) % MOD;
  }
  return ans;
}

}  

// '', 'B', 'O', 'N', 'BO', 'ON', 'NB', 'BON', 'ONB', 'NBO', 'BONB', ...
int get_last_b_idx(int len) { return len*3 - (len+1) % 3; }
int get_last_o_idx(int len) { return len*3 - (len+0) % 3; }
int get_last_n_idx(int len) { return len*3 - (len+2) % 3; }
int get_first_b_idx(int len) { return len*3 - 2; }
int get_first_o_idx(int len) { return len*3 - 1; }
int get_first_n_idx(int len) { return len*3 - 0; }

pair<vector<int>, vector<int>> get_subsequence_count_sum(int n, char *s, int a[], int p) {
  vector<int> cnt(p*9 + 1);
  vector<int> sum(p*9 + 1);
  cnt[0] = 1;

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'b') {
      cnt[1] = (cnt[1] + cnt[0]) % MOD;
      sum[1] = (1LL * cnt[0] * a[i] + sum[1]) % MOD;
      for (int j = 1; j < p*3; ++j) {
        int idx = get_last_b_idx(j+1);
        int pidx = get_last_n_idx(j);

        (cnt[idx] += cnt[pidx]) %= MOD;
        sum[idx] = (1LL * cnt[pidx] * a[i] + sum[pidx] + sum[idx]) % MOD;
      }
    } else if (s[i] == 'o') {
      cnt[2] = (cnt[2] + cnt[0]) % MOD;
      sum[2] = (1LL * cnt[0] * a[i] + sum[2]) % MOD;
      for (int j = 1; j < p*3; ++j) {
        int idx = get_last_o_idx(j+1);
        int pidx = get_last_b_idx(j);

        (cnt[idx] += cnt[pidx]) %= MOD;
        sum[idx] = (1LL * cnt[pidx] * a[i] + sum[pidx] + sum[idx]) % MOD;
      }
    } else if (s[i] == 'n') {
      cnt[3] = (cnt[3] + cnt[0]) % MOD;
      sum[3] = (1LL * cnt[0] * a[i] + sum[3]) % MOD;
      for (int j = 1; j < p*3; ++j) {
        int idx = get_last_n_idx(j+1);
        int pidx = get_last_o_idx(j);

        (cnt[idx] += cnt[pidx]) %= MOD;
        sum[idx] = (1LL * cnt[pidx] * a[i] + sum[pidx] + sum[idx]) % MOD;
      }
    }
  }

  return {cnt, sum};
}

vector<int> cpb1, cpo1, cpn1, cqb1, cqo1, cqn1;
vector<int> spb1, spo1, spn1, sqb1, sqo1, sqn1;
void init_polynoms(int n, char *s, int a[], int p) {
  vector<int> subsequence_count, subsequence_sum;
  tie(subsequence_count, subsequence_sum) = get_subsequence_count_sum(n, s, a, p);

  cpb1.resize(p*3 + 1, 0); cpb1[0] = 1;
  cpo1 = cpn1 = cqb1 = cqo1 = cqn1 = cpb1;

  spb1.resize(p*3 + 1, 0);
  spo1 = spn1 = sqb1 = sqo1 = sqn1 = spb1;

  for (int i = 1; i <= p*3; ++i) {
    cpb1[i] = subsequence_count[get_first_b_idx(i)];
    cpo1[i] = subsequence_count[get_first_o_idx(i)];
    cpn1[i] = subsequence_count[get_first_n_idx(i)];
    cqb1[i] = subsequence_count[get_last_b_idx(i)];
    cqo1[i] = subsequence_count[get_last_o_idx(i)];
    cqn1[i] = subsequence_count[get_last_n_idx(i)];

    spb1[i] = subsequence_sum[get_first_b_idx(i)];
    spo1[i] = subsequence_sum[get_first_o_idx(i)];
    spn1[i] = subsequence_sum[get_first_n_idx(i)];
    sqb1[i] = subsequence_sum[get_last_b_idx(i)];
    sqo1[i] = subsequence_sum[get_last_o_idx(i)];
    sqn1[i] = subsequence_sum[get_last_n_idx(i)];
  }
}

int solve(int n, char *s, int a[], int p, long long m) {
  init_polynoms(n, s, a, p);

  auto mul = [&p](
      const vector<int> &cpb_n, const vector<int> &cpo_n, const vector<int> &cpn_n, const vector<int> &spb_n, const vector<int> &spo_n, const vector<int> &spn_n,
      const vector<int> &cqb_m, const vector<int> &cqo_m, const vector<int> &cqn_m, const vector<int> &sqb_m, const vector<int> &sqo_m, const vector<int> &sqn_m) {

    auto add = [](const vector<int> &A, const vector<int> &B) {
      int n = A.size();
      vector<int> res(n);
      for (int i = 0; i < n; ++i) res[i] = (A[i] + B[i]) % MOD;
      return res;
    };

    vector<int> cbb = FFT::mul(cpb_n, cqb_m);
    vector<int> cbo = FFT::mul(cpb_n, cqo_m);
    vector<int> cbn = FFT::mul(cpb_n, cqn_m);
    vector<int> cob = FFT::mul(cpo_n, cqb_m);
    vector<int> coo = FFT::mul(cpo_n, cqo_m);
    vector<int> con = FFT::mul(cpo_n, cqn_m);
    vector<int> cnb = FFT::mul(cpn_n, cqb_m);
    vector<int> cno = FFT::mul(cpn_n, cqo_m);
    vector<int> cnn = FFT::mul(cpn_n, cqn_m);

    vector<int> sbb = add(FFT::mul(cpb_n, sqb_m), FFT::mul(spb_n, cqb_m));
    vector<int> sbo = add(FFT::mul(cpb_n, sqo_m), FFT::mul(spb_n, cqo_m));
    vector<int> sbn = add(FFT::mul(cpb_n, sqn_m), FFT::mul(spb_n, cqn_m));
    vector<int> sob = add(FFT::mul(cpo_n, sqb_m), FFT::mul(spo_n, cqb_m));
    vector<int> soo = add(FFT::mul(cpo_n, sqo_m), FFT::mul(spo_n, cqo_m));
    vector<int> son = add(FFT::mul(cpo_n, sqn_m), FFT::mul(spo_n, cqn_m));
    vector<int> snb = add(FFT::mul(cpn_n, sqb_m), FFT::mul(spn_n, cqb_m));
    vector<int> sno = add(FFT::mul(cpn_n, sqo_m), FFT::mul(spn_n, cqo_m));
    vector<int> snn = add(FFT::mul(cpn_n, sqn_m), FFT::mul(spn_n, cqn_m));

    vector<int> cpb_nm(p*3 + 1), cpo_nm(p*3 + 1), cpn_nm(p*3 + 1), cqb_nm(p*3 + 1), cqo_nm(p*3 + 1), cqn_nm(p*3 + 1);
    vector<int> spb_nm(p*3 + 1), spo_nm(p*3 + 1), spn_nm(p*3 + 1), sqb_nm(p*3 + 1), sqo_nm(p*3 + 1), sqn_nm(p*3 + 1);
    for (int i = 0; i <= p*3; ++i) {
      if (i % 3 == 0) {
        cpb_nm[i] = cbn[i];
        cpo_nm[i] = cob[i];
        cpn_nm[i] = cno[i];
        cqb_nm[i] = cob[i];
        cqo_nm[i] = cno[i];
        cqn_nm[i] = cbn[i];

        spb_nm[i] = sbn[i];
        spo_nm[i] = sob[i];
        spn_nm[i] = sno[i];
        sqb_nm[i] = sob[i];
        sqo_nm[i] = sno[i];
        sqn_nm[i] = sbn[i];
      } else if (i % 3 == 1) {
        cpb_nm[i] = cbb[i];
        cpo_nm[i] = coo[i];
        cpn_nm[i] = cnn[i];
        cqb_nm[i] = cbb[i];
        cqo_nm[i] = coo[i];
        cqn_nm[i] = cnn[i];

        spb_nm[i] = sbb[i];
        spo_nm[i] = soo[i];
        spn_nm[i] = snn[i];
        sqb_nm[i] = sbb[i];
        sqo_nm[i] = soo[i];
        sqn_nm[i] = snn[i];
      } else if (i % 3 == 2) {
        cpb_nm[i] = cbo[i];
        cpo_nm[i] = con[i];
        cpn_nm[i] = cnb[i];
        cqb_nm[i] = cnb[i];
        cqo_nm[i] = cbo[i];
        cqn_nm[i] = con[i];

        spb_nm[i] = sbo[i];
        spo_nm[i] = son[i];
        spn_nm[i] = snb[i];
        sqb_nm[i] = snb[i];
        sqo_nm[i] = sbo[i];
        sqn_nm[i] = son[i];
      }
    }

    return make_tuple(cpb_nm, cpo_nm, cpn_nm, cqb_nm, cqo_nm, cqn_nm,
                      spb_nm, spo_nm, spn_nm, sqb_nm, sqo_nm, sqn_nm);
  };

  vector<int> cpb = {1}, cpo = {1}, cpn = {1}, cqb = {1}, cqo = {1}, cqn = {1};
  vector<int> spb = {0}, spo = {0}, spn = {0}, sqb = {0}, sqo = {0}, sqn = {0};
  for (; m; m >>= 1) {
    if (m & 1) {
      tie(cpb, cpo, cpn, cqb, cqo, cqn, spb, spo, spn, sqb, sqo, sqn) = mul(cpb, cpo, cpn, spb, spo, spn, cqb1, cqo1, cqn1, sqb1, sqo1, sqn1);
    }
    if (m) tie(cpb1, cpo1, cpn1, cqb1, cqo1, cqn1, spb1, spo1, spn1, sqb1, sqo1, sqn1) = mul(cpb1, cpo1, cpn1, spb1, spo1, spn1, cqb1, cqo1, cqn1, sqb1, sqo1, sqn1);
  }

  return spb[p*3];
}

int main() {
  scanf("%d", &n);
  scanf("%s", s);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  scanf("%lld", &m);
  scanf("%d", &p);

  FFT::init_fft();

  // vector<int> aa = {1123456789};
  // vector<int> bb = {1987654321};
  // for (int u: FFT::mul(aa, bb)) cerr << u << " "; cerr << endl;

  printf("%d\n", solve(n, s, a, p, m));
  return 0;
}