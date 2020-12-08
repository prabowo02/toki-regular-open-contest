#include <bits/stdc++.h>
using namespace std;

bool B;
string S;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>S;
	
	for (char c : S) {
		if (c=='O') {
			if (B) {
				cout<<"Tidak\n";
				return 0;
			}
			
			B=1;
		}
	}
	
	if (B) {
		cout<<"Ya\n";
	}
	else {
		cout<<"Tidak\n";
	}
	
	return 0;
}
