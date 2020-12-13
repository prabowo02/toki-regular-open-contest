#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
const int N = 2e5 + 10;
const int INF = 1e9 + 50;
int n;
int a[N], idx[N], tree[N * 4], lazy[N * 4];
vector <int> pos[N];

void propogate(int idx , int l , int r) {
  if (lazy[idx] == 0) return;

  if (l != r) {
    lazy[idx << 1] += lazy[idx];
    lazy[idx << 1 | 1] += lazy[idx];
  }

  tree[idx] += lazy[idx];
  lazy[idx] = 0;

  return;
}

int rangeMax(int idx , int l , int r , int from , int to) {
  propogate(idx , l , r);
  if (from > to) return 0;
  if (r < from || l > to) return -INF;
  if (from <= l && r <= to) return tree[idx];
  int mid = l + r >> 1;
  return max(
    rangeMax(idx << 1 , l , mid , from , to),
    rangeMax(idx << 1 | 1 , mid + 1 , r , from , to)
  );
}

void rangeUpdate(int idx , int l , int r , int from , int to , int value) {
  propogate(idx , l , r);
  if (from > to) return;
  if (r < from || l > to) return;
  if (from <= l && r <= to) {
    lazy[idx] += value;
    propogate(idx , l , r);
    return;
  }
  int mid = l + r >> 1;
  rangeUpdate(idx << 1 , l , mid , from , to , value);
  rangeUpdate(idx << 1 | 1 , mid + 1 , r , from , to , value);
  tree[idx] = max(tree[idx << 1] , tree[idx << 1 | 1]);
}

void print(int idx , int  l , int r) {
  propogate(idx , l , r);
  if (l == r) {
    printf(" >> (%d, %d) = %d\n" , l , r , tree[idx]);
    return;
  }
  int mid = l + r >> 1;
  print(idx << 1 , l , mid);
  print(idx << 1 | 1 , mid + 1 , r);
}

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0 ; i < n ; i++) {
    cin >> a[i];
    pos[a[i]].pb(i);
  }

  int ans = 0;
  set <int> pref;
  for (int i = 0 ; i < n ; i++) {
    if (pref.find(a[i]) == pref.end()) {
      pref.insert(a[i]);
      if (pos[a[i]].size() >= 3) {
        rangeUpdate(1 , 0 , n - 1 , pos[a[i]][idx[a[i]] + 1] , pos[a[i]].back() - 1 , 1);
      }
    } else {
      if (idx[a[i]] + 1 < pos[a[i]].size()) {
        rangeUpdate(1 , 0 , n - 1 , pos[a[i]][idx[a[i]]] , pos[a[i]][idx[a[i]] + 1] - 1 , -1);
      }
    }
    ans = max(ans , rangeMax(1 , 0 , n - 1 , 0 , n - 1));
    idx[a[i]]++;
  }

  cout << ans << '\n';
}
