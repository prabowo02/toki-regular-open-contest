#include <cstdio>

const int MAXA = 100001;

int n, mx;

unsigned short cnt[MAXA];

void read() {
  scanf("%d", &n);
  int a;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a);
    mx = (a > mx ? a : mx);
    ++cnt[a];
  }
  ++mx;
}

int par[MAXA];
int rt[8];
int root(int u) {
  int r = 0;
  while (u != par[u]) {
    rt[r++] = u;
    u = par[u];
  }

  while (r--) {
    par[rt[r]] = u;
  }

  return u;
}

void init() {
  for (int i = 1; i < mx; ++i) par[i] = i;
}

void solve() {
  long long ans = 0;
  for (int i = mx-1; i > 0; --i) {
    int frst = -1;
    if (cnt[i] > 0) {
      ans += 1LL * i * (cnt[i] - 1);
      frst = i;
    }

    for (int j = i*2; j < mx; j += i) {
      if (cnt[j] == 0) continue;

      if (frst == -1) frst = root(j);
      if (root(j) != frst) {
        par[par[j]] = frst;
        ans += i;
      }
    }
  }

  printf("%lld\n", ans);
}

int main() {
  read();
  init();
  solve();
  return 0;
}
