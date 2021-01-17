#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>

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

void TLCassert(bool status, std::string message="") {
  if (!status) {
    wa(message);
  }
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

template<class T> inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

void eof() {
  std::string dummy;
  if (con >> dummy) wa("Extra output from contestant.");
}

void getVector(std::ifstream &ifs, int &N, std::vector<int> &vec) {
  vec.resize(N);
  for (int i = 0; i < N; i++) {
    readStream(ifs, vec[i]);
  }
}

bool sameElement(std::vector<int> A, std::vector<int> B) {
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  return A == B;
}

int countMEX(std::vector<int> &A) {
  int pointer_used = 1, result = 0;
  std::bitset<1005> used;

  for (int i = 0; i < A.size(); i++) {
    used.reset();
    pointer_used = 1;
    
    for (int j = i; j < A.size(); j++) {
      used[A[j]] = 1;
      while(used[pointer_used] == 1) pointer_used++;
      result += pointer_used;
    }
  }
  return result;
}

void checkContestantOutput() {
  int N;
  std::vector<int> vec_out, vec_con;
  
  inp >> N;
  getVector(out, N, vec_out);
  getVector(con, N, vec_con);

  TLCassert(sameElement(vec_out, vec_con), "Exist different element.");

  int out_sum = countMEX(vec_out);
  int con_sum = countMEX(vec_con);
  TLCassert(out_sum == con_sum, "Different sum mex");
  
  eof();
  ac("Answer correct: " + std::to_string(out_sum));
}

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);
  checkContestantOutput();
}