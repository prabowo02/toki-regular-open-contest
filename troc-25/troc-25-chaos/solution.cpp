#include <iostream>
#include <vector>
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

	int z = -1;
	for(int i = 1; i <= n; i ++)
		if(A[i] >= L[i]) z = i;

	r[z + 1] = 0;
	for(int i = z + 2; i <= n; i ++)
		r[i] = r[i - 1] + (A[i - 1] - r[i - 1] <= 0);
	ll R = 0ll;
	for(int i = z + 1; i <= n; i ++)
		R += max(0ll, A[i] - r[i]);

	if(L[z] + R >= A[z]) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}