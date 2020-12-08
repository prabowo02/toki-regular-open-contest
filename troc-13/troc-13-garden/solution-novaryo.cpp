#include <bits/stdc++.h>
#define pii pair<int, int>
#define piii tuple<int, int, int>
using namespace std;

int N, M, ans, res;
int A[305][305];
pii par[305][305];
bool vis[305][305];
piii B[90005];

pii findpar(pii u) {
  return par[u.first][u.second] == u ? u : par[u.first][u.second] = findpar(par[u.first][u.second]);
}

void merge(int a, int b, int p, int q) {
  if(vis[p][q] == 0) return;
  pii u = {a, b}, v = {p, q};
  u = findpar(u), v = findpar(v);
  if(v == u) return;
  res--;
  par[v.first][v.second] = u;
}

void go(int r, int c) {
  if(r > 1)merge(r, c, r - 1, c);
  if(r < N)merge(r, c, r + 1, c);
  if(c > 1)merge(r, c, r, c - 1);
  if(c < M)merge(r, c, r, c + 1);
}

int main() {
  scanf("%d %d", &N, &M);
  int cnt = 0;
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= M; j++) {
      par[i][j] = {i, j};
      scanf("%d", &A[i][j]);
      A[i][j] = 1000000000 - A[i][j];
      B[++cnt] = make_tuple(A[i][j], i, j);
    }
  }
  sort(B + 1, B + cnt + 1);
  B[cnt + 1] = make_tuple(2e9, 0, 0);
  int H, r, c;
  for(int i = 1; i <= cnt; i++) {
    tie(H, r, c) = B[i];
    vis[r][c] = 1;
    res++;
    go(r, c);
    if(get<0>(B[i]) != get<0>(B[i + 1])) ans = max(ans, res);
  }
  printf("%d\n", ans);
}