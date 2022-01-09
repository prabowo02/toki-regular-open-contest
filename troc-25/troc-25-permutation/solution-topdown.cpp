#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define ll long long
const int MX = 305;
const int mod = 998244353;

int N, K, P[MX];
int L[MX], R[MX];
int dp[MX][MX][MX][2];

inline void upd(int &a, int b){
	a += b;
	if(a >= mod) a -= mod;
}

int f(int i, int j, int k, bool d){
	int &res = dp[i][j][k][d];
	if(res == -1){
		res = 0;
		if(i == N) res = 1;
		else if(j == N) res = 0;
		else{
			/* dont use */
			upd(res, f(i, j + 1, k, 0));

			/* use */
			if(L[P[j]] <= i && i <= R[P[j]]){
				if(d == 0 && i != j){
					if(k < K)
						upd(res, f(i + 1, j, k + 1, 1));
				}else
					upd(res, f(i + 1, j, k, d));
			}
		}
	}

	return res;
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> N >> K;
	for(int i = 0; i < N; i ++){
		cin >> P[i];
		P[i] --;
	}

	for(int i = 0; i < N; i ++){
		L[P[i]] = i;
		R[P[i]] = i;
		for(; L[P[i]] > 0 && P[L[P[i]] - 1] < P[i]; L[P[i]] --);
		for(; R[P[i]] < N - 1 && P[R[P[i]] + 1] < P[i]; R[P[i]] ++);
	}

	for(int i = 0; i <= N; i ++)
		for(int j = 0; j <= N; j ++)
			for(int k = 0; k <= K; k ++)
				for(int l = 0; l < 2; l ++)
					dp[i][j][k][l] = -1;
	cout << f(0, 0, 0, 0) << endl;
	return 0;
}