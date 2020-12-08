/**
 * Author   : rama_pang
 * Problem  : troc-11-listrik
 * Time     : O(A_max log A_max)
 * Memory   : O(N + A_max)
**/

#include <bits/stdc++.h>
using namespace std;

using lint = long long;

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
vector<int> Freq[MAXA];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  
  cin >> N;
  for (int i = 0; i < N; i++) {
    int Ai;
    cin >> Ai;
    Freq[Ai].push_back(i);
  }

  DisjointSet DSU(N);

  lint ans = 0;
  vector<int> canBeDivided;

  for (int i = MAXA - 1; i >= 1; i--) {
    canBeDivided.clear();
    for (int j = i; j < MAXA; j += i) {
      for (int k = 0; k < (int) Freq[j].size(); k++) {
        canBeDivided.emplace_back(Freq[j][k]);
      }
    }

    if ((int) canBeDivided.size() > 1) {
      for (int j = 1; j < (int) canBeDivided.size(); j++) {
        int u = canBeDivided[j - 1];
        int v = canBeDivided[j];
        if (!DSU.sameSet(u, v)) {
          DSU.join(u, v);
          ans += i;
        }
      }
    }
  }

  cout << ans << "\n";
  return 0;

}
