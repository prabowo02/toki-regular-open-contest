#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> A(N), B(N), C(N), D(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i] >> C[i] >> D[i];
  }

  vector<tuple<long long, int, int>> edges;

  const auto GetEdges = [&]() {
    map<int, vector<pair<int, int>>> events;
    for (int i = 0; i < N; i++) {
      events[A[i]].emplace_back(B[i], + i + 1);
      events[A[i]].emplace_back(D[i], - i - 1);
      events[C[i]].emplace_back(B[i], + i + 1);
      events[C[i]].emplace_back(D[i], - i - 1);
    }

    for (auto &[_, ev] : events) {
      set<int> active;
      sort(begin(ev), end(ev));
      for (auto [__, type] : ev) {
        int id = abs(type) - 1;
        long long area = 1ll * (C[id] - A[id]) * (D[id] - B[id]);
        if (type > 0) {
          active.emplace(id);
          for (auto v : active) {
            long long area_v = 1ll * (C[v] - A[v]) * (D[v] - B[v]);
            edges.emplace_back(abs(area - area_v), id, v);
          }
        } else {
          active.erase(id);
        }
      }
    }
  };

  for (int i = 0; i < 2; i++) {
    GetEdges();
    swap(A, B);
    swap(C, D);
  }

  vector<int> dsu(N);
  iota(begin(dsu), end(dsu), 0);
  const auto IsConnected = [&](int u, int v) {
    const auto Find = [&](const auto &self, int x) {
      if (dsu[x] == x) return x;
      return dsu[x] = self(self, dsu[x]);
    };
    u = Find(Find, u);
    v = Find(Find, v);
    dsu[u] = v;
    return u == v;
  };

  int cnt = 0;
  long long ans = 0;
  sort(begin(edges), end(edges));
  for (const auto &[w, u, v] : edges) {
    if (cnt + 2 < N && !IsConnected(u, v)) {
      cnt += 1;
      ans += w;
    }
  }

  cout << (cnt == N - 2 ? ans : -1) << '\n';
  return 0;
}
