#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MXN = 1e9, MXM = 5e4;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, X, Y, C, D, M1, M2;
  long long ANS;

  void InputFormat() { LINE(N, X, Y, C, D, M1, M2); }

  void OutputFormat() { LINE(ANS); }

  void Constraints() {
    CONS(1 <= N && N <= MXN);
    CONS(1 <= M1 && M1 <= MXM);
    CONS(1 <= M2 && M2 <= MXM);
    CONS(0 <= X && X < M1);
    CONS(0 <= C && C < M1);
    CONS(0 <= Y && Y < M2);
    CONS(0 <= D && D < M2);
  }

  void Subtask1() {}

 private:
  

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({"3 1 2 3 4 7 11"});
    Output({"48"});
  }

  void TestGroup1() {
    Subtasks({1});

    SmallTC();
    LargeTC();

  }

 private:
  void SmallTC(){
    
    // Random Small TC
    for(int i = 0;i < 3; ++i){
      CASE(
        N = rnd.nextInt(1, 100000), 
        M1 = rnd.nextInt(1, MXM), 
        M2 = rnd.nextInt(1, MXM),
        X = rnd.nextInt(0, M1),
        Y = rnd.nextInt(0, M2),
        C = rnd.nextInt(0, M1),
        D = rnd.nextInt(0, M2)
      );
    }

    // Manual Small TC
    CASE(N = 10, X = 3, Y = 10, C = 2, D = 3, M1 = 10, M2 = 11); 
    CASE(N = 10, X = 3, Y = 10, C = 2, D = 3, M1 = 8, M2 = 11); 
    CASE(N = 5, X = 3, Y = 2, C = 3, D = 2, M1 = 4, M2 = 4);
    CASE(N = 9, X = 3, Y = 2, C = 3, D = 2, M1 = 5, M2 = 5);
    CASE(N = 10, X = 3, Y = 2, C = 3, D = 2, M1 = 5, M2 = 5);

    //No Cycle
    CASE(N = 39999, X = 25835, Y = 23989, C = 123, D = 21930, M1 = 40009, M2 = 40013);
    
    //Only one cycle
    CASE(N = 1000, X = MXM - 1, Y = MXM - 1, C = 1, D = 1, M1 = MXM, M2 = MXM);
    CASE(N = 80000, X = 25835, Y = 23989, C = 123, D = 21930, M1 = 40009, M2 = 40013);

    CASE(N = 1000, X = MXM - 1, Y = MXM - 1, C = 0, D = 0, M1 = MXM, M2 = MXM);
    CASE(N = 80000, X = 25835, Y = 23989, C = 0, D = 21930, M1 = 40009, M2 = 40013);

    CASE(N = 1, X = MXM - 1, Y = MXM - 1, C = 0, D = 0, M1 = MXM, M2 = MXM);

    //Ga semua cycle kena
    CASE(N = 1000, X = 70, Y = 80, C = 2, D = 2, M1 = 102, M2 = 10000);
    CASE(N = 1000, X = 35, Y = 80, C = 2, D = 2, M1 = 102, M2 = 10000);
    CASE(N = 7000, X = 0, Y = MXM - 1, C = 2132, D = 23123, M1 = 4000, M2 = MXM);

    //semua idx kena
    CASE(N = 1000, X = 70, Y = 80, C = 2, D = 2, M1 = 101, M2 = 729);
    CASE(N = 1000, X = 35, Y = 80, C = 2, D = 2, M1 = 101, M2 = 729);


    
  }

  void LargeTC(){

    // Random Large TC
    for(int i = 0;i < 10; ++i){
      CASE(
        N = rnd.nextInt(1, MXN), 
        M1 = rnd.nextInt(1, MXM), 
        M2 = rnd.nextInt(1, MXM),
        X = rnd.nextInt(0, M1),
        Y = rnd.nextInt(0, M2),
        C = rnd.nextInt(0, M1),
        D = rnd.nextInt(0, M2)
      );
    }

    for(int i = 0;i < 4; ++i){
      CASE(
        N = rnd.nextInt(1, MXN), 
        M1 = rnd.nextInt(1, MXM), 
        M2 = rnd.nextInt(1, MXM),
        X = rnd.nextInt(0, M1),
        Y = rnd.nextInt(0, M2),
        C = rnd.nextInt(0, 2),
        D = rnd.nextInt(0, 2)
      );
    }

    CASE(N = MXN, X = MXM - 1, Y = MXM - 1, C = 1, D = 1, M1 = MXM, M2 = MXM);

    CASE(N = MXN, X = 3, Y = 10, C = 2, D = 3, M1 = 10, M2 = 11); 
    CASE(N = MXN, X = 3, Y = 10, C = 2, D = 3, M1 = 8, M2 = 11); 
    CASE(N = MXN, X = 3, Y = 2, C = 3, D = 2, M1 = 4, M2 = 4);
    CASE(N = MXN - 1, X = 3, Y = 2, C = 3, D = 2, M1 = 5, M2 = 5);
    CASE(N = MXN, X = 3, Y = 2, C = 3, D = 2, M1 = 5, M2 = 5);

    //Normal Cycle
    CASE(N = MXN, X = MXM - 1, Y = MXM - 1, C = 1, D = 1, M1 = MXM, M2 = MXM);
    CASE(N = MXN, X = 25835, Y = 23989, C = 123, D = 21930, M1 = 40009, M2 = 40013);

    //Ga semua cycle kena
    CASE(N = MXN, X = 70, Y = 80, C = 2, D = 2, M1 = 102, M2 = 10000);
    CASE(N = MXN, X = 35, Y = 80, C = 2, D = 2, M1 = 102, M2 = 10000);
    CASE(N = MXN, X = 0, Y = MXM - 1, C = 2132, D = 23123, M1 = 4000, M2 = MXM);


    //semua idx kena
    CASE(N = 100000000, X = 70, Y = 80, C = 2, D = 2, M1 = 101, M2 = 729);
    CASE(N = 100000000, X = 35, Y = 80, C = 2, D = 2, M1 = 101, M2 = 729);
    CASE(N = MXN, X = 35, Y = 80, C = 2, D = 0, M1 = 101, M2 = 729);
    CASE(N = MXN, X = 35, Y = 80, C = 0, D = 0, M1 = 101, M2 = 729);

  }
};
