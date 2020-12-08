#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

#ifdef __DEBUG
#define debug if (true)
#else
#define debug if (false)
#endif

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, r, v;
  cin >> n >> r >> v;
  int vp = -1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (vp == -1 || abs(v - x) < abs(v - vp)) {
      vp = x;
    }
  }
  if (vp == v) {
    puts("-1");
    return 0;
  }
  printf("%.6f\n", 1.0 * r / abs(v - vp));
  return 0;
}
