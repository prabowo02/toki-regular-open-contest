#include <stdio.h>
using namespace std;

int main(){
	int n; scanf("%d", &n);
	if(n & 1) printf("%d\n", n * n - 1);
	else printf("%d\n", n * n);
	return 0;
}