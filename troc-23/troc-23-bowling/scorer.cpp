#include <bits/stdc++.h>
using namespace std;

void ac() {
  puts("AC");
  exit(0);
}

void wa() {
  puts("WA");
  exit(0);
}

const long long maxn = 131072;
long long segtree[2*maxn], lazy[2*maxn], range[2*maxn][2];
long long selfloop[maxn];

void build(){
    for(int i=0; i<2*maxn; i++){
        segtree[i] = 0;
        selfloop[i] = 0;
    }
}

void update(long long idx, long long val){
    idx += maxn;
    while(idx>0){
        segtree[idx] += val;
        idx /= 2;
    }
}

long long query(pair<long long, long long> p){
    long long l = p.first + maxn;
    long long r = p.second + maxn;
    long long ret = 0;
    while(l<=r){
        if(l%2 == 1){ret += segtree[l];}
        if(r%2 == 0){ret += segtree[r];}
        l = (l+1)/2;
        r = (r-1)/2;
    }
    return ret;
}

long long c3(long long x){
    return x*(x-1)*(x-2)/6;
}

long long m, u, l, r;
vector<pair<long long, long long> > ranges[maxn], newranges[maxn];
vector<long long> vadd[maxn], vdec[maxn];

int main(int argc, char** argv){
    ifstream input(argv[1]);
    ifstream judgeOutput(argv[2]);
    ifstream contestantOutput(argv[3]);

    build();
    // Input
    if(!(contestantOutput >> m)){
        wa(); return 0;
    }
    if(m<=0 || m>100000){
        wa(); return 0;
    }
    while(m--){
        if(!(contestantOutput >> u >> l >> r)){
            // cout << "Not enough lines delivered" << endl; 
            wa(); return 0;
        }
        if(min(u,min(l,r)) < 1 || max(u,max(l,r)) > 1e5 || l>r){
            // cout << "Out of bounds" << endl; 
            wa(); return 0;
        }
        if(l<=u && u<=r){selfloop[u] = 1;}
        ranges[u].push_back({l,r});
    }
    string dummy;
    if ((contestantOutput >> dummy)){
        wa(); return 0;
    }

    long long lmin, rmax;
    for(int i=0; i<maxn; i++){
        // combining ranges
        if(ranges[i].size() > 0){
            sort(ranges[i].begin(), ranges[i].end());
            lmin = ranges[i][0].first; rmax = ranges[i][0].second;
            for(int j=1; j<ranges[i].size(); j++){
                if(ranges[i][j].first <= rmax){
                    rmax = max(rmax, ranges[i][j].second);
                }else{
                    newranges[i].push_back({lmin, rmax});
                    lmin = ranges[i][j].first;
                    rmax = ranges[i][j].second;
                }
            }
            newranges[i].push_back({lmin, rmax});
        }
        // add and decrease range in vertical
        // if(i < 10) cout << i;
        for(int j=0; j<newranges[i].size(); j++){
            /*if(i<10){
                cout << " " << newranges[i][j].first << newranges[i][j].second;
            }*/
            vadd[newranges[i][j].first].push_back(i);
            vdec[newranges[i][j].second].push_back(i);
        }
        // if(i < 10)cout << endl;
    }

    long long deg, ans = 0;
    for(int i=0; i<maxn; i++){
        for(int j=0; j<vadd[i].size(); j++){
            update(vadd[i][j], 1);
        }
        deg = query({0, maxn-1});
        for(int j=0; j<newranges[i].size(); j++){
            deg += newranges[i][j].second - newranges[i][j].first + 1 - query(newranges[i][j]);
        }
        for(int j=0; j<vdec[i].size(); j++){
            update(vdec[i][j], -1);
        }
        /*if(i<10){
            cout << i << " " << deg - selfloop[i] + query({0, maxn-1}) << endl;
        }*/
        ans += c3(deg - selfloop[i]);
    }
    long long k; input >> k;
    if(k == ans){
        ac();
    }else{
        wa();
    }
    return 0;
}
