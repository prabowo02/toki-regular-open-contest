#include <fstream>
#include <iostream>

std::ifstream inp;  // Input file
std::ifstream out;  // Output file
std::ifstream con;  // Contestant output

void ac(std::string reason="") {
  std::cout << "AC\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void ok(double points, std::string reason="") {
  std::cout << "OK\n";
  std::cout << points;
  if (reason != "") {
    std::cout << " " << reason << '\n';
  }
  exit(0);
}

void registerScorer(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  inp = std::ifstream(argv[1]);
  out = std::ifstream(argv[2]);
  con = std::ifstream(argv[3]);
}

void eof(std::ifstream &ifs) {
  std::string dummy;
  if (ifs >> dummy) {
    wa();
  }
}

int readInt(std::ifstream &ifs) {
  std::string s;
  if (!(ifs >> s)) {
    wa();
  }

  if (s.size() > 10) {
    wa();
  }

  long long num = 0;
  for (char c : s) {
    if (c < '0' || c > '9') {
      wa();
    }
    num = num * 10 + c - '0';
  }
  return num;
}

int _gcd(int x, int y) {
  return y ? _gcd(y, x % y) : x;
}

long long _lcm(int x, int y) {
  return 1LL * x * y / _gcd(x, y);
}

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);
  int a = readInt(con), b = readInt(con);
  eof(con);

  int n = readInt(inp);

  if (a < 1 || a > 1000000000 || b < 1 || b > 1000000000) {
    wa();
  }

  if (1LL * (a + b) * n != _gcd(a, b) + _lcm(a, b)) {
    wa();
  }

  ac();
}
