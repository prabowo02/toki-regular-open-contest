#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define ll long long
const int MX = 100005;

int n, A[MX];
ll L[MX], r[MX]; // r[z][]

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for(int i = 1; i <= n; i ++)
		cin >> A[i];

	for(int i = 2; i <= n; i ++)
		L[i] = L[i - 1] + (ll)(A[i - 1] + 1);

	bool ok = 1;
	for(int i = 1; ok && i <= n; i ++){
		memset(r, 0, sizeof(r));
		r[i + 1] = 0;
		for(int j = i + 2; j <= n; j ++)
			r[j] = r[j - 1] + (A[j - 1] - r[j - 1] <= 0);
		ll R = 0ll;
		for(int j = i + 1; j <= n; j ++)
			R += max(0ll, A[j] - r[j]);
		if(L[i] + R < A[i])
			ok = 0;
	}

	if(ok) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}