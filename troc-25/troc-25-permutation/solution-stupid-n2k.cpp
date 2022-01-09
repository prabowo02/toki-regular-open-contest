/* O(N^(2K) * NK) */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

const int mod = 998244353;

int n, k;
vector<int> a;
set<vector<int> > s;

int main(){
	scanf("%d %d", &n, &k);
	a.resize(n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);

	int max_msk = 1;
	for(int i = 0; i < 2 * k; i ++)
		max_msk *= n;

	for(int msk = 0; msk < max_msk; msk ++){
		int tmpmsk = msk;
		vector<int> tmp = a;
		for(int i = 0; i < k; i ++){
			int l = tmpmsk % n; tmpmsk /= n;
			int r = tmpmsk % n; tmpmsk /= n;
			if(l > r) swap(l, r);

			int get_max = 0;
			for(int j = l; j <= r; j ++)
				get_max = max(get_max, tmp[j]);
			for(int j = l; j <= r; j ++)
				tmp[j] = get_max;
		}
		s.insert(tmp);
	}

	cout << s.size() << endl;

	return 0;
}