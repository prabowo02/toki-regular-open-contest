#include <bits/stdc++.h>
using namespace std;

const int N = 40005;

int n, q;
int a[N];
pair<vector<int>, int> b[N];

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  --n;
  for (int i = 0; i < n; ++i) {
    a[i] ^= a[i+1];
  }

  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);

    b[i].second = i;
    b[i].first.resize(k);
    for (int j = 0; j < k; ++j) {
      scanf("%d", &b[i].first[j]);
    }

    --k; b[i].first.pop_back();
    for (int j = 0; j < k; ++j) {
      b[i].first[j] ^= b[i].first[j+1];
    }
  } 
}

const int BASE = 1031;
const int MOD = 1004535809;

vector<pair<int, int>> hash_locations;
void hash_substrings(int len) {
  hash_locations.resize(n - len + 1);

  int cur_hash = 0;
  int base_len = 1;
  for (int i = 0; i < len; ++i) {
    cur_hash = (1LL * cur_hash * BASE + a[i]) % MOD;
    base_len = (1LL * base_len * BASE) % MOD;
  }

  hash_locations[0] = {cur_hash, 0};

  for (int i = len; i < n; ++i) {
    cur_hash = (1LL * cur_hash * BASE + a[i] - 1LL * base_len * a[i-len]) % MOD;
    if (cur_hash < 0) cur_hash += MOD;

    hash_locations[i-len+1] = {cur_hash, i-len+1};
  }

  sort(hash_locations.begin(), hash_locations.end());
}

int get_hash(const vector<int> &s) {
  int ret = 0;
  for (int i = 0; i < s.size(); ++i) {
    ret = (1LL * ret * BASE + s[i]) % MOD;
  }

  return ret;
}

int ans[N];
int rights[N];

void solve() {
  sort(b, b + q, [&](const pair<vector<int>, int> &u, const pair<vector<int>, int> &v) {
    if (u.first.size() != v.first.size()) return u.first.size() < v.first.size();
    return u.first < v.first;
  });

  for (int i = 0; i <= n; ++i) rights[i] = n + 1;

  for (int i = 0; i < q; ++i) {
    if (i > 0 && b[i].first == b[i-1].first) {
      ans[b[i].second] = ans[b[i-1].second];
      continue;
    }

    if (i == 0 || b[i].first.size() != b[i-1].first.size()) {
      hash_substrings(b[i].first.size());
    }

    int h = get_hash(b[i].first);
    
    ans[b[i].second] = 0;
    int cur = n + 1;
    for (
        int j = lower_bound(hash_locations.begin(), hash_locations.end(), make_pair(h, -1)) - hash_locations.begin();
        j < hash_locations.size() && hash_locations[j].first == h;
        ++j
    ) {
      int idx = hash_locations[j].second;
      int R = min(idx + (int) b[i].first.size(), n);
      rights[idx] = min(rights[idx], R);

      if (idx > cur) {
        ++ans[b[i].second];
        cur = R;
      } else {
        cur = min(cur, R);
      }
    }

    if (cur <= n) ++ans[b[i].second];
  }

  for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);

  int res = 0;
  int cur = n + 1;
  for (int i = 0; i <= n; ++i) {
    cur = min(cur, rights[i]);

    if (i == cur) {
      ++res;
      cur = n + 1;
    }
  }

  printf("%d\n", res);
}

int main() {
  read();
  solve();
  return 0;
}
