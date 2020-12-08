#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;

	vector<int> arr(n);
	for(int i = 0; i < n; i ++)
		cin >> arr[i];

	vector<int> tmp = arr;

	sort(tmp.begin(), tmp.end());

	if(tmp[0] == tmp.back()){
		cout << "EQUAL\n";
		return 0;
	}
	if(tmp == arr){
		cout << "NONDECREASING\n";
		return 0;
	}

	reverse(tmp.begin(), tmp.end());

	if(tmp == arr){
		cout << "NONINCREASING\n";
		return 0;
	}

	cout << "NONE\n";
	return 0;
}