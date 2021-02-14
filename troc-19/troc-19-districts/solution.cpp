#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5+5, MAX = 1e6;
int n;
struct edge {
  int u, v; ll w;
  bool operator < (const edge &ot) const { return w < ot.w; }
};
ll area[N];
vector<pair<int, int>> events[2][MAX+5]; //0 = horizontal, 1 = vertical
vector<edge> edges;
int par[N];
bool found[N];

int find(int u) {
  if(par[u] == u) return u;
  else return par[u] = find(par[u]);
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
    area[i] = (ll)(c-a) * (ll)(d-b);
    events[0][b].push_back({a, i}); events[0][b].push_back({c, -i});
    events[0][d].push_back({a, i}); events[0][d].push_back({c, -i});
    events[1][a].push_back({b, i}); events[1][a].push_back({d, -i});
    events[1][c].push_back({b, i}); events[1][c].push_back({d, -i});
  }

  for(int ty = 0; ty <= 1; ty++) {
    for(int i = 1; i <= MAX; i++) {
      sort(events[ty][i].begin(), events[ty][i].end());
      pair<int, int> nw = {0, 0};
      for(auto &x : events[ty][i]) {
        if(x.second > 0) {
          if(nw.first == 0) nw.first = x.second;
          else if(nw.second == 0) nw.second = x.second;
          else assert(0);
          if(nw.first != 0 && nw.second != 0) {
            edges.push_back({nw.first, nw.second, abs(area[nw.first] - area[nw.second])});
          }
        } else {
          if(nw.first == -x.second) nw.first = 0;
          else if(nw.second == -x.second) nw.second = 0;
          else assert(0);
        }
      }
    }
  }

  for(int i = 1; i <= n; i++) par[i] = i;
  sort(edges.begin(), edges.end());
  ll ans = 0, prv = -1;
  for(edge e : edges) {
    if(find(e.u) != find(e.v)) {
      par[par[e.u]] = e.v;
      ans += e.w;
      prv = e.w;
    }
  }

  int cc = 0;
  for(int i = 1; i <= n; i++) {
    if(!found[find(i)]) {
      cc++;
      found[par[i]] = 1;
    }
  }

  if(cc == 1) printf("%lld\n", ans-prv);
  else if(cc == 2) printf("%lld\n", ans);
  else puts("-1");

  return 0;
}
