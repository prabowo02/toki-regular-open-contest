#include <bits/stdc++.h>
using namespace std;

const int HRF=26;
const long long MOD=1e9+7;

int A[HRF];
long long H;
string S;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>S>>S;
	H=1;
	
	for (char c : S) {
		A[c-'A']++;
	}
	
	for (char c : S) {
		H=H*(A[c-'A']+1)%MOD;
	}
	
	cout<<H<<'\n';
	return 0;
}
