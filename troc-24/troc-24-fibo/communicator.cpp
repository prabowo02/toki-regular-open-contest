#include <bits/stdc++.h>
using namespace std;

void WA(string reason) {
  cerr << "WA" << endl;
  exit(0);
}

void AC() {
  cerr << "AC" << endl;
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

int instruction_count = 0;
unsigned reg[m];
int fibonacci[32];

void load_register(unsigned &bs, int inp){
	bs=inp;
}

int read_register(unsigned &bs) {
    int res=0;
    for (int i = 0; i < 32; i++) {
        if (bs&(1<<i)) res += fibonacci[i];
    }
    return res;
}

void execute_and(int t, int x, int y) {
    reg[t] = (reg[x]&reg[y]);
}

void execute_or(int t, int x, int y) {
    reg[t] = (reg[x]|reg[y]);
}

void execute_xor(int t, int x, int y) {
    reg[t] = (reg[x]^reg[y]);
}

void execute_not(int t, int x) {
    reg[t] = (~reg[x]);
}

void execute_left(int t, int x, int p) {
    reg[t] = (reg[x]<<p);
}

void execute_right(int t, int x, int p) {
    reg[t] = (reg[x]>>p);
}

struct instruction {
    int type, t, x, y;

    void execute() {
        switch(type) {
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
            default:
                assert(false);
        }
    }
};

vector<instruction> instructions;

vector<int> tokenize(string s) {
    stringstream S(s);
    vector<int> res;
    int k;
    while(S.peek()!=-1) {
        if(S>>k)
            res.push_back(k);
        else
            S.clear(), S.ignore(1, S.peek());
    }
    return res;
}

void parse_command(string s){
	static string r="([0-9]|[1-9][0-9])";
	static string n32="([0-9]|[1-2][0-9]|3[0-1])";
	static regex r_add=regex(r+"="+r+"&"+r);
	static regex r_or=regex(r+"="+r+"\\|"+r);
	static regex r_xor=regex(r+"="+r+"\\^"+r);
	static regex r_not=regex(r+"=~"+r);
	static regex r_left=regex(r+"="+r+"<<"+n32);
	static regex r_right=regex(r+"="+r+">>"+n32);
	static regex r_print=regex("\\."+r);
	
	vector<int> v=tokenize(s);
	
	if (regex_match(s, r_add)){
		instruction_count++;
		instructions.push_back({
			id_and,
			v[0],
			v[1],
			v[2]
		});
	}
	else if (regex_match(s, r_or)){
		instruction_count++;
		instructions.push_back({
			id_or,
			v[0],
			v[1],
			v[2]
		});
	}
	else if (regex_match(s, r_xor)){
		instruction_count++;
		instructions.push_back({
			id_xor,
			v[0],
			v[1],
			v[2]
		});
	}
	else if (regex_match(s, r_not)){
		instruction_count++;
		instructions.push_back({
			id_not,
			v[0],
			v[1]
		});
	}
	else if (regex_match(s, r_left)){
		instruction_count++;
		instructions.push_back({
			id_left,
			v[0],
			v[1],
			v[2]
		});
	}
	else if (regex_match(s, r_right)){
		instruction_count++;
		instructions.push_back({
			id_right,
			v[0],
			v[1],
			v[2]
		});
	}
	else if (regex_match(s, r_print)){
		//do nothing here
	}
	else{
		WA("Invalid command");
	}
}

int main(int argc, char *argv[]) {
	ifstream in(argv[1]);
	
	//precompute fibonacci values
	fibonacci[0]=1;
	fibonacci[1]=2;
	for (int x = 2; x < 32; x++) {
		fibonacci[x] = fibonacci[x-1] + fibonacci[x-2];
	}
	
	int n;
	string _n;
	
	if (!getline(cin,_n)){
		WA("Incorrect output format");
	}
	
	try{
		n=stoi(_n);
	}
	catch(std::exception const & e){
		WA("Incorrect output format");
	}
	
	if (n<0 || n>1000){
		WA("Bad Constraints");
	}
	
	for (int i=0;i<n;i++){
		string s;
		if (!getline(cin,s)){
			WA("Incorrect output format");
		}
		s.erase(remove_if(s.begin(),
					s.end(),
					[](unsigned char x){return std::isspace(x);}
				)
		,s.end());
		parse_command(s);
	}
	
	string eof;
	if (cin >> eof){
		WA("Operations output format");
	}
	
	if (instruction_count > q){
		WA("Too many operations");
	}
	
	string __temp;
	in>>__temp;
	
	vector<pair<int,int> > tests;
	if (__temp=="sample"){
		tests.push_back({3,5});
	}
	else if (__temp=="full"){
		for (int a=0;a<(1<<10);a++) for (int b=0;b<(1<<10);b++){
			tests.push_back({a,b});
		}
	}
	else{
		WA("what the fuck?");
	}
	
	for (auto p:tests){
    int a = p.first, b = p.second;
		memset(reg,0,sizeof(reg));
		load_register(reg[0],a);
		load_register(reg[1],b);
		
		int va=read_register(reg[0]),vb=read_register(reg[1]);
		
		for (auto i:instructions) i.execute();
		
		int vc=read_register(reg[2]);
		
		if (va+vb!=vc) WA("Wrong value on register 2");
	}
	
	AC();
}
