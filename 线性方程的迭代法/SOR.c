#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// SOR ������ ��� Ax=b, 
//	ͣ��׼��|x_{k+1}-x_K|<\epsilon �� ������������ K 
//	������ҵͣ��׼�� \infty-���� 
int SORSolver(double A[], double b[], double x[], double x0[], int n, double epsilon, int K, double omega){
	int i, j, k=0;
	double err=1, temp;
	
	while(err>epsilon && k<K){// ͣ��׼�� 
		for(i=0; i<n; i++){
			temp=0;
			for(j=0; j<=i-1; j++){
				temp=temp+A[i*n+j]*x[j];
			}
			
			for(j=i+1; j<n; j++){
				temp=temp+A[i*n+j]*x0[j];
			}
			
			x[i]=(1-omega)*x0[i]-omega*(temp-b[i])/A[i*n+i];
		}
		
		k=k+1;
		
		// ����в\infty-����
		err=fabs(x[0]-x0[0])/(1+fabs(x[0]));
		for(i=1; i<n; i++){
			temp=fabs(x[i]-x0[i])/(1+fabs(x[i]));
			if(temp>err){ err=temp;}
		} 
		
		// ����
		for(i=0; i<n; i++){	x0[i]=x[i]; } 
	}
	
	return k;
} 


// JOR �㷨��� Ax=b 
//		ͣ��׼��|x_{k+1}-x_K|<\epsilon �� ������������ K 
//		������ҵͣ��׼�� \infty-���� 
int JORSolver(double A[], double b[], double x[], double x0[], int n, double epsilon, int K, double omega){
	int i, j, k=0;
	double err=1, temp;
	
	while(err>epsilon && k<K){// ͣ��׼�� 
		for(i=0; i<n; i++){
			temp=0;
			for(j=0; j<=i-1; j++){
				temp=temp+A[i*n+j]*x0[j];
			}
			
			for(j=i+1; j<n; j++){
				temp=temp+A[i*n+j]*x0[j];
			}
			
			x[i]=(1-omega)*x0[i]-omega*(temp-b[i])/A[i*n+i];
		}
		
		k=k+1;
		
		// ����в\infty-����
		err=fabs(x[0]-x0[0])/(1+fabs(x[0]));
		for(i=1; i<n; i++){
			temp=fabs(x[i]-x0[i])/(1+fabs(x[i]));
			if(temp>err){ err=temp;}
		} 
		
		// ����
		for(i=0; i<n; i++){	x0[i]=x[i]; } 
	}
	
	return k;
} 


int main(){
	int i, j;
	
	// ��������
	double A[16]={13, 9, 9, 11, 9, 11, 6, 9, 9, 6, 12, 7, 11, 9, 7, 10};
	double b[4]={42,35,34,37};
	double epsilon=0.000001;
	int K=5000;


	// ��ҵ
	double omega=0.5;
	int k;
	double x[4], x0[4]={0, 0, 0, 0};
	
	// SOR ������ 
	k=SORSolver(A, b, x, x0, 4, epsilon, K, omega);
	
	// JOR ������
	//k=JORSolver(A, b, x, x0, 4, epsilon, K, omega);
		 
	printf("step = %d\n", k);
	printf("x =\n");
	for(i=0; i<4; i++){
		printf("%lf\n", x[i]);
	}	 



/*
	// ��鲻ͬ�ɳ����Ӷ� SOR ����Ч�ʵ�Ӱ�� 
	double omega[100];
	int steps[100];
	for(i=0; i<100; i++){ omega[i]=0.02*(i+1);	}

	for(i=0; i<100; i++){
		// SOR �����������鲻ͬ�ɳ����ӶԵ���Ч�ʵ�Ӱ�� 
		double x[4], x0[4]={0, 0, 0, 0};	
		steps[i]=SORSolver(A, b, x, x0, 4, epsilon, K, omega[i]);
	} 
	
	// ���
	for(i=0; i<100; i++){
		printf("omega = %lf \t step = %d \n", omega[i], steps[i]);
	}
*/

/*	
	// ��鲻ͬ�ɳ����Ӷ� JOR ����Ч�ʵ�Ӱ�� 
	double omega[100];
	int steps[100];
	for(i=0; i<100; i++){ omega[i]=0.01*(i+1);	}

	for(i=0; i<100; i++){
		// SOR �����������鲻ͬ�ɳ����ӶԵ���Ч�ʵ�Ӱ�� 
		double x[4], x0[4]={0, 0, 0, 0};	
		steps[i]=JORSolver(A, b, x, x0, 4, epsilon, K, omega[i]);
	} 
	
	// ���
	for(i=0; i<100; i++){
		printf("omega = %lf \t step = %d \n", omega[i], steps[i]);
	}
*/
		
	return 0;
}




