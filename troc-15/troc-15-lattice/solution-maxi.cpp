#include <iostream>
#include <math.h>
using namespace std;

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;

	int ans = -1;
	for(int i = 1; i <= n; i ++){
		int cnt = 0;
		for(int j = 1; j <= i; j ++){
			int k = i * i - j * j;
			int sq = (int)sqrt(k);
			if(sq * sq == k && k > 0) cnt ++;
		}
		if(cnt == 2) ans = i;
	}

	cout << ans << endl;
	return 0;
}
