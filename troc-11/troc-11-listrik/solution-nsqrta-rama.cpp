/**
 * Author   : rama_pang
 * Problem  : troc-11-listrik
 * Time     : O(N sqrt A_max)
 * Memory   : O(N sqrt A_max)
**/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int MAXA = 100005;

struct DisjointSet {
  vector<int> root;
  vector<int> sz;

  DisjointSet(int n) {
    root.resize(n);
    iota(begin(root), end(root), 0);
    sz.assign(n, 1);
  }

  int find(int n) {
    return root[n] == n ? n : root[n] = find(root[n]); 
  }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (sz[a] > sz[b]) {
      swap(a, b);
    }
    root[a] = b;    
    sz[b] += sz[a];
    sz[a] = 0;
    return true;
  }

  bool sameSet(int a, int b) {
    a = find(a);
    b = find(b);
    return a == b;
  }
};


int N;
int A[MAXN];
vector<int> haveFactor[MAXA];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  DisjointSet DSU(N);

  for (int i = 0; i < N; i++) {
    for (int j = 1; j * j <= A[i]; j++) {
      if (A[i] % j == 0) {
        haveFactor[j].emplace_back(i);
        if (j * j != A[i]) {
          haveFactor[A[i] / j].emplace_back(i);
        }
      }
    }
  }


  long long ans = 0;

  for (int i = MAXA - 1; i >= 1; i--) {
    if ((int) haveFactor[i].size() <= 1) {
      continue;
    }
    int key = haveFactor[i][0];
    for (int j = 1; j < (int) haveFactor[i].size(); j++) {
      if (!DSU.sameSet(key, haveFactor[i][j])) {
        DSU.join(key, haveFactor[i][j]);
        ans += i;
      }
    }
  }

  cout << ans << "\n";
  return 0;
}
