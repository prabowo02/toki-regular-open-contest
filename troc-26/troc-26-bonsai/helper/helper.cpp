#include <bits/stdc++.h>
using namespace std;

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
  ColorDebugger& operator<<(ostream&(*pManip)(ostream&)){
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

const int MAXN = 1e5;
typedef vector <int> vi;
#define fi first
#define se second
#define pb push_back
#define all(v) begin(v), end(v)
#define sz(v) (int) v.size()
#define trav(nx, v) for(auto &nx : v)

vector <int> edge[MAXN + 5];
int dist[MAXN + 5];

void checkDistanceFromRoot(int pos, int par = -1){
  if(par == -1) dist[pos] = 0;
  else dist[pos] = dist[par] + 1;
  for(auto &nx : edge[pos]){
    if(par == nx) continue;
    checkDistanceFromRoot(nx, pos);
  }
}

pair<int, int> checkChain(int n){
  vector <int> ends;
  for(int i = 1;i <= n;i++){
    if(sz(edge[i]) > 2){
      bcout << "Not chain because node " << i << " has " << sz(edge[i]) << endl;
      return {-1, -1};
    }
    if(sz(edge[i]) == 1) ends.pb(i);
  }
  checkDistanceFromRoot(ends[0]);
  int curDist = dist[1];
  checkDistanceFromRoot(ends[1]);
  curDist = min(dist[1], curDist);
  bcout << "Distance from root is " << curDist << endl;
  return {ends[0], ends[1]};
}

void checkAverageDegree(int n){
  vi bucket(n);
  for(int i = 1;i <= n;i++){
    bucket[sz(edge[i]) - (i != 1)]++;
  }
  vector <int> perm(n);
  iota(all(perm), 0);
  sort(all(perm), [&](int a, int b){
    return bucket[a] > bucket[b];
  });
  bcout << "Child count " << endl;
  trav(i, perm){
    if(bucket[i] == 0) break;
    cout << i << " child: " << bucket[i] << endl;
  }
}

int main(){
  int n; cin >> n;
  vector <int> isi(n);
  for(auto &cur: isi) cin >> cur;
  for(int i = 1;i < n;i++){
    int u, v; cin >> u >> v;
    edge[u].pb(v);
    edge[v].pb(u);
  }

  ycout << "Currently checking chain..." << endl;
  auto ret = checkChain(n);
  cout << ret.fi << " " << ret.se << endl;

  ycout << "Currently checking degree..." << endl;
  checkAverageDegree(n);
}