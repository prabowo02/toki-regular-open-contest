#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

const int MAXN=1e5+5;

int N, X, Y;
int A[MAXN];
int B[MAXN];

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);
	
	tc_in>>N;
	
	for (int i=1;i<=N;i++) {
		tc_in>>A[i];
	}
	
	tc_out>>X;
	con_out>>Y;
	
	if (X!=Y) {
		return wa();
	}
	
	for (int i=1;i<=Y;i++) {
		con_out>>B[i];
	}
	
	for (int i=2;i<=Y;i++) {
		if (B[i]==B[i-1]) {
			return wa();
		}
	}
	
	for (int i=2;i<Y;i++) {
		if ((B[i]>B[i-1])==(B[i+1]>B[i])) {
			return wa();
		}
	}
	
	X=0;
	
	for (int i=1;i<=N;i++) {
		if (A[i]==B[X+1]) {
			X++;
			
			if (X==Y) {
				break;
			}
		}
	}
	
	if (X!=Y) {
		return wa();
	}
	
	string dummy;
	if(con_out >> dummy)
		return wa();
	
	return ac();
}
