#include <bits/stdc++.h>
using namespace std;

#define MAX_DOUBLE 1e18
#define DEG360 2.0*acos(-1)
#define DEG1 2.0*acos(-1)/360.0
#define REP 1000000
#define REP2 300

double xa,ya,xb,yb,xo,yo,r;

int main() {
	scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
	scanf("%lf%lf%lf",&xo,&yo,&r);
	
	double best_deg = 0;
	double best_dist = MAX_DOUBLE;
	
	for (double i = 0; i <= DEG360; i += DEG360 / REP) {
		double xc = xo + r * cos(i);
		double yc = yo + r * sin(i);
		double dist = hypot(xa-xc, ya-yc) + hypot(xb-xc, yb-yc);
		
		if (dist < best_dist) {
			best_deg = i;
			best_dist = dist;
		}
	}
	
	double base = best_deg - DEG1;
	double top = best_deg + DEG1;
	
	for (int i = 0; i < REP2; i++) {
		double kiri = base + (top - base) / 3.0;
		double kanan = top - (top - base) / 3.0;
		
		double xc = xo + r * cos(kiri);
		double yc = yo + r * sin(kiri);
		double dist = hypot(xa-xc, ya-yc) + hypot(xb-xc, yb-yc);
		
		xc = xo + r * cos(kanan);
		yc = yo + r * sin(kanan);
		double dist2 = hypot(xa-xc, ya-yc) + hypot(xb-xc, yb-yc);
		
		if (dist > dist2) base = kiri; else top = kanan;
		best_dist = min(min(dist, dist2), best_dist);
	}

	printf("%.9lf\n", best_dist);
}

