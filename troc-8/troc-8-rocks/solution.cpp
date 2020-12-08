#include <bits/stdc++.h>
using namespace std;

const int MAXL=6e3+5;
const long long MOD=1e9+7;

int L, Q;
long long M, K, X, Y;
long long A[MAXL];
string S;

long long expo(long long x,long long y) {
	if (y==1) {
		return x;
	}
	
	long long r;
	r=expo(x,y>>1);
	r=r*r%MOD;
	
	if (y&1) {
		r=r*x%MOD;
	}
	
	return r;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>L>>M>>Q>>S;
	
	for (int i=0;i<L;i++) {
		if (S[i]=='b') {
			A[3*i+1]=A[3*i]+4;
			A[3*i+2]=A[3*i]+2;
			A[3*i+3]=A[3*i]+6;
		}
		
		if (S[i]=='o') {
			A[3*i+1]=A[3*i]+1;
			A[3*i+2]=A[3*i]+1;
			A[3*i+3]=A[3*i]+2;
		}
		
		if (S[i]=='n') {
			A[3*i+1]=A[3*i];
			A[3*i+2]=A[3*i]+2;
			A[3*i+3]=A[3*i]+2;
		}
	}
	
	Y=expo(M*A[3*L]%MOD,MOD-2);
	
	for (int i=0;i<Q;i++) {
		cin>>K;
		X=((K/(3*L))*A[3*L]+A[K%(3*L)])%MOD;
		cout<<X*Y%MOD<<'\n';
	}
	
	return 0;
}
