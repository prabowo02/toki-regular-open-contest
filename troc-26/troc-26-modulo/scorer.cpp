#include <bits/stdc++.h>
using namespace std;

void wa()
{
	puts("WA");
	exit(0);
}

void ac()
{
	puts("AC");
	exit(0);
}

int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	ifstream con(argv[3]);

	int n;
	in >> n;

	string s;
	con >> s;

	if (s.empty())
		wa();

	for (char c : s)
		if (!('0' <= c && c <= '9'))
			wa();


	// remove leading zero
	reverse(s.begin(), s.end());
	while (s.size() > 1 && s.back() == '0')
		s.pop_back();
	reverse(s.begin(), s.end());

	if (s.size() <= 3 && stoi(s) <= n)
		wa();

	string dummy;
	if (con >> dummy)
		wa();

	ac();
	return 0;
}