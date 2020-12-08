#include <fstream>
#include <iostream>
using namespace std;

int wa() {
    cerr<<"WA\n";
    return 0;
}

int ac() {
    cerr<<"AC\n";
    return 0;
}

int N;
int X[4], Y[4];
int DX[4], DY[4];
bool sample;
string S;

//U++
//D--
//L-+
//R+-

bool salah(int x,int y) {
	if (X[x]<X[0]&&X[y]<X[0]) {
		return 1;
	}
	
	if (X[x]>X[0]&&X[y]>X[0]) {
		return 1;
	}
	
	if (Y[x]<Y[0]&&Y[y]<Y[0]) {
		return 1;
	}
	
	if (Y[x]>Y[0]&&Y[y]>Y[0]) {
		return 1;
	}
	
	return 0;
}

void update(int x,char c) {
	if (c=='U'||c=='R') {
		X[x]++;
	}
	else {
		X[x]--;
	}
	
	if (c=='U'||c=='L') {
		Y[x]++;
	}
	else {
		Y[x]--;
	}
	
	return;
}

void query() {
	S="UUU";
	
	for (int i=0;i<3;i++) {
		if (DX[i+1]==-1) {
			S[i]='L';
		}
		
		if (DY[i+1]==-1) {
			if (S[i]=='U') {
				S[i]='R';
			}
			else {
				S[i]='D';
			}
		}
		
		update(i+1,S[i]);
	}
	
	return;
}

bool gagal(int x,int y) {
	if (X[x]==X[y]&&Y[x]==Y[y]) {
		if (X[x]!=X[0]||Y[y]!=Y[0]) {
			return 1;
		}
	}
	
	return 0;
}

bool gagal() {
	return gagal(1, 2) || gagal(1, 3) || gagal(2, 3);
}

int jalan(int x,int y) {
	while (X[x]!=X[y]||Y[x]!=Y[y]) {
		if (abs(X[x]-X[y])>=abs(Y[x]-Y[y])) {
			if (X[x]<X[y]) {
				DX[x]=1;
				DX[y]=-1;
			}
			else {
				DX[x]=-1;
				DX[y]=1;
			}
		}
		else {
			if (X[x]>X[0]) {
				DX[x]=1;
				DX[y]=1;
			}
			else {
				DX[x]=-1;
				DX[y]=-1;
			}
		}
		
		if (abs(X[x]-X[y])<=abs(Y[x]-Y[y])) {
			if (Y[x]<Y[y]) {
				DY[x]=1;
				DY[y]=-1;
			}
			else {
				DY[x]=-1;
				DY[y]=1;
			}
		}
		else {
			if (Y[x]>Y[0]) {
				DY[x]=1;
				DY[y]=1;
			}
			else {
				DY[x]=-1;
				DY[y]=-1;
			}
		}
		
		query();
		cout<<S<<'\n';
		fflush(stdout);
		cin>>S;
		
		if (S.length()>1) {
			return wa();
		}
		
		if (S[0]!='U'&&S[0]!='D'&&S[0]!='L'&&S[0]!='R') {
			return wa();
		}

		update(0, S[0]);

		if (gagal()) {
			cout<<"STOP\n";
			fflush(stdout);
			return wa();
		}
	}
	
	cout<<"STOP\n";
	fflush(stdout);
	return ac();
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
	
	tc_in>>N>>sample;
	
	for (int i=0;i<4;i++) {
		X[i]=0;
		Y[i]=0;
	}
	
	for (int i=1;i<=N;i++) {
		tc_in>>S;
		cout<<S<<'\n';
		fflush(stdout);
		
		for (int i=0;i<3;i++) {
			update(i+1,S[i]);
		}
		
		cin>>S;
		
		if (S.length()>1) {
			return wa();
		}
		
		if (S[0]!='U'&&S[0]!='D'&&S[0]!='L'&&S[0]!='R') {
			return wa();
		}
		
		update(0,S[0]);
		
		if (sample) {
			if (gagal()) {
				cout<<"STOP\n";
				fflush(stdout);
				return wa();
			}
			
			continue;
		}
		
		if (salah(1,2)) {
			return jalan(1,2);
		}
		
		if (salah(1,3)) {
			return jalan(1,3);
		}
		
		if (salah(2,3)) {
			return jalan(2,3);
		}
	}
	
	cout<<"STOP\n";
	fflush(stdout);
	return ac();
}
