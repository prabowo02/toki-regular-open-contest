#include <iostream>
#define ll long long
using namespace std;
int n;
ll to = 0;
int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		ll x; cin >> x;
		to += x << i;
	}
	if (to & ((1 << n) - 1)) {cout << "-1\n";}
	else {cout << (to >> n) << "\n";}
	return 0;
}
