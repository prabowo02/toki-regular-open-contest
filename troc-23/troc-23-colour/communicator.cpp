#include <bits/stdc++.h>
using namespace std;

int wa() {
    cerr<<"WA\n";
    return 0;
}

int ac() {
    cerr<<"AC\n";
    // cerr<<"queries = "<<count<<'\n';
    return 0;
}

long long _gcd(long long num1, long long num2){
    if (num1 == 0){
        return num2;
    }else if(num2 % num1){
        return _gcd(num2 % num1, num1);
    }else{
        return num1;
    }
}
long long type, seed;
char c;
long long a, b, nbGuess=0, color;
long long guesses[250], replies[250], nbDistinctGuess=0;

int isGuessed(long long x){
    for(int i=0; i<nbDistinctGuess; i++){
        if(x==guesses[i]){return i;}
    }
    return -1;
}
void ins(){ //nambahin a dalam guesses, harus ttp sorted
    int idx=0;
    while(idx<nbDistinctGuess && guesses[idx]<a){idx++;}
    for(int i=nbDistinctGuess; i>idx; i--){
        guesses[i] = guesses[i-1];
        replies[i] = replies[i-1];
    }
    //cout << idx << endl;
    guesses[idx] = a;
    replies[idx] = color;
    nbDistinctGuess++;
}
/*
long long objective
int objGuess(){ //objective function, AI wants to minimize
    long long ret = 1;
    for(int i=0; i<=nbGuess; i++){
        for(int j=i+1; j<=nbGuess; j++){
            for(int k=j+1; k<=nbGuess; k++){
                for(int l=)
            }
        }
    }
}
*/

const int mod = 104729; //random prime over 
int rndOnGuess[mod];
int rand_perm[4];
void init(){
    srand(seed);
    for(int i=0; i<mod; i++){
        rndOnGuess[i] = rand()%4+1;
    }
    // random permutation 1-4
    for(int i=0; i<4; i++) rand_perm[i] = i + 1;
    for(int i=0; i<4; i++){
        int toSwap = rand()%4;
        int temp = rand_perm[i];
        rand_perm[i] = rand_perm[toSwap];
        rand_perm[toSwap] = temp;
    }
}
//literally the perfect response for kinon/pyqe solution
int ans[41][5] = {
    {1,1,2,3,4},
    {2,2,3,4,1},
    {3,3,4,1,2},
    {4,4,1,2,3},
    {1,2,1,3,4},
    {2,3,2,4,1},
    {3,4,3,1,2},
    {4,1,4,2,3},
    {1,2,3,1,4},
    {2,3,4,2,1},
    {3,4,1,3,2},
    {4,1,2,4,3},
    {1,2,3,4,1},
    {2,3,4,1,2},
    {3,4,1,2,3},
    {4,1,2,3,4},

    {2,1,1,3,4},
    {3,2,2,4,1},
    {4,3,3,1,2},
    {1,4,4,2,3},
    {2,1,3,1,4},
    {3,2,4,2,1},
    {4,3,1,3,2},
    {1,4,2,4,3},
    {2,1,3,4,1},
    {3,2,4,1,2},
    {4,3,1,2,3},
    {1,4,2,3,4},

    {2,3,1,1,4},
    {3,4,2,2,1},
    {4,1,3,3,2},
    {1,2,4,4,3},
    {2,3,1,4,1},
    {3,4,2,1,2},
    {4,1,3,2,3},
    {1,2,4,3,4},

    {2,3,4,1,1},
    {3,4,1,2,2},
    {4,1,2,3,3},
    {1,2,3,4,4},

    {1,1,2,3,4}
};
int reply(){
    if(type == 0){ //urut dari guesses
        return nbGuess%4+1;
    }
    if(type == 1){ //random based on reply sequence
        return rand()%4+1;
    }
    if(type == 2){ //random based on a
        return rndOnGuess[a%mod];
    }
    if(type == 3){// reply based on pangkat prima
        long long cpy = a, mul = 1, ret = 0;
        for(int i=2; i<10000; i++){
            int cur = 0;
            while(cpy%i == 0){
                cur++;
                cpy/=i;
                mul *= -1;
            }
            ret += mul*cur;
        }
        return (ret%4 + 4)%4 + 1;
    }
    if(type == 4){ //kinon-pyqe solution, ambil dari pangkat 2 dan 3
        long long cpy = a, pw[2]={0,0}, cur, idx=0;
        for(int i=2; i<4; i++){
            cur = 0;
            while(cpy%i == 0){
                cur++;
                cpy/=i;
            }
            pw[i-2] = cur;
        }
        return ans[pw[0]%41][pw[1]%5];
    }
    if(type == 5){ //definisikan ada edge kalau a|b dan warnanya sama, AI minimalize edge
        int obj[5] = {0,0,0,0,0};
        for(int i=0; i<nbDistinctGuess; i++){
            obj[replies[i]] += !((a%guesses[i]) && (guesses[i]%a));
        }
        int ret = 0, cur = 1e9;
        
        //ngeceknya pakai rend_perm, biar ga smallest satisfy yang dikeluarin terus
        for(int i=0; i<4; i++){
            if(obj[rand_perm[i]]<cur){
                cur = obj[rand_perm[i]];
                ret = rand_perm[i];
            }
        }
        return ret;
    }
    if(type == 6){
        long long obj[5] = {0,0,0,0,0};
        for(int i=0; i<nbDistinctGuess; i++){
            obj[replies[i]] += !((a%guesses[i]) && (guesses[i]%a));
            for(int j=i+1; j<nbDistinctGuess; j++){
                long long s[3];
                if(replies[i] == replies[j]){
                    if(a<guesses[i]){
                        s[0] = a;
                        s[1] = guesses[i];
                        s[2] = guesses[j];
                    }else if(a>guesses[j]){
                        s[0] = guesses[i];
                        s[1] = a;
                        s[2] = guesses[j];
                    }else{
                        s[0] = guesses[i];
                        s[1] = guesses[j];
                        s[2] = a;
                    }
                }
                obj[replies[i]] += 1000*(s[0] == _gcd(s[1],s[2]));
                obj[replies[i]] += 1000*(!(s[1]%s[0]) && !(s[2]%s[1]) && (_gcd(s[1]/s[0], s[2]/s[1])==1));
                obj[replies[i]] += 1000*(_gcd(s[0],s[1])*s[2] == s[0]*s[1]);
            }
        }
        long long ret = 0, cur = 1e18;
        for(int i=0; i<4; i++){
            if(obj[rand_perm[i]]<cur){
                cur = obj[rand_perm[i]];
                ret = rand_perm[i];
            }
        }
        return ret;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    tc_in >> type >> seed;
    init();
    nbGuess = 0;
    nbDistinctGuess = 0;
    while((nbGuess<=200) && (cin >> c)){
        if(c == '?'){
            if(cin >> a){
                if(isGuessed(a)>=0){//udah pernah ditebak
                    cout << replies[isGuessed(a)] << endl;
                }else if(0<a && a<=1e18){//belum pernah ditebak
                    color = reply();
                    cout << color << endl;
                    ins();
                }else{
                    return wa();
                }
            }else{
                return wa();
            }
        }else if(c == '!'){
            if(cin >> a >> b){
                long long g = _gcd(a,b);
                int idx[4] = {isGuessed(g), isGuessed(a), isGuessed(b), isGuessed(a/g*b)};
                bool iswin = (a/g <= 1e18/b) && idx[0]>=0;
                for(int i=1; i<4; i++){
                    iswin = iswin && (idx[i]>=0) && (replies[idx[i]] == replies[idx[0]]);
                }
                iswin = iswin && (g < min(a, b));
                if(iswin){
                    return ac();
                }else{
                    return wa();
                }
            }else{
                return wa();
            }
        }else{
            return wa();
        }
        cout << flush;
        nbGuess++;
    }
    return wa();
}
