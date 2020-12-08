#include <fstream>
#include <iostream>

std::ifstream inp;
std::ifstream out;
std::ifstream con;

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

template<class T>
inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

void eof() {
  std::string dummy;
  if (con >> dummy) wa();
}

void compareRemainingLines() {
  std::string judge, contestant;
  while (out >> judge) {
    readStream(con, contestant);
    if (judge != contestant) wa();
  }
  eof();
  ac();
}

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);

  std::string conFound, judgeFound;
  readStream(con, conFound); readStream(out, judgeFound);
  if (conFound != judgeFound) wa();

  if (conFound == "YES") {
    std::string moves;
    readStream(con, moves);

    int N, M;
    inp >> N >> M;

    int cur = 0;
    for (int i = 0; i < moves.size(); ++i) {
      if (moves[i] == 'L') {
        cur -= i*2 + 1;
      } else if (moves[i] == 'R') {
        cur += i*2 + 1;
      } else {
        wa();
      }

      if (cur < 1 || cur > N) wa();
    }

    if (cur != M) wa();
  }

  eof();
  ac();
  return 0;
}
