#include <iostream>
using namespace std;

long long min_dist(long long T, long long F){
    return F*(F+1)/2;
}

long long max_dist(long long T, long long F){
    long long ret = F * (F-1)/2, now = F;
    T -= F-1;
    while(T){
        if(T == 1){
            ret += now;
            T--;
        }
        else{
            ret += 2 * now;
            T -= 2;
        }
        now++;
    }
    return ret;
}

int main() {
    long long T, F, D;
    cin >> T >> F >> D;
    if(T >= F && D >= min_dist(T, F) && D <= max_dist(T, F)){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
}