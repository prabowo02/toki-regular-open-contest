#include <bits/stdc++.h>
using namespace std;

int X, A[3], S, H;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>X>>A[0]>>A[1]>>A[2];
	
	sort(A,A+3);
	
	for (int i=0;i<3;i++) {
		S+=A[i];
	}
	
	H+=X/S;
	H*=3;
	X%=S;
	
	for (int i=0;i<3;i++) {
		if (X>=A[i]) {
			H++;
			X-=A[i];
		}
	}
	
	cout<<H<<'\n';
	
	return 0;
}
