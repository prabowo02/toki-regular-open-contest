#include <iostream>
#include <fstream>
using namespace std;

void ac() {
  puts("AC");
  exit(0);
}

void wa() {
  puts("WA");
  exit(0);
}

int main(int argc, char** argv) {
  ifstream input(argv[1]);
  ifstream judgeOutput(argv[2]);
  ifstream contestantOutput(argv[3]);

  string judgeString, contestantString;
  while (judgeOutput >> judgeString) {
    if (!(contestantOutput >> contestantString)) {
      wa();
    }

    if (judgeString != contestantString) {
      wa();
    }
  }

  if (contestantOutput >> contestantString) {
    wa();
  }

  ac();
  return 0;
}

