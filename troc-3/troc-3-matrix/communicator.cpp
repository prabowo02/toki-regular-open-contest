#include <fstream>
#include <iostream>
using namespace std;

int wa() {
    cerr<<"WA\n";
    return 0;
}

int ac(int count) {
    cerr<<"AC\n";
    cerr<<"queries = "<<count<<'\n';
    return 0;
}

const int MAXN=1e3+5, MAXG=2000;

int N, M;
int A[MAXN], B[MAXN];
long long X, Y;
long long H;
string S;

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);

    tc_in>>N>>M;

	for (int i=1;i<=N;i++) {
		tc_in>>A[i];
	}

	for (int i=1;i<=M;i++) {
		tc_in>>B[i];
	}

	H=0;
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=M;j++) {
			H+=A[i]^B[j];
		}
	}

    cout<<N<<' '<<M<<'\n';
    fflush(stdout);

    int guesses_count=0;

    while (true) {
        cin>>S;
        
        if (S=="!") {
			cin>>X;
			if (X==H) {
				return ac(guesses_count);
			}
		}
		
		if (S!="?") {
			return wa();
		}
		
        guesses_count++;
        
        if (guesses_count > MAXG) {
            return wa();
        }
        
        cin>>X>>Y;
        
        if (X<1||Y<1||X>N||Y>M) {
			return wa();
		}
		
		cout<<(A[X]^B[Y])<<'\n';
		fflush(stdout);
    }
}
