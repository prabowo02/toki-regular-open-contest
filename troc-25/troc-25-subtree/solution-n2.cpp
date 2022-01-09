#include <cstdio>
#include <vector>

const int N = 100005;
const int MOD = 998244353;

int n;
int a[N];
std::vector<int> adj[N];
int q;

void update(int x) {
  for (int y : adj[x]) {
    a[y] = (a[y] + a[x]) % MOD;
  }
}

int query(int x) {
  int ret = 0;
  for (int y : adj[x]) {
    ret = (ret + a[y]) % MOD;
  }
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int t, x;
    scanf("%d %d", &t, &x);
    --x;

    if (t == 1) update(x);
    else if (t == 2) printf("%d\n", query(x));
  }
  return 0;
}
