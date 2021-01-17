#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n; scanf("%d", &n);
	vector<int> v(n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &v[i]);

	if(n == 1){
		printf("%d\n", v[0]);
		return 0;
	}

	sort(v.begin(), v.end());
	swap(v[1], v[n - 1]);

	for(int i = 0; i < n; i ++)
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}