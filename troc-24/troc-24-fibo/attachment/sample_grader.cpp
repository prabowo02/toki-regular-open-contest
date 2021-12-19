#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
using namespace std;

void WA(string s){
  cout << "WA: " << s << endl;
  exit(0);
}

const int m = 100;
const int q = 500;
const int id_and = 0;
const int id_or = 1;
const int id_xor = 2;
const int id_not = 3;
const int id_left = 4;
const int id_right = 5;
const int id_print = 6;

int instruction_count = 0;
unsigned reg[m];
int fibonacci[32];

void load_register(unsigned &bs, string s){
  bs = 0;
  for (int i = 0; i < 10; i++) { //lsb is s[9]
    if (s[9-i] == '1') bs |= (1<<i);
  }
}

string unload_register(unsigned &bs){
  string s;
  for (int i=31; i>=0; i--) {
    if (bs & (1<<i)) s += "1";
    else s += "0";
  }
  return s;
}

int read_register(unsigned &bs) {
  int res = 0;
  for (int i = 0; i < 32; i++) {
    if (bs & (1 << i)) res += fibonacci[i];
  }
  return res;
}

void execute_and(int t, int x, int y) {
  reg[t] = (reg[x] & reg[y]);
}

void execute_or(int t, int x, int y) {
  reg[t] = (reg[x] | reg[y]);
}

void execute_xor(int t, int x, int y) {
  reg[t] = (reg[x] ^ reg[y]);
}

void execute_not(int t, int x) {
  reg[t] = (~reg[x]);
}

void execute_left(int t, int x, int p) {
  reg[t] = (reg[x] << p);
}

void execute_right(int t, int x, int p) {
  reg[t] = (reg[x] >> p);
}

void print(int t,string name){
  string s = unload_register(reg[t]);
  int val = read_register(reg[t]);
  cout << name << " " << s << " (" << val << ")" << endl;
}

void execute_print(int t) {
  print(t, "register " + to_string(t));
}

struct Instruction {
  int type, t, x, y;

  void execute() {
    switch (type) {
      case id_and:
        execute_and(t, x, y);
        break;
      case id_or:
        execute_or(t, x, y);
        break;
      case id_xor:
        execute_xor(t, x, y);
        break;
      case id_not:
        execute_not(t, x);
        break;
      case id_left:
        execute_left(t, x, y);
        break;
      case id_right:
        execute_right(t, x, y);
        break;
      case id_print:
        execute_print(t);
        break;
      default:
        assert(false);
    }
  }
};

vector<Instruction> instructions;

vector<int> tokenize(string s) {
  stringstream S(s);
  vector<int> res;
  int k;
  while (S.peek()!=-1) {
    if (S >> k) {
      res.push_back(k);
    } else {
      S.clear();
      S.ignore(1, S.peek());
    }
  }
  return res;
}

void parse_command(string s){
  static string r      = "([0-9]|[1-9][0-9])";
  static string n32    = "([0-9]|[1-2][0-9]|3[0-1])";
  static regex r_add   = regex(r + "=" + r + "&" + r);
  static regex r_or    = regex(r + "=" + r + "\\|" + r);
  static regex r_xor   = regex(r + "=" + r + "\\^" + r);
  static regex r_not   = regex(r + "=~" + r);
  static regex r_left  = regex(r + "=" + r + "<<" + n32);
  static regex r_right = regex(r + "=" + r + ">>" + n32);
  static regex r_print = regex("\\." + r);

  vector<int> v = tokenize(s);

  if (regex_match(s, r_add)) {
    instruction_count++;
    instructions.push_back({
      id_and,
      v[0],
      v[1],
      v[2]
    });
  } else if (regex_match(s, r_or)) {
    instruction_count++;
    instructions.push_back({
      id_or,
      v[0],
      v[1],
      v[2]
    });
  } else if (regex_match(s, r_xor)) {
    instruction_count++;
    instructions.push_back({
      id_xor,
      v[0],
      v[1],
      v[2]
    });
  } else if (regex_match(s, r_not)) {
    instruction_count++;
    instructions.push_back({
      id_not,
      v[0],
      v[1]
    });
  } else if (regex_match(s, r_left)) {
    instruction_count++;
    instructions.push_back({
      id_left,
      v[0],
      v[1],
      v[2]
    });
  } else if (regex_match(s, r_right)) {
    instruction_count++;
    instructions.push_back({
      id_right,
      v[0],
      v[1],
      v[2]
    });
  } else if (regex_match(s, r_print)) {
    instructions.push_back({
      id_print,
      v[0]
    });
  } else {
    WA("Unable to parse "+s);
  }
}

int main(int argc, char *argv[]) {
  ifstream commands("out.txt");

  // precompute fibonacci values
  fibonacci[0] = 1;
  fibonacci[1] = 2;
  for (int x = 2; x < 32; x++) {
    fibonacci[x] = fibonacci[x-1] + fibonacci[x-2];
  }

  int n;
  string _n;

  if (!getline(commands,_n)) {
    WA("There is no input!");
  }

  try {
    n = stoi(_n);
  } catch (std::exception const &e) {
    WA("The first line should be the number of operations");
  }

  if (n < 0 || n > 1000) {
    WA("The value t should be between 0 and 1000");
  }

  for (int i = 0; i < n; i++) {
    string s;
    if (!getline(commands,s)) {
      WA("There are less than t operations");
    }
    s.erase(
      remove_if(
        s.begin(),
        s.end(),
        [](unsigned char x){ return std::isspace(x); }
      ),
      s.end()
    );
    parse_command(s);
  }

  string eof;
  if (commands >> eof) {
    WA("There are more than t operations");
  }
  
  cout << "Operations used: " << instruction_count << endl;
  if (instruction_count > q) {
    WA("Too many operations");
  }

  string a, b;
  cin >> a >> b;

  memset(reg, 0, sizeof(reg));
  load_register(reg[0], a);
  load_register(reg[1], b);

  int va = read_register(reg[0]), vb = read_register(reg[1]);
  print(0, "input 0");
  print(1, "input 1");

  for (auto i : instructions) i.execute();

  int vc = read_register(reg[2]);
  print(2, "output");

  if (va + vb != vc) {
    WA(to_string(va) + " + " + to_string(vb) + " != " + to_string(vc));
  }

  cout<<"AC"<<endl;
  return 0;
}
