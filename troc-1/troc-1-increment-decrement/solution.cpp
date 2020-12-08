#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, Q, cmd, pos;
	long long L = 0, R = 0, val;
	scanf("%d %d", &N, &Q);
	while(Q--) {
		scanf("%d %d %lld", &cmd, &pos, &val);
		if(cmd == 1) {
			L += val;
			if(pos == N) {
				R += val;
			}
		}
		else if(cmd == 2) {
			R -= val;
			if(pos == N) {
				L -= val;
			}
		}
	}
	printf("%lld\n", max(abs(L), abs(R)));
}