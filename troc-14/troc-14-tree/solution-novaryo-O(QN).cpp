#include <vector>
#include <cstdio>
using namespace std;

int N, Q;
int A[50005], par[50005];
long long ans[50005], sz[50005];
vector<int> adj[50005];

void DFS(int u, int p) {
  sz[u] = A[u];
  for(int v : adj[u]) {
    if(v == p) continue;
    DFS(v, u);
    par[v] = u;
    ans[u] += sz[u] * sz[v];
    sz[u] += sz[v];
  }
}

int main() {
  scanf("%d %d", &N, &Q);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
  }
  int u, v;
  for(int i = 1; i < N; i++) {
    scanf("%d %d", &u, &v);
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  DFS(1, 0);
  int ty;
  long long cnt, bef;
  while(Q--) {
    scanf("%d %d", &ty, &u);
    if(ty == 1) {
      cnt = 0, bef = sz[u];
      while(u != 0) {
        ans[u] += cnt * (sz[u] - bef);
        bef = sz[u];
        sz[u] += cnt;
        if(A[u] == 0) {
          ans[u] += sz[u];
          sz[u]++;
          cnt++;
          A[u] = 1;
        }else {
          sz[u]--;
          ans[u] -= sz[u];
          cnt--;
          A[u] = 0;
        }
        u = par[u];
      }
    }else {
      printf("%lld\n", ans[u]);
    }
  }
}
