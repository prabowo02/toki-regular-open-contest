#include <bits/stdc++.h>
using namespace std;

void WA(string reason){
	cout << "WA" << endl; exit(0);
}
void AC(){
	cout << "AC" << endl; exit(0);
}

#define ll long long
ll GCD, LCM;
ll A, B, C;
ll jA, jB;

void read_contestant(ifstream &is){
	if(!(is >> A)) WA("No Output!");
	if(!(is >> B)) WA("Incomplete Output!");
	if((is >> C)) WA("Excessive Output!");
}

void check(){
	ll inv = LCM % GCD;

	if(inv != 0){
		if(A == -1 && B == -1) AC();
		WA("Incorrect Pair!");
	}

	ll get_gcd = __gcd(A, B);
	if(get_gcd != GCD) WA("Wrong GCD!");
	ll get_lcm = (A / get_gcd) * B;
	if(get_lcm != LCM) WA("Wrong LCM!");

	if(A + B == jA + jB) AC();
	else WA("Not The Best Pair!");
}

int main(int argc, char *argv[]){
	ifstream tc_in(argv[1]);
	ifstream tc_out(argv[2]);
	ifstream con_out(argv[3]);
	tc_in >> GCD >> LCM;
	tc_out >> jA >> jB;

	read_contestant(con_out);

	check();
	return 0;
}
