#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long LL;
const int MAXN = 1e5;
#define int long long
#define pb push_back
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (int)v.size()

int n;
LL isi[MAXN + 5];
vector <int> edge[MAXN + 5];

LL dp(int pos, int k, int par = -1) {
  priority_queue <LL, vector <LL>, greater<LL>> kbest;
  LL ret = isi[pos];
  if(sz(edge[pos]) < k) return isi[pos];
  trav(nx, edge[pos]) {
    if (nx == par) continue;
    LL nxCost = dp(nx, k, pos);
    ret += nxCost;
    kbest.push(nxCost);
    if (sz(kbest) > k) {
      ret -= kbest.top();
      kbest.pop();
    }
  }
  if (sz(kbest) == k) return ret;
  return isi[pos];
}

constexpr int MOD = 998244353;

namespace Color {
enum Code {
  FG_RED     = 31,
  FG_GREEN   = 32,
  FG_YELLOW  = 33,
  FG_BLUE    = 34,
  FG_MAGENTA = 35,
  FG_CYAN    = 36,
  FG_DEFAULT = 39
};
class ColorDebugger {
  Code code;
 public:
  ColorDebugger(Code pCode) : code(pCode) {}
  template <class T>
  ColorDebugger& operator<<(const T &other) {
    cerr << "\033[" << code << "m" << other << "\033[" << FG_DEFAULT << "m";
    return *this;
  }
  ColorDebugger& operator<<(ostream & (*pManip)(ostream&)) {
    (*pManip)(cerr);
    return *this;
  }
};
}

using namespace Color;
ColorDebugger rcout(FG_RED);
ColorDebugger ycout(FG_YELLOW);
ColorDebugger gcout(FG_GREEN);
ColorDebugger bcout(FG_BLUE);
ColorDebugger mcout(FG_MAGENTA);
ColorDebugger ccout(FG_CYAN);


int32_t main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> isi[i];
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    edge[p].pb(i);
    // cout << p << " " << i << endl;
    // cout << p << "-" << isi[p] << " " << i << "-" << isi[i] << endl;
  }
  // LL ans = LLONG_MIN;
  // LL ans = chain(1);
  // bcout << ans << endl;
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    LL curans = dp(1, i);
    ans += curans;
    ans %= MOD;
    // cout << curans << endl;
    // bcout << i << " " << curans << endl;
    // bcout << i << "-ary, depth: " << maxDepth << " - " << maxd << endl;
    // ans = max(ans, curans);
  }
  cout << ans << endl;
}