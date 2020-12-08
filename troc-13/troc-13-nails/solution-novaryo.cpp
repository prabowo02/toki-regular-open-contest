#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
using namespace std;
using namespace __gnu_pbds;

int N;
gp_hash_table<int, int> id;
int A[10005], dp[10005];
int sum, ans = 1e9, D;

void solve(int gap) {
  int cnt = sum / gap;
  if(cnt > N || cnt < 3) return;
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= N; i++) {
    int bef = (A[i] - gap + sum) % sum;
    if(id.find(bef) != id.end()) {
      dp[i] = 1 + dp[id[bef]];
    }
    if(dp[i] == cnt) {
      ans = min(ans, N - cnt);
      return;
    }
  }
}

int32_t main() {
  scanf("%lld", &N);
  for(int i = 2; i <= N; i++) {
    scanf("%lld", &D);
    A[i] = D + A[i - 1];
    id[A[i]] = i;
    sum += D;
  }
  scanf("%lld", &D);
  sum += D;
  id[0] = 1;
  A[1] = 0;
  int i;
  for(i = 1; i * i <= sum; i++) {
    if(sum % i == 0) {
      solve(i);
      solve(sum / i);
    }
  }
  if(ans != 1e9) printf("%lld\n", ans);
  else puts("-1");
}