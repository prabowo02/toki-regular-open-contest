#include <bits/stdc++.h>
using namespace std;

int N;
long long ans;
int par[50005];
vector<int> factor[100005];

inline int findpar(int u) {
  return par[u] == u ? u : par[u] = findpar(par[u]);
}

inline int sameset(int u, int v) {
  return findpar(u) == findpar(v);
}

void merge(int u, int v) {
  par[findpar(u)] = findpar(v);
}

void factorize(int id, int num) {
  int i = 1;
  for(i = 1; i * i < num; i++) {
    if(num % i == 0) {
      factor[i].emplace_back(id);
      factor[num / i].emplace_back(id);
    }
  }
  if(i * i == num) {
    factor[i].emplace_back(id);
  }
}

void solve() {
  int here;
  for(int i = 100000; i > 0; i--) {
    if(factor[i].size() < 2) continue;
    here = factor[i][0];
    for(int j = 1; j < factor[i].size(); j++) {
      if(!sameset(here, factor[i][j])) {
        merge(here, factor[i][j]);
        ans += i;
      }
    }
  }
}

int main() {
  scanf("%d", &N);
  int tmp;
  for(int i = 0; i < N; i++) {
    scanf("%d", &tmp);
    factorize(i, tmp);
    par[i] = i;
  }
  solve();
  printf("%lld\n", ans);
}
