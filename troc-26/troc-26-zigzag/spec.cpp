#include <tcframe/spec.hpp>
using namespace tcframe;

bool cek(vector<int>&B){
    for(int i:B){
        if(i < 1 || i > 100000){
            return false;
        }
    }
    return true;
}

bool ceksum(vector<int>&B){
    int sum = 0;
    for(int i:B){
        sum += i;
    }
    for(int i:B){
        if(i > sum/2){
            return false;
        }
    }
    return true;
}

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> B; 
    string ans;

    void InputFormat() {
        LINE(N);
        LINE(B % SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= 10000);
        CONS(cek(B));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3",
            "1 2 3"
        });
        Output({
            "YES"
        });
    }

    void SampleTestCase2() {
        Input({
            "2",
            "2 1"
        });
        Output({
            "NO"
        });
    }

    vector<int>C(int N){
        vector<int>ret;
        do{
            ret.clear();
            for(int i=1; i<=N; i++){
                ret.push_back(rnd.nextInt(1, 100000));
            }
        }while(!ceksum(ret));
        return ret;
    }

    vector<int>D(int N){
        int sum = 0, rem = 100000-(N-1), pos = rnd.nextInt(1, N-1), temp;
        vector<int>ret;
        ret.resize(N);
        for(int i=1; i<=N; i++){
            if(i==pos){
                continue;
            }
            temp = rnd.nextInt(0, min(100000/N, rem));
            ret[i-1] = temp+1;
            sum += temp+1;
            rem -= temp;
        }
        ret[pos-1] = sum+1;
        return ret;
    }

    vector<int>E(int N, int no){
        int sum = 0, rem = 100000-no-(N-1), temp;
        vector<int>ret;
        for(int i=1; i<N; i++){
            temp = rnd.nextInt(0, min(100000/N, rem));
            ret.push_back(temp+1);
            sum += temp+1;
            rem -= temp;
        }
        ret.push_back(sum+1+no);
        return ret;
    }

    void TestCases() {
        CASE(N = 213, B = C(N));
        CASE(N = 780, B = C(N));
        CASE(N = 8973, B = C(N));
        CASE(N = 9654, B = C(N));

        CASE(N = 213, B = D(N));
        CASE(N = 780, B = D(N));
        CASE(N = 8973, B = D(N));
        CASE(N = 9654, B = D(N));

        CASE(N = 105, B = E(N, 0));
        CASE(N = 105, B = E(N, 1));
        CASE(N = 9999, B = E(N, 0));
        CASE(N = 9999, B = E(N, 1));

        CASE(N = 120, B = E(N, 0));
        CASE(N = 10000, B = E(N, 0));
    }
};