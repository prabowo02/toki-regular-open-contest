#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int xa, ya, xb, yb, xo, yo, r;
	double ans;

	void InputFormat() {
		LINE(xa, ya, xb, yb);
		LINE(xo, yo, r);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void Constraints() {
		CONS(-1000000 <= xa && xa <= 1000000);
		CONS(-1000000 <= ya && ya <= 1000000);
		CONS(-1000000 <= xb && xb <= 1000000);
		CONS(-1000000 <= yb && yb <= 1000000);
		CONS(-1000000 <= xo && xo <= 1000000);
		CONS(-1000000 <= yo && yo <= 1000000);
		CONS(1 <= r && r <= 1000000);
		CONS(1LL * (xa-xo) * (xa-xo) + 1LL * (ya-yo) * (ya-yo) > 1LL * r * r);
		CONS(1LL * (xb-xo) * (xb-xo) + 1LL * (yb-yo) * (yb-yo) > 1LL * r * r);
		CONS(xa != xb || ya != yb);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void Subtask1() {
		Points(100);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
		Input({	"4 3 14 2",
				"8 7 2"});
		Output({"11.180339887"});
	}

	void TestGroup1() {
		Subtasks({1});

		assert(allDirection(-12345, 0, -67890, 0, 0, 0, 666));
		assert(allDirection(-42424, 0, -24242, 0, 0, 666, 666));
		assert(allDirection(-101010, 0, 909090, 0, 0, 0, 666));
		assert(allDirection(77777, 0, -13579, 0, 0, 666, 666));
		assert(allDirection(10*98765, 3*98765, -2*98765, -6*98765, 3*98765, 4*98765, 5*98765));
		assert(allDirection(10*98765, 3*98765, -2*98765, -6*98765, 3*98765, 4*98765, 5*98765-10));
		assert(allDirection(0, 0, 1000000, 0, 0, -1000000, 999999));
		assert(allDirection(-1, 0, 1000000, 0, 0, -1000000, 999999));
		assert(allDirection(-1000000, -1000000, -999999, -1000000, 1000000, 987654, 1000000));
		assert(allDirection(316511, 257693, 316512, 257692, 1000000, 987654, 1000000));
		
		for (int i = 0; i < 15; i++) {
			if (!randomFarAway()) i--;
		}
		
		for (int i = 0; i < 15; i++) {
			if (!randomSmallCircle()) i--;
		}
		
		for (int i = 0; i < 15; i++) {
			if (!randomLargeCircle()) i--;
		}
		
		for (int i = 0; i < 15; i++) {
			if (!randomLargeOuterCircle()) i--;
		}
	}

private:
	bool allDirection(int xa1, int ya1, int xb1, int yb1, int xo1, int yo1, int r1) {
		if (1LL * (xa1-xo1) * (xa1-xo1) + 1LL * (ya1-yo1) * (ya1-yo1) <= 1LL * r1 * r1) return false;
		if (1LL * (xb1-xo1) * (xb1-xo1) + 1LL * (yb1-yo1) * (yb1-yo1) <= 1LL * r1 * r1) return false;
		if (xa1 == xb1 && ya1 == yb1) return false;
	
		CASE(xa = xa1, ya = ya1, xb = xb1, yb = yb1, xo = xo1, yo = yo1, r = r1);
		CASE(xa = -ya1, ya = xa1, xb = -yb1, yb = xb1, xo = -yo1, yo = xo1, r = r1);
		CASE(xa = -xa1, ya = -ya1, xb = -xb1, yb = -yb1, xo = -xo1, yo = -yo1, r = r1);
		CASE(xa = ya1, ya = -xa1, xb = yb1, yb = -xb1, xo = yo1, yo = -xo1, r = r1);
	
		return true;
	}
	
	bool oneDirection(int xa1, int ya1, int xb1, int yb1, int xo1, int yo1, int r1) {
		if (1LL * (xa1-xo1) * (xa1-xo1) + 1LL * (ya1-yo1) * (ya1-yo1) <= 1LL * r1 * r1) return false;
		if (1LL * (xb1-xo1) * (xb1-xo1) + 1LL * (yb1-yo1) * (yb1-yo1) <= 1LL * r1 * r1) return false;
		if (xa1 == xb1 && ya1 == yb1) return false;
	
		int c = rnd.nextInt(1, 4);
	
		if (c == 1) CASE(xa = xa1, ya = ya1, xb = xb1, yb = yb1, xo = xo1, yo = yo1, r = r1);
		if (c == 2) CASE(xa = -ya1, ya = xa1, xb = -yb1, yb = xb1, xo = -yo1, yo = xo1, r = r1);
		if (c == 3) CASE(xa = -xa1, ya = -ya1, xb = -xb1, yb = -yb1, xo = -xo1, yo = -yo1, r = r1);
		if (c == 4) CASE(xa = ya1, ya = -xa1, xb = yb1, yb = -xb1, xo = yo1, yo = -xo1, r = r1);
	
		return true;
	}
	
	int p() {
		return rnd.nextInt(1, 1000000);
	}
	
	int q() {
		return rnd.nextInt(-1000000, 1000000);
	}
	
	int l() {
		return rnd.nextInt(900000, 1000000);
	}
	
	bool randomFarAway() {
		return oneDirection(-p(), -p(), -p(), -p(), p(), p(), p());
	}
	
	bool randomSmallCircle() {
		return oneDirection(q(), q(), q(), q(), q(), q(), rnd.nextInt(1, 10));
	}
	
	bool randomLargeCircle() {
		return oneDirection(q(), q(), q(), q(), q(), q(), l());
	}
	
	bool randomLargeOuterCircle() {
		return oneDirection(-l(), -l(), -l(), -l(), l(), l(), l());
	}
};
