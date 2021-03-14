#include <bits/stdc++.h>
using namespace std;

class StronglyConnected {
 public:
  int N;
  vector<bool> vis;
  vector<int> todo, comp;
  vector<vector<int>> adj, radj, comps;

  StronglyConnected(int N) : N(N), vis(N, false), comp(N, -1), adj(N), radj(N) {}

  void AddEdge(int x, int y) {
    adj[x].emplace_back(y);
    radj[y].emplace_back(x);
  }

  void Dfs(int u) {
    vis[u] = true;
    for (auto v : adj[u]) if (!vis[v]) Dfs(v);
    todo.emplace_back(u);
  }

  void Dfs2(int u, int x, vector<int> &vec) {
    comp[u] = x; vec.emplace_back(u);
    for (auto v : radj[u]) if (comp[v] == -1) Dfs2(v, x, vec);
  }

  void Kosaraju() {
    for (int i = 0; i < N; i++) if (!vis[i]) Dfs(i);
    reverse(begin(todo), end(todo));
    for (auto i : todo) if (comp[i] == -1) {
      comps.emplace_back();
      Dfs2(i, int(comps.size()) - 1, comps.back());
    }
  }
};

class TwoSat {
 public:
  int N;
  vector<int> ans;
  StronglyConnected S;

  TwoSat(int N) : N(N), ans(N, 0), S(2 * N) {}

  void EitherOr(int x, int y) {
    x = max(2 * x, -1 - 2 * x);
    y = max(2 * y, -1 - 2 * y);
    S.AddEdge(x ^ 1, y);
    S.AddEdge(y ^ 1, x);
  }

  bool Solve() {
    S.Kosaraju();
    for (int i = 0; i < N; i++) {
      if (S.comp[i * 2] == S.comp[i * 2 + 1]) {
        return false;
      }
    }
    for (int i = 0; i < N; i++) {
      ans[i] = S.comp[i * 2] > S.comp[i * 2 + 1];
    }
    return true;
  }
};

vector<int> Solve(int N, int M, vector<int> T, vector<int> X, vector<int> Y, vector<int> Z) {
  vector<int> lower(N, *min_element(begin(Z), end(Z)));
  vector<int> upper(N, *max_element(begin(Z), end(Z)));

  for (int i = 0; i < M; i++) {
    if (T[i] == 0) {
      upper[X[i]] = min(upper[X[i]], Z[i]);
      upper[Y[i]] = min(upper[Y[i]], Z[i]);
    } else if (T[i] == 1) {
      lower[X[i]] = max(lower[X[i]], Z[i]);
      lower[Y[i]] = max(lower[Y[i]], Z[i]);
    }
  }

  for (int i = 0; i < N; i++) {
    if (lower[i] > upper[i]) {
      return {};
    }
  }

  TwoSat G(N);

  for (int i = 0; i < M; i++) {
    int cntX = (lower[X[i]] == Z[i]) + (upper[X[i]] == Z[i]);
    int cntY = (lower[Y[i]] == Z[i]) + (upper[Y[i]] == Z[i]);
    if (cntX == 0 && cntY == 0) {
      return {};
    } else if (cntX != 0 && cntY == 0) {
      G.EitherOr(lower[X[i]] == Z[i] ? ~X[i] : X[i],
                 lower[X[i]] == Z[i] ? ~X[i] : X[i]);
    } else if (cntX == 0 && cntY != 0) {
      G.EitherOr(lower[Y[i]] == Z[i] ? ~Y[i] : Y[i],
                 lower[Y[i]] == Z[i] ? ~Y[i] : Y[i]);
    } else if (cntX != 0 && cntY != 0) {
      G.EitherOr(lower[X[i]] == Z[i] ? ~X[i] : X[i],
                 lower[Y[i]] == Z[i] ? ~Y[i] : Y[i]);
    }
  }

  if (!G.Solve()) {
    return {};
  }

  vector<int> answer(N, -1);
  for( int i = 0; i < N; i++) {
    answer[i] = G.ans[i] ? upper[i] : lower[i];
  }

  for (int i = 0; i < M; i++) {
    if (T[i] == 0) assert(max(answer[X[i]], answer[Y[i]]) == Z[i]);
    if (T[i] == 1) assert(min(answer[X[i]], answer[Y[i]]) == Z[i]);
  }

  return answer;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> T(M), X(M), Y(M), Z(M);
  for (int i = 0; i < M; i++) {
    cin >> T[i] >> X[i] >> Y[i] >> Z[i];
    T[i]--, X[i]--, Y[i]--;
  }

  vector<int> answer = Solve(N, M, T, X, Y, Z);
  cout << (answer.empty() ? "NO" : "YES") << '\n';
  return 0;
}
