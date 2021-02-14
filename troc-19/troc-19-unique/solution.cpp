#include <iostream>
#include <vector>
using namespace std;

int pref[505], suff[505];

int ask(int lf, int rg){
	cout << "? " << lf << " " << rg << endl;
	int rsp; cin >> rsp;
	return rsp;
}
void answer(vector<int> s){
	cout << "! " << s.size();
	for(int i : s) cout << " " << i;
	cout << endl;
	return;
}

int main(){
	int n; cin >> n;
	pref[1] = 1;
	for(int i = 2; i <= n; i ++)
		pref[i] = ask(1, i);
	suff[n] = 1;
	for(int i = n - 1; i >= 2; i --)
		suff[i] = ask(i, n);
	suff[1] = pref[n];

	vector<int> ans;
	for(int i = 1; i <= n; i ++){
		if(i == 1 && suff[i] == suff[i + 1] + 1) ans.push_back(i);
		else if(i == n && pref[i] == pref[i - 1] + 1) ans.push_back(i);
		else if(pref[i] == pref[i - 1] + 1 && suff[i] == suff[i + 1] + 1) ans.push_back(i);
	}

	answer(ans);
	return 0;
}