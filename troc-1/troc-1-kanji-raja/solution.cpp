#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int c2(int x) {
  return 1ll * x * (x - 1) / 2 % MOD;
}

vector<int> adj[N];
int n;

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i < n ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int work() {
  int ret = 0;

  for(int i = 1 ; i <= n ; i++) {
    int k = adj[i].size();
    if (k < 4) continue;

    int sums = 0;

    for(int nex : adj[i]) {
      int deg = adj[nex].size();

      sums = (sums + c2(deg-1)) % MOD;
    }

    // choosing left hand and right hand for middle
    int ck2 = c2(k-2);

    // bruteforce lower leg
    for(int nex : adj[i]) {
      int deg = adj[nex].size();
      int cdeg2 = c2(deg-1);

      // number of ways to make upper leg
      sums = (sums + MOD - cdeg2) % MOD;

      int ways = 1ll * cdeg2 * sums % MOD;
      ways = 1ll * ways * ck2 % MOD;

      ret = (ret + ways) % MOD;
    }
  }

  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
