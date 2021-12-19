#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>
#include <map>
#include <utility>

const int MAXN = 50005;

int N, Q;
char S[MAXN];
char P[MAXN];

int ans[MAXN];

void add(int st, int p, int t) {
  if (t > N - p) t = N - p;
  for (int i = 0; i < t; ++i) {
    if (P[st + i] == '1') ++ans[i];
  }
  for (int i = p; i < p + t; ++i) {
    if (P[st + i - p] == '1') ++ans[i];
  }
}

int main() {
  scanf("%d %d", &N, &Q);
  scanf("%s", S);
  scanf("%s", P);

  std::map<std::pair<int, int>, int> pos;
  for (int i = 0; i < N; ++i) {
    pos[{i, 0}] = -i;
  }

  std::pair<int, int> head = {0, 0};
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};

  for (int t = 0; t < Q; ++t) {
    if (S[t] == 'U') {
      ++head.second;
    } else if (S[t] == 'D') {
      --head.second;
    } else if (S[t] == 'R') {
      ++head.first;
    } else if (S[t] == 'L') {
      --head.first;
    }

    for (int k = 0; k < 4; ++k) {
      auto side = pos.find({head.first + dx[k], head.second + dy[k]});
      if (side != pos.end() && side->second > t - N + 1 && side->second != t) {
        add(t, t - side->second + 1, Q - t);
      }
    }

    pos[head] = t + 1;
  }

  int ones = 0;
  for (int i = 0; i < Q; ++i) if (P[i] == '1') ++ones;
  if (N > 1) {
    ans[0] += ones;
    ans[N - 1] += ones;
    for (int i = 1; i < N - 1; ++i) {
      ans[i] += ones * 2;
    }
  }

  for (int i = 0; i < N; ++i) printf("%d\n", ans[i]);
  return 0;
}
