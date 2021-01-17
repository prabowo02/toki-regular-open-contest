#include <fstream>
#include <iostream>

std::ifstream inp;
std::ifstream out;
std::ifstream con;

void ac(std::string reason="") {
  std::cout << "AC\n";
//  if (reason != "") std::cout << reason << '\n';
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
//  if (reason != "") std::cout << reason << '\n';
  exit(0);
}

void ok(double points, std::string reason="") {
  std::cout << "OK\n";
  std::cout << points;
//  if (reason != "") std::cout << " " << reason << '\n';
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

void TLCassert(bool ok) {
  if (!ok) {
    wa();
  }
}

template<class T> inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

void eof() {
  std::string dummy;
  if (con >> dummy) wa("Extra output from contestant.");
}

std::string capitalize(std::string word) {
  std::string result = "";
  for (char ch : word) {
    if ('a' <= ch && ch <= 'z') {
      result += (char) (ch - 32);
    }else {
      result += ch;
    }
  }
  return result;
}

bool notSimilar(std::string judge, std::string contestant) {
  return capitalize(judge) != capitalize(contestant);
}

void isSimilarWords() {
  std::string judge, contestant;
  while (out >> judge) {
    readStream(con, contestant);
    if (notSimilar(judge, contestant)) wa(capitalize(judge) + " != " + capitalize(contestant));
  }
  eof();
  ac();
}

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);
  isSimilarWords();
}