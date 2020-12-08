#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
 private:
  int cc = 0;
  vector<int> p;
  vector<int> sz;
 
 public:
  DisjointSet() {}
  DisjointSet(int s) : p(vector<int>(s, -1)), sz(vector<int>(s, -1)) {}

  int Find(int x) {
    return p[x] == x ? x : p[x] = Find(p[x]);
  }

  void Unite(int x, int y) {
    if (p[x] == -1 || p[y] == -1) return;
    x = Find(x), y = Find(y);
    if (x != y) {
      if (sz[x] < sz[y]) swap(x, y);
      cc--;
      p[y] = x;
      sz[x] += sz[y];
    }
  }

  void MakeSet(int x) {
    cc++;
    p[x] = x;
    sz[x] = 1;
  }

  int CountComponent() {
    return cc;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int N, M;
  cin >> N >> M;

  map<int, vector<pair<int, int>>> A;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int a;
      cin >> a;
      A[-a].emplace_back(i, j);
    }
  }

  vector<int> dx = {1, 0, -1, 0};
  vector<int> dy = {0, 1, 0, -1};
  auto Inside = [&](int x, int y) { return 0 <= x && x < N && 0 <= y && y < M; };

  DisjointSet D(N * M);
  int ans = 1;
  
  for (auto &elem : A) {
    int height = elem.first;
    vector<pair<int, int>> ls = elem.second;
    for (auto p : ls) {
      int cur = p.first * M + p.second;
      D.MakeSet(cur);
      for (int d = 0; d < 4; d++) {
        int x = p.first + dx[d];
        int y = p.second + dy[d];
        if (Inside(x, y)) {
          D.Unite(cur, x * M + y);
        }
      }
    }
    ans = max(ans, D.CountComponent());
  }

  cout << ans << "\n";
  return 0;
}
