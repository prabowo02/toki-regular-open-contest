#include <bits/stdc++.h>
using namespace std;

pair<pair<int, int>, int> samecolored[41]; //idx 0,1 posisi,

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long pow2 = 1, pow3;
    for(int i=0; i<41; i++){
        pow3 = 1;
        long long c, colored[5] = {-1, -1, -1, -1, -1};
        for(int j=0; j<5; j++){
            cout << "? " << pow2*pow3 << endl;
            cout << flush;
            pow3 *= 3;
            cin >> c;
            if(colored[c] < 0){
                colored[c] = j;
            }else{
                samecolored[i] = {{colored[c], j}, c};
            }
        }
        pow2 *= 2;
    }
    for(long long i=0; i<40; i++){
        // cout << samecolored[i].first.first << " " <<  samecolored[i].first.second << " " << samecolored[i].second << endl;

        for(long long j=i+1; j<41; j++){
            if(samecolored[i] == samecolored[j]){
                // cout << i << " " << j << endl;
                cout << "! ";
                pow3 = 1;
                int k=0;
                while(k<samecolored[i].first.first){
                    k++; pow3 *= 3;
                }
                cout << (1ll<<j)*pow3 << " ";
                while(k<samecolored[i].first.second){
                    k++; pow3 *= 3;
                }
                cout << (1ll<<i)*pow3 << endl;
                return 0;
            }
        }
    }

}
