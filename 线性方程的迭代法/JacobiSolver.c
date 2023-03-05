#include<stdio.h>
#include<math.h>

int main(){
	int JacobiSolver(double A[], double b[], double x[], double x0[], int n, double epsilon, int K);
	int i, j;
	
	// ��������
	double A[9]={20,-1,2,2,8,1,1,2,10},b[3]={21,11,13},x[3],x0[3]={0,0,0};
	double epsilon=0.000001;
	int K=1000, k;	
	
	// Jacobi ������ 
	k=JacobiSolver(A, b, x, x0, 3, epsilon, K);
	/*
	// ���
	printf("step = %d \n", k);
	printf("x=\n");
	for(i=0; i<3; i++){
		printf("%lf\n", x[i]);
	} 
	*/
	return 0;
}

//  Jacobi ������ ��� Ax=b, 
//	ͣ��׼��|x_{k+1}-x_K|<\epsilon �� ������������ K 
//	ͣ����׼�� \infty-���� 
int JacobiSolver(double A[], double b[], double x[], double x0[], int n, double epsilon, int K){
	int i,j,k;
	double err,temp;
	
	for(k=0,err=1; err>epsilon && k<K; k++){// ͣ��׼�� 
		for(i=0; i<n; i++){
			temp=0;
			for(j=0; j<=i-1; j++){
				temp=temp+A[i*n+j]*x0[j];
			}
			
			for(j=i+1; j<=n; j++){
				temp=temp+A[i*n+j]*x0[j];
			}
			
			x[i]=-(temp-b[i])/A[i*n+i];
		}
		// ����в\infty-����
		err=fabs(x[0]-x0[0]);
		for(i=1; i<n; i++){
			temp=fabs(x[i]-x0[i]);
			if(temp<err){ err=temp;}
		} 
		// ����
		for(i=0; i<n; i++){	x0[i]=x[i]; } 
		
		
		printf("x_(%d)\n",k+1);
		for(i=0; i<n; i++){
			printf("%lf\t",x[i]);
		}
		printf("\n");	
		
	}
	return k;
} 

