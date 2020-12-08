#include <bits/stdc++.h>
using namespace std;

void wa() {
    puts("WA");
    exit(0);
}

void ac() {
    puts("AC");
    exit(0);
}

int main(int argc, char *argv[]) {
    ifstream in, con;

    in.open(argv[1]);
    con.open(argv[3]);

    int m;
    int n;
    in >> n;

    con >> m;
    int mins = -100, last = -100;
    int sums = 0;
    for(int i = 0; i < m; ++i){
        int x;

        if(!(con >> x)){
            wa();
        }
        if(x <= 0){
            wa();
        }

        if(!i) mins = x;
        else{
            if(x < last){
                wa();
            }
        }
        last = x;
        sums += x;

    }

    string dummy;
    if(con >> dummy) {
        wa();
    }

    if((last - mins != 1) || (sums != n)){
        wa();
    }

    ac();
    return 0;
}
