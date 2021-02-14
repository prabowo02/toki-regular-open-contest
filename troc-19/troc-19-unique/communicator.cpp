#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int wa(string s){
	cerr << "WA\n";
	// cerr << "reason = " << s << "\n";
	return 0;
}
int ac(int count){
	cerr << "AC\n";
	// cerr << "queries = " << count << "\n";
	return 0;
}

const int MX = 500;

int n, a[MX + 5], cnt[MX + 5];
vector<int> ans;
string tp;

int main(int argc, char* argv[]){
	ifstream tc_in(argv[1]);
	ifstream tc_out(argv[2]);

	tc_in >> n;
	for(int i = 1; i <= n; i ++)
		tc_in >> a[i];

	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= n; i ++)
		cnt[a[i]] ++;
	for(int i = 1; i <= n; i ++)
		if(cnt[a[i]] == 1) ans.push_back(i);

	cout << n << endl;
	int guess_count = 0;

	while(true){
		if(!(cin >> tp)) return wa("No query given");

		if(tp == "!"){
			int sz; 
			if(!(cin >> sz)) return wa("No Output after ! query");
			vector<int> li;
			for(int x, i = 0; i < sz; i ++){
				if(!(cin >> x)) return wa("Answer Size Incorrect");
				li.push_back(x);
			}
			if(cin >> sz) return wa("Answer Size Incorrect");

			sort(li.begin(), li.end());
			sort(ans.begin(), ans.end());

			if(li == ans) return ac(guess_count);
			else return wa("WA");
		}

		if(tp != "?") return wa("Invalid Query");

		guess_count ++;
		if(guess_count > 5 * n) return wa("Too Many Queries");

		int lf, rg;
		if(!(cin >> lf)) return wa("No L Output");
		if(!(cin >> rg)) return wa("No R Output");
		if(lf < 1 || rg > n || lf > rg) return wa("Out Of Bounds");

		int res = 0;
		memset(cnt, 0, sizeof(cnt));
		for(int i = lf; i <= rg; i ++)
			cnt[a[i]] ++;
		for(int i = lf; i <= rg; i ++)
			if(cnt[a[i]] == 1) res ++;

		cout << res << endl;
	}
}
