#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 100000;
const int MXN = 2000;
const int highCompFactor = 80;
const int maxComp = 83160, maxComp2 = 1680;
int sieve[MAX+69]={};
vector<int> prmlist;
vector<int> highCompositelist;
class ProblemSpec : public BaseProblemSpec
{
    protected:
      int N, K;
      vector<int> A;
      long long ans;

      void InputFormat()
      {
          LINE(N, K);
          LINE(A % SIZE(N));
      }

      void OutputFormat()
      {
          LINE(ans);
      }

      void GradingConfig()
      {
          TimeLimit(1);
          MemoryLimit(64);
      }

      void Constraints()
      {
          CONS(1 <= N && N <= MXN);
          CONS(1 <= K && K <= MAX);
          CONS(eachElementBetween(A, 1, MAX));
      }

      void Subtask1()
      {
          Points(100);
      }

    private:
      bool eachElementBetween(const vector<int> &A, int lo, int hi) 
      {
          for (int a: A) 
          {
             if (a < lo || a > hi) return false;
          }
          return true;
      }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
    protected:
      void SampleTestCase1()
      {
          Subtasks({1});
          Input({
            "3 6",
            "2 3 6"
          });
          Output({
            "2"
          });
      }

      void SampleTestCase2()
      {
          Subtasks({1});
          Input({
            "4 2",
            "1 1 2 2"
          });
          Output({
            "7"
          });
      }

      void BeforeTestCase()
      {
          A.clear();
      }

      void TestGroup1()
      {
          Subtasks({1});
          //Initialize Prime list and HC list
          init();

          //Max Cases
          CASE(N = MXN, A = randomVec(N,MAX,MAX), K = MAX);
          CASE(N = MXN, A = randomVec(N,1,MAX), K = randfromVector(A,1,MAX));
          CASE(N = MXN, A = randomVec(N,100,100), K = MAX);
          CASE(N = MXN, A = increaseVec(1,N), K = MXN / 2);
          CASE(N = MXN, A = increaseVec(MAX-N+1,N), K = 45);

          //Pure Random Cases
          CASE(N = rnd.nextInt(1,MXN), A = randomVec(N,1,MAX), K = rnd.nextInt(1,MAX));
          CASE(N = rnd.nextInt(1,MXN), A = randomVec(N,1,MAX), K = 840);
          CASE(N = rnd.nextInt(1,MXN), A = randomVec(N,1,MAX), K = randfromVector(A,1,MAX));

          //Prime Cases
          CASE(N = MXN, A = distinctPrime(N), K = randfromVector(A,1,MAX));
          CASE(N = MXN, A = rangePrime(N,1,MAX), K = rnd.nextInt(1, N));
          CASE(N = MXN, A = rangePrime(N,MAX,MAX), K = rnd.nextInt(1, MAX));
          CASE(N = MXN, A = rangePrime(N,MAX/2,MAX), K = randfromVector(A,1,MAX));

          //HC Cases
          CASE(N = MXN, A = randomVec(N,maxComp,maxComp), K = maxComp);
          CASE(N = MXN, A = highComposite(N,1,MAX), K = maxComp);
          CASE(N = MXN, A = highComposite(N,MAX/2,MAX), K = randfromVector(A,1,MAX));
          CASE(N = MXN, A = highComposite(N,2*MAX/3,MAX), K = randfromVector(A,1,MAX));

          //Multiples of each otther Cases
          CASE(N = MXN, A = randomMultiple(N,1), K = maxComp2);
          CASE(N = MXN, A = randomMultiple(N,2), K = maxComp2);
          CASE(N = MXN, A = randomMultiple(N,3), K = maxComp2);

          // answer is C(N, 1000)
          CASE(N = MXN; A = randomVec(N, MAX/1000, MAX/1000); K = MAX);

          // A is (upper-half) factors of K
          CASE(N = MXN; A = randomVecFromChoiceVector(N, {
            945, 990, 1080, 1155, 1188, 1260, 1320, 1386, 1485, 1512, 1540, 1848, 1890, 1980, 2079,
            2310, 2376, 2520, 2772, 2970, 3080, 3465, 3780, 3960, 4158, 4620, 5544, 5940, 6930, 7560,
            8316, 9240, 10395, 11880, 13860, 16632, 20790, 27720, 41580, 83160
          }); K = maxComp);
          CASE(N = MXN; A = randomVecFromChoiceVector(N, {
            40, 42, 48, 56, 60, 70, 80, 84, 105, 112, 120, 140, 168, 210, 240, 280, 336, 420, 560, 840, 
            680
          }); K = maxComp2);
      }

    private:

      vector<int> randomVec(int n,int l,int r)
      {
          vector<int> v;
          for (int i = 0; i < n;i++)
          {
              v.push_back(rnd.nextInt(l,r));
          }
          return v;
      }

      vector<int> increaseVec(int l,int n)
      {
          vector<int> v;
          for (int i = l; i < l + n;i++)
          {
              v.push_back(i);
          }
          rnd.shuffle(v.begin(),v.end());
          return v;
      }

      vector<int> distinctPrime(int n)
      {
          vector<int> v = prmlist;
          rnd.shuffle(v.begin(),v.end());
          while (v.size() > n) {v.pop_back();}
          return v;
      }

      int randfromVector(vector<int>& v,int l,int r)
      {
          int lf = lower_bound(v.begin(),v.end(),l) - v.begin();
          if (lf == v.size()) {lf--;}
          int rg = prev(upper_bound(v.begin(),v.end(),r)) - v.begin();
          return v[rnd.nextInt(lf,rg)];
      }

      vector<int> rangePrime(int n,int l,int r)
      {
          vector<int> v;
          for (int i = 0; i < n;i++)
          {
              v.push_back(randfromVector(prmlist,l,r));
          }
          return v;
      }

      vector<int> highComposite(int n,int l,int r)
      {
          vector<int> v;
          for (int i = 0; i < n;i++)
          {
              v.push_back(randfromVector(highCompositelist,l,r));
          }
          return v;
      }

      vector<int> randomMultiple(int n,int s)
      {
          vector<int> v;
          queue<int> q;
          q.push(s);
          while (v.size() < n)
          {
              if (q.size() == 0)
              {
                  q.push(s);
              }
              else
              {
                if (q.front() <= MAX)
                {
                    if (q.front() <= 10000) {q.push(q.front() * randfromVector(prmlist,1,MAX/10000));}
                    if (q.front() <= 1000) {q.push(q.front() * randfromVector(prmlist,1,MAX/1000));}
                    if (q.front() <= 100) {q.push(q.front() * randfromVector(prmlist,1,MAX/100));}
                    if (q.front() <= 10) {q.push(q.front() * randfromVector(prmlist,1,MAX/10));}
                    v.push_back(q.front());
                }
                q.pop();
              }
          }
          rnd.shuffle(v.begin(),v.end());
          return v;
      }

      vector<int> randomVecFromChoiceVector(int n, vector<int> choices)
      {
          vector<int> ret(n);
          for (int i = 0; i < n; ++i)
          {
              ret[i] = choices[rnd.nextInt(choices.size())];
          }

          return ret;
      }

      int factorAmount(int n,int prv,int sz)
      {
          if (n==1) {return (sz+1);}
          else
          {
              if (sieve[n] != prv) {return (sz+1) * factorAmount(n / sieve[n],sieve[n],1);}
              else {return factorAmount(n / sieve[n], sieve[n], sz + 1);}
          }
      }

      void init()
      {
          for (int i = 2; i <= MAX; i++)
          {
              if (!sieve[i])
              {
                  sieve[i] = i;
                  for (int j = i; j <= MAX; j+=i)
                  {
                      sieve[j] = i;
                  }
                  prmlist.push_back(i);
              }
          }
          cout<<"Prime List Size : "<<prmlist.size()<<"\n";
          
          for (int i = 2; i <= MAX; i++)
          {
              if (factorAmount(i,-1,0) >= highCompFactor) {highCompositelist.push_back(i);}
          }
          cout<<"High Composite List Size : "<<highCompositelist.size()<<"\n";
      }

};