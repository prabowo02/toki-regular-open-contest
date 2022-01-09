#include <iostream>
using namespace std;

long long min_dist(long long T, long long F){
    return F*(F+1)/2;
}

long long max_dist(long long T, long long F){
    long long ret = F * (F-1)/2;
    if((T - (F-1)) % 2 == 0){
        T -= F-1;
        ret += ((F + (F + T/2 - 1)) * T)/2;
    }
    else{
        T -= F-1;
        ret += ((F + (F + T/2 - 1)) * (T-1))/2 + (F + T/2);
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