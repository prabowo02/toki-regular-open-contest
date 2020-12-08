#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream input, judgeOut, contestantOut;

void ac() {
    puts("AC");
    exit(0);
}

void wa() {
    puts("WA");
    exit(0);
}

void checkAC(){
    string dummy;
    if(contestantOut >> dummy) wa();
    else ac();
}

template <class T>
inline void getInput(T &a){ if(!(contestantOut >> a)) wa(); }

int main(int argc, char** argv) {

    input = ifstream(argv[1]);
    judgeOut = ifstream(argv[2]);
    contestantOut = ifstream(argv[3]);

    int N, M; input >> N >> M;
    vector<vector<char>> grid(N, vector<char>(M));

    for(int i = 0;i < N;i++) for(int j = 0;j < M;j++){
        getInput(grid[i][j]);
        if(grid[i][j] != 'B' && grid[i][j] != 'W') wa();
    }

    for(int i = 0;i < N-1;i++){
        for(int j = 0;j < M;j++){
            if(j != 0 && grid[i+1][j-1] == grid[i][j]) wa();
            if(j != M-1 && grid[i+1][j+1] == grid[i][j]) wa();
        }
    }

    checkAC();
    
    return 0;
}