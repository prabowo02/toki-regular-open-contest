#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int a, x; cin >> a >> x;
	int n = x/a, m = x%a;
	cout << n << " " << m << '\n';
	return 0;
}
