#include <bits/stdc++.h>
using namespace std;

int T, X, Y, A, B;

bool dp(int x,int y) {
	if (x>=y) {
		return 1;
	}
	
	if (2*x<=y||x<=B) {
		if (y>=A||B>=x+A) {
			return 0;
		}
		
		return 1;
	}
	
	if (y>=A) {
		return dp(2*x-y,y-x);
	}
	
	return 1;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>T>>A>>B;
	
	for (int i=1;i<=T;i++) {
		cin>>X>>Y>>A>>B;
		
		if (dp(X,Y)) {
			cout<<"AMNU\n";
		}
		else {
			swap(A,B);
			swap(X,Y);
			
			if (dp(X,Y+B)&&dp(X-Y,Y)) {
				cout<<"YOGA\n";
			}
			else {
				cout<<"SALMAN\n";
			}
		}
	}
	
	return 0;
}
