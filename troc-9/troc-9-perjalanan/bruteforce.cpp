#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
pair<char, char> roads[N];

int par[N];
int depth[N];

void toggleA(char &c) {
  if (c == 'a') c = 'A';
  else c = 'a';
}

void toggleB(char &c) {
  if (c == 'b') c = 'B';
  else c = 'b';
}

void toggleRoad(int x) {
  toggleA(roads[x].first);
  toggleB(roads[x].second);
}

void query1(int x, char r) {
  if (r == 'A') {
    toggleA(roads[x].first);
  } else if (r == 'B') {
    toggleB(roads[x].second);
  }
}

void query2(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  while (depth[u] != depth[v]) {
    toggleRoad(u);
    u = par[u];
  }

  while (u != v) {
    toggleRoad(u);
    toggleRoad(v);
    u = par[u]; v = par[v];
  }
}

int goUp(int &u, char &c) {
  if (roads[u].first == 'A' && roads[u].second == 'B') {
    u = par[u];
    return 2;
  }
  if (roads[u].first == 'a' && roads[u].second == 'b') {
    u = par[u];
    return 5;
  }
  if (roads[u].first == 'A') {
    u = par[u];
    if (c == 'A') return 2;
    c = 'A';
    return 3;
  }
  if (roads[u].second == 'B') {
    u = par[u];
    if (c == 'B') return 2;
    c = 'B';
    return 3;
  }

  return -1;
}

int query3(int u, char c, int v, char d) {
  if (depth[u] < depth[v]) {
    swap(u, v);
    swap(c, d);
  }

  int ret = 0;
  while (depth[u] != depth[v]) {
    ret += goUp(u, c);
  }

  while (u != v) {
    ret += goUp(u, c);
    ret += goUp(v, d);
  }

  return ret += (c != d);
}

int main() {
  scanf("%d %d", &n, &q);

  for (int i=1; i<n; i++) {
    int u;
    scanf("%d %c %c", &u, &roads[i].first, &roads[i].second);

    --u;
    par[i] = u;
    depth[i] = depth[u] + 1;
  }

  while (q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int x; char r;
      scanf("%d %c", &x, &r);
      query1(x, r);
    } else if (t == 2) {
      int u, v;
      scanf("%d %d", &u, &v);
      query2(--u, --v);
    } else if (t == 3) {
      int u, v; char c, d;
      scanf("%d %c %d %c", &u, &c, &v, &d);
      printf("%d\n", query3(--u, c, --v, d));
    }
  }

  return 0;
}
