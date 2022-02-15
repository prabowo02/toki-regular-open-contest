#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long LL;
const int MAXN = 1e5;
#define pb push_back
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (int)v.size()

LL n;
LL isi[MAXN + 5];
vector <LL> edge[MAXN + 5];

LL dp(LL pos, LL k, LL par = -1) {
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

// LL chain(LL pos, LL par = -1){
//   LL ret = 0;
//   trav(nx, edge[pos]){
//     if(nx == par) continue;
//     ret = max(ret, chain(nx, pos));
//   }
//   return ret + isi[pos];
// }

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

#include <algorithm>
#define all(v) begin(v), end(v)

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) cin >> isi[i];
  for (LL i = 2; i <= n; i++) {
    LL p; cin >> p;
    edge[p].pb(i);
  }
  LL ans = LLONG_MIN;
  vector <LL> diffK;
  for(LL i = 1;i <= n;i++){
    if(sz(edge[i])) diffK.pb(sz(edge[i]));
  }
  sort(all(diffK));
  diffK.erase(unique(all(diffK)),diffK.end());
  // LL ans = chain(1);
  // bcout << ans << endl;
  trav(k, diffK){
    LL curans = dp(1, k);
    // bcout << i << " " << curans << endl;
    // bcout << i << "-ary, depth: " << maxDepth << " - " << maxd << endl;
    ans = max(ans, curans);
  }
  cout << ans << endl;
}