#include <iostream>
#include <vector>
using namespace std;

int X, A[31];
vector<int> V;

int main()
{
	cin >> X;
	for (int i = (1 << 14); i; i >>= 1) 
	{
		if (X & i) {V.push_back(i);}
	}	
	cout << 2 * V.size() << "\n";
	for (int i = 0; i < V.size(); i++)
	{
		A[2 * i] = V[i];
		A[2 * i + 1] = (1 << (15 + i));
	}
	for (int i = 2 * (int)V.size() - 2; i >= 0; i--)
	{
		A[i] |= A[i + 1];
	}
	for (int i = 0; i < 2 * V.size(); i++) 
	{
		cout << A[i]; 
		if (i + 1 < 2 * V.size()) cout << " ";
	}
	cout << "\n";
	return 0;
}
