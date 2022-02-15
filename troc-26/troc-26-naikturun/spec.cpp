#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec 
{
protected:
    int N, M;
    long long X;
    string s;
    vector<vector<long long> >A;

    void InputFormat() 
    {
        LINE(N,M);
        GRID(A) % SIZE(N,M);
    }

    void OutputFormat1() 
    {
        LINE(s);
    }
    
    void OutputFormat2()
    {
        LINE(s);
        LINE(X);
    }
    void GradingConfig() 
    {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1<=N && N<=200);
        CONS(1<=M && M<=200);
        CONS(eachElementBetween(A,-1,1e9));
    }

    bool eachElementBetween(const vector<vector<long long> >a, int lo, int hi)
    {
        int count=0;
        if(a.size()!=N)
        {
            return false;
        }
        for(int i=0;i<a.size();i++)
        {
            for(int j=0;j<a[i].size();j++)
            {
                if(a[i][j]==-1)
                {
                    count++;
                }
                if(lo>a[i][j]||a[i][j]>hi)
                {
                    return false;
                }
            }
            if(a[i].size()!=M)
            {
                return false;
            }
        }
        return (count==1);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> 
{
protected:
    void SampleTestCase1()
    {
        Input
        (
            {
                "2 4",
                "1 0 0 0",
                "0 0 -1 0"
            }
        );
        Output
        (
            {
                "YES",
                "1"
            }
        );
    }

    void SampleTestCase2() 
    {
        Input({
            "2 3",
            "3 2 -1",
            "0 0 0" 
        });
        Output({
            "NO",
        });
    }

    void SampleTestCase3()
    {
        Input
        (
            {
                "3 3",
                "0 0 0",
                "0 -1 0",
                "0 0 0"
            }
        );
        Output
        (
            {
                "YES",
                "0"
            }
        );
    }
    void TestGroup1() 
    {
        //kasus handmade
        CASE(N=2, M=2, A={{1,6},{2,-1}});
        CASE(N=2, M=2, A={{1000000000,999999999},{0,-1}});
        CASE(N=2, M=2, A={{8,0},{-1,0}});
        CASE(N=2, M=2, A={{4,-1},{9,4}});
        CASE(N=3, M=2, A={{5,-1},{2,5},{5,1}});
        
        //kasus random
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(false));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(false));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(false));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=rnd.nextInt(2,200), M=rnd.nextInt(2,200), generateRandom(true));
        CASE(N=200, M=200, generateRandom(true));
        
        //kasus ketika satu sisi berisi 1e9 dan sisanya 0
        CASE(N=158, M=170, generateOverflow(true,86,100));
        CASE(N=192, M=85, generateOverflow(false,101,45));
        CASE(N=200, M=200, generateOverflow(true,3,199));
        
        //kasus ketika semua sama
        CASE(N=200,M=200, generateAllEqual(0,69,96));
        CASE(N=200,M=200, generateAllEqual(1e9,69,96));
    }

    void generateOverflow(bool F,int p,int q)
    {
        A=vector<vector<long long>>(N, vector<long long>(M));
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                if((i+j)%2==F)
                {
                    A[i][j]=1e9;
                }
                else
                {
                    A[i][j]=0;
                }
            }
        }
        A[p][q]=-1;
    }

    void generateAllEqual(int x,int p,int q)
    {
        A=vector<vector<long long>>(N, vector<long long>(M));
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                A[i][j]=x;
            }
        }
        A[p][q]=-1;
    }

    void generateRandom(bool isYes) 
    {
        A=vector<vector<long long>>(N, vector<long long>(M));
        long long odd=0,even=0;
        bool again;
        do
        {
            for(int i=0;i<N;i++) 
            {
                for(int j=0;j<M;j++) 
                {
                    if((i+j)%2==0) 
                    {
                        A[i][j]=rnd.nextInt(1000000000);
                        even+=A[i][j];
                    }
                    else 
                    {
                        A[i][j]=rnd.nextInt(1000000000);
                        odd+=A[i][j];
                    }
                }
            }
            int p,q,count=0;
            do 
            {
                again=false;
                count++;
                p=rnd.nextInt(N);
                q=rnd.nextInt(M);
                bool f=(p+q)%2;
                if(f&&odd-A[p][q]<=even) 
                {
                    again=true;
                }
                else if(!f&&odd>=even-A[p][q]) 
                {
                    again=true;
                }
            } while(again!=isYes&&count<=10000);
            A[p][q]=-1;
        }
        while(again!=isYes);
    }
};
