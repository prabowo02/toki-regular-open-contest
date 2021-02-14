#include <iostream>
using namespace std;

#define endl "\n"
#define ll long long
const ll mod = 998244353;

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int p, q;
	cin >> p >> q;

	int total = p * p + q * q + 1;

	if(total % 4 == 0)
		cout << total / 4 << endl;
	else
		cout << -1 << endl;
	
	return 0;
}