#include <bits/stdc++.h>
using namespace std;

int bfs(int N, int M) {
  int mask = 0;
  for (int i = 0; i < N; ++i) mask |= 1 << i;
  vector<bool> vis(1 << M, false);
  vis[mask] = true;
  queue<int> q;
  q.push(mask);

  while (q.size()) {
    int mask = q.front();
    q.pop();

    vector<int> pos;
    for (int i = 0; i < M; ++i) if (mask >> i & 1) pos.push_back(i);

    for (int i = 0; i < N - 2; ++i) {
      if (pos[i + 2] + 1 < M) {
        int nmask = mask & ~(1 << pos[i]);
        int j = pos[i + 2] + 1;
        while (nmask >> j & 1) --j;
        nmask |= 1 << j;
        if (!vis[nmask]) {
          vis[nmask] = true;
          q.push(nmask);
        }
      }
    }

    for (int i = N - 1; i >= 2; --i) {
      if (pos[i - 2] - 1 >= 0) {
        int nmask = mask & ~(1 << pos[i]);
        int j = pos[i - 2] - 1;
        while (nmask >> j & 1) ++j;
        nmask |= 1 << j;
        if (!vis[nmask]) {
          vis[nmask] = true;
          q.push(nmask);
        }
      }
    }
  }

  int ret = 0;
  for (int mask = 0; mask < 1 << M; ++mask) {
    if (vis[mask]) {
      ++ret;
    } else if (__builtin_popcount(mask) == N) {
      // for (int i = 0; i < M; ++i) {
      //   if (mask >> i & 1) printf("1");
      //   else printf("0");
      // }
      // printf("\n");
    }
  }
  return ret;
}

int main() {
  int T = 1;
  scanf("%d", &T);
  for (int tc = 0; tc < T; ++tc) {
    int N, M;
    scanf("%d %d", &N, &M);
    printf("%d\n", bfs(N, M));
  }
  return 0;
}
