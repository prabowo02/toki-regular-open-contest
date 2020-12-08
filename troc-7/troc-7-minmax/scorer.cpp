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

int N, P;
long long sumA, sumL,sumR;
int A[MAXN];
int L[MAXN];
int R[MAXN];

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);
	
	tc_in>>N;
	
	for (int i=1;i<=N;i++) {
		tc_in>>L[i];
	}
	
	for (int i=1;i<=N;i++) {
		tc_in>>R[i];
	}
	
	tc_out>>P;
	
	for (int i=1;i<=N;i++) {
		con_out>>A[i];
		
		if (A[i]==-1) {
			break;
		}
	}
	
	if ((P==-1)&&(A[1]==-1)) {
		string dummy;
		if(con_out >> dummy)
			return wa();
		return ac();
	}
	
	if ((P==-1)||(A[1]==-1)) {
		return wa();
	}
	
	for (int i=1;i<=N;i++) {
		if (A[i]<L[i]||A[i]>R[i]) {
			return wa();
		}
		
		sumA+=A[i];
		sumL+=L[i];
		sumR+=R[i];
	}
	
	if (sumA==sumL||sumA==sumR) {
		return wa();
	}
	
	string dummy;
	if(con_out >> dummy)
		return wa();
	
	return ac();
}
