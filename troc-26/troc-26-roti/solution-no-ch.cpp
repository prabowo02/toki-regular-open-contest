#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int,int> ii;

const ll MX = 1e15;
const ll INF = 1e18;
int n, m, k;
vector<ll> a, st, bt, dp;

void monge(ll mid) {
    dp = bt = vector<ll>(m+2);
    for (int i = 1; i <= m; i++) {
        ll p = -1, cost = INF;
        for (int j = 1; j <= i; j++) {
            ll cur = dp[j-1]+a[st[j]]*st[i];
            if (cost > cur) {
                cost = cur;
                p = j-1;
            }
        }
        dp[i] = cost+mid;
        bt[i] = bt[p]+1;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    a = st = vector<ll>(n+2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    reverse(a.begin()+1,a.begin()+n+1);
    for (int i = 1; i <= n; i++) {
        while (m > 0 && a[st[m]] <= a[i]) m--;
        st[++m] = i;
    }
    ll ans = INF;
    for (ll l = 0, r = MX; l <= r; ) {
        ll mid = (l+r)/2; monge(mid);
        if (bt[m] <= k) {
            ans = dp[m]-mid*bt[m];
            r = mid-1;
        }
        else l = mid+1;
    }
    assert(ans != INF);
    cout << ans << '\n';
    return 0;
}