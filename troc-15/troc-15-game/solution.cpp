#include <iostream>
#include <iomanip>
using namespace std;

#define ll long long
const int MX = 5005;
const ll mod = 998244353;
#define max(x, y) (x > y ? x : y)

ll sm[MX], a[MX], b[MX], inv[2 * MX];

int main(){
  cin.tie(0) -> sync_with_stdio(0);

  int n, d, sa, sb;
  cin >> n >> d >> sa >> sb;
  
  inv[0] = inv[1] = 1ll;
  for(int i = 2; i < 2 * MX; i ++)
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;

  sa = min(sa, n - d); sb = min(sb, n - d);

  ll p = inv[d];
  a[sa] = 1; b[sb] = 1;
  ll ans = 0, cr = 1;

  for(int i = 0; i < n; i ++){
    (ans += (cr * a[n - d]) % mod * p % mod) %= mod;
    (cr -= b[n - d] * p % mod) %= mod; if(cr < 0) cr += mod;
    (a[n - d] *= (1 + mod - p)) %= mod; if(a[n - d] < 0) a[n - d] += mod;
    (b[n - d] *= (1 + mod - p)) %= mod; if(b[n - d] < 0) b[n - d] += mod;

    sm[0] = 0;
    for(int i = 1; i < n - d; i ++)
      sm[i] = (sm[i - 1] + a[i]) % mod;
    for(int i = 1; i < n - d; i ++)
      a[i] = (sm[i - 1] + mod - sm[max(0, i - d - 1)]) % mod * 1ll * p % mod;
    for(int i = 1; i <= d; i ++)
      (a[n - d] += (sm[n - d - 1] + mod - sm[max(0, n - d - i - 1)]) % mod* 1ll * p % mod) %= mod;

    sm[0] = 0;
    for(int i = 1; i < n - d; i ++)
      sm[i] = (sm[i - 1] + b[i]) % mod;
    for(int i = 1; i < n - d; i ++)
      b[i] = (sm[i - 1] + mod - sm[max(0, i - d - 1)]) % mod * 1ll * p % mod;
    for(int i = 1; i <= d; i ++)
      (b[n - d] += (sm[n - d - 1] + mod - sm[max(0, n - d - i - 1)]) % mod* 1ll * p % mod) %= mod;
  }

  (ans += a[n - d] * 1ll * cr % mod * 1ll * d % mod * 1ll * inv[2 * d - 1] % mod) %= mod;

  cout << ans << endl;
  return 0;
}