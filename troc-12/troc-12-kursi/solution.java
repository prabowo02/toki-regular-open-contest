//Runs in 3 seconds on Patrick's computer
import java.util.*;

public class solution{
	//ideally use unsigned 32 bit integer instead of long to use less memory
	public static int maxChair=30;
	public static Boolean between (long lo, long mid, long hi){
		return (lo<mid&&mid<hi)||(lo>mid&&mid>hi);
	}
	public static long solve(long x, long y){
		long x1=0, y1=0, x2=1l<<maxChair, y2=1l<<maxChair, x3=2l<<maxChair, y3=2l<<maxChair;
		for(int i = maxChair-1;i >= 0;i --){
			if(between((x1+x2)>>1, x, (x2+x3)>>1)&&between((y1+y2)>>1, y, (y2+y3)>>1)){
				x1=(x1+x2)>>1;
				y1=(y1+y2)>>1;
				x3=(x2+x3)>>1;
				y3=(y2+y3)>>1;
			}else if(between(x2, x, x3)&&between(y1, y, y2)){
				x1=x3;
				x3=x2;
				y3=y2;
			}else if(between(x1, x, x2)&&between(y2, y, y3)){
				x3=x2;
				y1=y3;
				y3=y2;
			}else if(between(x1, x, x2)&&between(y1, y, y2)){
				x3=x2;
				y3=y2;
			}else{
				break;
			}
			x2=(x1+x3)>>1;
			y2=(y1+y3)>>1;
		}
		if(x1+1==x2&&y1+1==y2){
			return x+y+2;
		}else{
			return x+y;
		}
	}
	public static void main (String[] args) throws java.lang.Exception{
		Scanner scanner=new Scanner(System.in);
		int t;
		t=scanner.nextInt();
		for(int i = 0;i < t;i ++){
			long x, y;
			x=scanner.nextInt();
			y=scanner.nextInt();
			System.out.println(solve(x, y));
		}
	}
}
