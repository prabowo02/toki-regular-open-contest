#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;

	ll ans = 0;
	ans += 2 * (m-3) * (m-2) + 8 * (m-2);
	ans += 2 * (n-3) * (n-2) + 8 * (n-2);

	cout << ans << '\n';

	return 0;
}