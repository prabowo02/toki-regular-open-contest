#include <iostream>
#include <fstream>
using namespace std;

const int queryLimit = 100;

int ac() {
	cerr << "AC" << endl;
	return 0;
}

int wa() {
	cerr << "WA" << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	ifstream tc_in(argv[1]);

	int x, y, a, b;
	tc_in >> x >> y >> a >> b;

	long long n = 2ll * x * y - a - b;
	cout << n << endl;

	int queries = 0;

	while (true) {
		char c;
		cin >> c;
		if (c == '?') {
			++queries;
			long long q;
			cin >> q;
			if (queries > queryLimit)
				return wa();
			if (q < 1 || q > n)
				return wa();
			q += a - 1;
			q %= 2 * x;
			cout << (int)(x <= q) << endl;
		} else if (c == '!') {
			int xans, yans, aans, bans;
			cin >> xans >> yans >> aans >> bans;
			if (xans == x && yans == y && aans == a && bans == b) {
				string s;
				if (cin >> s)
					return wa();
				return ac();
			}
			return wa();
		} else {
			return wa();
		}
	}
}
