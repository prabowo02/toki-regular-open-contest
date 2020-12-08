#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;



vector<pair<int, int>> adj[N];
int depth[N];
pair<int, int> parent[N];

int n, k, q;

void read() {
  scanf("%d %d", &n, &k);
  
  for (int i = 1 ; i < n ; i++) {
    int u, v;
    char s[5];

    scanf("%d %d %s", &u, &v, s);
    int ch = s[0] - 'a';

    adj[u].push_back({v, ch});
    adj[v].push_back({u, ch});
  }
}

void dfs(int now, int prv) {
  for (pair<int, int> nex : adj[now]) {
    if (nex.first == prv) continue;
    depth[nex.first] = depth[now] + 1;
    parent[nex.first] = {now, nex.second};
    
    dfs(nex.first, now);
  }
}

void fetchPath(vector<int> &ret, int u, int v) {
  vector<int> pathU, pathV;
  
  while (u != v) {
    if (depth[u] > depth[v]) {
      pathU.push_back(parent[u].second);
      u = parent[u].first;
    } else {
      pathV.push_back(parent[v].second);
      v = parent[v].first;
    }
  }

  reverse(pathV.begin(), pathV.end());

  ret.clear();
  for (int x : pathU) ret.push_back(x);
  for (int x : pathV) ret.push_back(x);
}

long long solveArray(vector<int> &arr) {
  vector<int> cnt(k, 0);
  int inactive = k;
  long long ret = 0;

  for (int l = 0, r = 0 ; l < arr.size() ; l++) {
    while (inactive > 0 && r < arr.size()) {
      cnt[arr[r]]++;
      inactive -= (cnt[arr[r]] == 1);
      r++;
    }
    if (r == arr.size() && inactive > 0) {
      break;
    }

    ret += (arr.size() - r + 1);
    cnt[arr[l]]--;
    inactive += (cnt[arr[l]] == 0);
  }

  return ret;
} 

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int a, b;
    scanf("%d %d", &a, &b);

    vector<int> arr;
    fetchPath(arr, a, b);
    long long ret = solveArray(arr);

    printf("%lld\n", ret);
  }
}

int main() {
  read();
  dfs(1, -1);
  work();
  return 0;
}
