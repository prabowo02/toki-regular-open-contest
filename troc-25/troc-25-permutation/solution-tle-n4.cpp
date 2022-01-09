#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define ll long long
const int MX = 305;
const int mod = 998244353;

int N, K, P[MX];
int L[MX], R[MX];
int dp[2][MX][MX];

inline void upd(int &a, int b){
	a += b;
	if(a >= mod) a -= mod;
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> N >> K;
	for(int i = 0; i < N; i ++){
		cin >> P[i];
		P[i] --;
	}

	for(int i = 0; i < N; i ++){
		L[i] = i;
		R[i] = i;
		for(; L[i] > 0 && P[L[i] - 1] < P[i]; L[i] --);
		for(; R[i] < N - 1 && P[R[i] + 1] < P[i]; R[i] ++);
	}

	dp[0][0][0] = 1;
	for(int i = 0; i < N; i ++){
		for(int j = 0; j <= N; j ++)
			for(int k = 0; k <= K; k ++)
				dp[(i + 1) & 1][j][k] = 0;

		for(int j = 0; j <= N; j ++){
			for(int k = 0; k <= K; k ++){
				upd(dp[(i + 1) & 1][j][k], dp[i & 1][j][k]);
				if(j < L[i]) continue;
				for(int ps = max(L[i], j); ps <= R[i]; ps ++){
					int nk = k + 1;
					if(max(L[i], j) == i && ps == i) nk --;
					upd(dp[(i + 1) & 1][ps + 1][nk], dp[i & 1][j][k]);
				}
			}
		}
	}

	int ans = 0;
	for(int k = 0; k <= K; k ++)
		upd(ans, dp[N & 1][N][k]);
	cout << ans << endl;

	return 0;
}
