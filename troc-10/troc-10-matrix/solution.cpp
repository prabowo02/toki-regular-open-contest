//new.cpp
/*
Author : Hocky Yudhiono
1/14/2020 1:17:44 PM
*/
#include <iostream>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;
LL r,c,p;
LL isi[1005][1005];
LL BIT[1005][1005];
const LL MAXN = 1000;
void upd(LL posx,LL posy, LL val){
    if(posx <= 0) return;
    for(;posx <= MAXN;posx += (posx&(-posx))){
        LL curposy = posy;
        for(;curposy <= MAXN;curposy += (curposy&(-curposy))){
            BIT[posx][curposy] += val;
        }
    }
}

LL get(LL posx, LL posy){
    LL ret = 0;
    for(;posx > 0; posx -= (posx&(-posx))){
        LL curposy = posy;
        for(;curposy > 0; curposy -= (curposy&(-curposy))){
            ret += BIT[posx][curposy];
        }
    }
    return ret;
}

void updaterect(PLL st, PLL ed,LL val){
    if(val == 0) return;
    upd(st.fi,st.se,val);
    upd(st.fi,ed.se+1,-val);
    upd(ed.fi+1,st.se,-val);
    upd(ed.fi+1,ed.se+1,val);
}

#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#define GETCHAR getchar_unlocked
inline void fastll(LL &input_number) 
{
    input_number = 0;
    int ch = GETCHAR();
    int sign = 1;
    while(ch < '0' || ch > '9'){
        if(ch == '-') sign=-1;
        ch = GETCHAR();
    }
    while(ch >= '0' && ch <= '9'){
        input_number = (input_number << 3)+(input_number << 1) + ch-'0';
        ch = GETCHAR();
    }
    input_number *= sign;
}

void cant(){
    printf("TIDAK\n");
    exit(0);
}

int main(){
    fastll(r); fastll(c); fastll(p);
    for(int i = 1;i <= r;i++){
        for(int j = 1;j <= c;j++){
            fastll(isi[i][j]);
        }
    }
    for(int i = 1;i <= r;i++){
        if(i+p-1 > r) break;
        for(int j = 1;j <= c;j++){
            if(j+p-1 > c) break;
            LL curval = isi[i][j]-get(i,j);
            if(curval < 0) cant();
            PLL st = {i,j};
            PLL ed = {i+p-1,j+p-1};
            updaterect(st,ed,curval);
        }
    }
    for(int i = 1;i <= r;i++){
        for(int j = 1;j <= c;j++){
            LL curval = isi[i][j]-get(i,j);
            if(curval != 0) cant();
        }
    }
    printf("YA\n");
    return 0;
}