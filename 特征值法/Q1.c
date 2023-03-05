#include<stdio.h>
#include<math.h>

int main(){
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	void Matprintf(double A[],int m,int n);
	
	double A[16]={12,9,4,3,2,11,1,5,7,2,13,1,-5,2,-7,-10};
	double x[4]={-0.75667,2.3,0.1917,-0.7959};
	double y[4];
	int i;
	for(i=0;i<4;i++){
		y[i]=0;
	}
	
	MatMul(A,x,y,4,4,4);
	Matprintf(y,4,1);
}




//¾ØÕó³Ë·¨
void MatMul(double A[],double B[],double y[],int m,int n,int p){
	int i,j,k;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			y[(i-1)*p+j-1]=0;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*p+j-1]+=A[(i-1)*n+k-1]*B[(k-1)*p+j-1];
}



void Matprintf(double A[],int m,int n){
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			printf("%.4lf\t",A[(i-1)*m+j-1]);
		}
		printf("\n");
	}
}






