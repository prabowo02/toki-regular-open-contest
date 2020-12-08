#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MOD = 1000000007;

int n, m;
int w[N];
long long pre[N];

int main() {
  scanf("%d %d", &n, &m);
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &w[i]);
    sum += w[i];
  }
  pre[1] = w[0];
  for (int i = 2; i <= n; ++i) pre[i] = pre[i-1] + w[i-1];

  long long ans = 0;
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
    ans = (ans + min(pre[j] - pre[i], sum - pre[j] + pre[i])) % MOD;
  }
  cout << ans << endl;
  return 0;
}
