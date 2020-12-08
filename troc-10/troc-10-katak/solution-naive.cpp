#include <cstdio>
using namespace std;

int n, k, l;
__int8_t memo[100][100];//1000000 x 1000000 exceeds time and memory limit
bool solve(int nA, int nB){//parameters are distances from finish
	if(memo[nA][nB]!=-1)
		return memo[nA][nB];
	if(nB==0)
		return memo[nA][nB]=false;
	bool ans=0;
	for(int i = 1;i <= l && i <= nA && nA-i >= nB-k;i ++){
		ans=ans||!solve(nB, nA-i);
	}
	return memo[nA][nB]=ans;
}
int main(){
	scanf("%d%d%d", &n, &k, &l);//n is distance from finish
	for(int i = 0;i < n;i ++)for(int j = 0;j < n;j ++)
		memo[i][j]=-1;
	printf(solve(n-1, n-1)?"A\n":"B\n");
}