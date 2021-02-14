#include <iostream>
#include <vector>
using namespace std;

#define endl "\n"
#define ll long long
const ll mod = 998244353;

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int k;
	cin >> k;

	vector<int> ans;
	int cr = (1 << 30) - 1;

	for(; k > 0;){
		ans.push_back(cr);
		cr -= k & -k;
		k -= k & -k;
		ans.push_back(cr);

		int tp = cr & ~k;
		cr -= tp & -tp;
	}

	cout << ans.size() << endl;
	for(int i : ans)
		cout << i << " ";
	cout << endl;

	return 0;
}