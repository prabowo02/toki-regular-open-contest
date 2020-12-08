#include <iostream>
using namespace std;
int main()
{
	int a, x, rs = 0; cin >> a >> x;
	while (x >= a) {x -= a; rs++;}
	cout << rs << " " << x << "\n";
}