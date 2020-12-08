#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int A, B;
	int ans;

	void InputFormat() {
		LINE(A, B);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(0 <= A && A < 1000000007);
		CONS(0 <= B && B < 1000000007);
	}

	void Subtask1() {
		Points(100);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
		Input({
			"2 815380231"
		});
		Output({
			"4"
		});
	}

	void TestGroup1() {
		Subtasks({1});
		//simple TC
		CASE(A = 0, B = 0);
		CASE(A = 0, B = 1);
		CASE(A = 0, B = 2019);
		CASE(A = 1, B = 2020);
		CASE(A = 2, B = 4040);
		//add and multiply only might be a solution TC
			//comment explanantion: without modulo, with modulo (solution is minimum)
			//multiply, add a few times, multiply, add a few times
			CASE(A = 128, B = 542707328);//19 18
			CASE(A = 105, B = 473316294);//19 19
			CASE(A = 103, B = 485537299);//19 20
			CASE(A = 108, B = 457024986);//20 19
			CASE(A = 105, B = 432554703);//20 20
			CASE(A = 100, B = 424381786);//20 21
			CASE(A = 103, B = 424395922);//21 20
			CASE(A = 122, B = 546763493);//21 21
			CASE(A = 230, B = 967064888);//21 22
			CASE(A = 0, B = 32653287);//22 21
			//multiply twice, add a few times
			CASE(A = 238, B = 971169523);//19 20
			CASE(A = 113, B = 461121542);//20 21
			//multiply, add a few times, multiply
			CASE(A = 18, B = 142779660);//19 20
			CASE(A = 84, B = 416164440);//20 21
			//add a few times, multiply, add a few times
			CASE(A = 202, B = 444382);//19 19
			CASE(A = 36, B = 12338145);//19 20
			CASE(A = 244, B = 531241);//20 19
			CASE(A = 99, B = 28772868);//20 20
			CASE(A = 25, B = 88861);//20 21
			CASE(A = 71, B = 12412883);//21 20
			CASE(A = 89, B = 49136492);//21 21
			CASE(A = 226, B = 33107788);//21 22
			CASE(A = 29, B = 4177340);//22 21
		//stress TC (solution is 23 for all)
		CASE(A = 0, B = 83138284);
		CASE(A = 0, B = 109456821);
		CASE(A = 0, B = 273366441);
		//CASE(A = 0, B = 554968345);
		//CASE(A = 0, B = 706262172);
		//CASE(A = 0, B = 782708487);
		//CASE(A = 0, B = 833582344);
		//CASE(A = 0, B = 946014539);
		CASE(A = 1, B = 2);
		CASE(A = 1, B = 267219087);
		//CASE(A = 1, B = 620708541);
		//CASE(A = 1, B = 915190664);
		//CASE(A = 1, B = 925350070);
		//CASE(A = 1, B = 970278802);
		//21 exponents, modulo
		CASE(A = 52, B = 161911861);
		CASE(A = 487, B = 881218969);
		CASE(A = 750, B = 962076833);
		CASE(A = 1030, B = 455249513);
		CASE(A = 1186, B = 637829542);
		//CASE(A = 1314, B = 887953953);
		//CASE(A = 1340, B = 755423211);
		//CASE(A = 1344, B = 104107208);
		//CASE(A = 1572, B = 821743127);
		//CASE(A = 1642, B = 439569594);
		//CASE(A = 1780, B = 890148391);
		//10 exponents, 1 addition, 10 exponents, modulo
		CASE(A = 300, B = 283534625);
		CASE(A = 460, B = 964534709);
		CASE(A = 576, B = 828954096);
		CASE(A = 874, B = 120752835);
		CASE(A = 889, B = 729781327);
		//random TC
		for(int i = 0;i < 20;i ++){
			CASE(A = rnd.nextInt(1000000007), B = rnd.nextInt(1000000007));
		}
	}
};