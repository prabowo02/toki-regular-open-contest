#include <bits/stdc++.h>
using namespace std;

int N;
int X[5];
int Y[5];
char C;
string S;

int main () {
	while (cin>>S) {
		if (S=="STOP") {
			break;
		}
		
		for (int j=1;j<=3;j++) {
			C=S[j-1];
			
			if (C=='L'||C=='U') {
				X[j]++;
			}
			else {
				X[j]--;
			}
			
			if (C=='R'||C=='U') {
				Y[j]++;
			}
			else {
				Y[j]--;
			}
		}
		
		X[0]=min(max(X[1],X[2]),min(max(X[1],X[3]),max(X[2],X[3])));
		Y[0]=min(max(Y[1],Y[2]),min(max(Y[1],Y[3]),max(Y[2],Y[3])));
		
		if (X[0]>X[4]) {
			C='L';
		}
		else {
			C='D';
		}
		
		if (Y[0]>Y[4]) {
			if (C=='L') {
				C='U';
			}
			else {
				C='R';
			}
		}
		
		X[4]=X[0];
		Y[4]=Y[0];
		
		cout<<C<<'\n';
		fflush(stdout);
	}
	
	return 0;
}
