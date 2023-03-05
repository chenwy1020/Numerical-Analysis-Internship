#include<stdio.h>
#include<math.h>
int main(){
	
	double Newtonsqrt(double x,double a,int K);
	double x0,a,xk;
	int K;
	x0=1;a=3;
	K=3;
	xk = Newtonsqrt(x0,a,K);
	printf("x%d = %lf",K,xk);		
}
double Newtonsqrt(double x,double a,int K){
	double y;
	int i;
	for(i=0;i<K;i++){
		y=x/2.0+a/(2*x);
		x=y;	
	}
	return x;
}
