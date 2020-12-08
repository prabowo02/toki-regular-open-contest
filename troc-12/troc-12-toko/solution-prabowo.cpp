#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, d;
vector<int> edges[N];
int indeg[N];

int main() {  
  scanf("%d %d", &n, &d);
  for (int u = 0; u < n; ++u) {
    int w;
    scanf("%d", &w);
    for (int j = 0; j < w; ++j) {
      int v;
      scanf("%d", &v);
      edges[--v].push_back(u);
    }

    indeg[u] += w;
  }

  set<int> nodes;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) nodes.insert(i);
  }

  int offset = 0;
  while (nodes.size()) {
    set<int>::iterator it = nodes.lower_bound(offset);
    if (it == nodes.end()) it = nodes.begin();
    int u = *it;
    nodes.erase(it);

    for (int v: edges[u]) {
      if (--indeg[v] == 0) nodes.insert(v);
    }
    printf("%d ", u-offset < 0 ? u-offset+n : u-offset);

    if ((offset -= d) < 0) offset += n;
  }

  printf("\n");
  return 0;
}
