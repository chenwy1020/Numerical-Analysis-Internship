#include<stdio.h>
#include<math.h>

// 高斯列主元消去法 
int main(){
	// 相应子程序
	void GaussianEliminationB(double A[], double b[], int n);
	void UpTriSys(double A[], double x[], double y[], int n);
	void MatrixPrint(double A[], int n, int m);
	 
	// 测试数据
	int i, j;
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2}; 
	double B[9]={2, 4, -2, 1, -1, 5, 4, 1, -2}; 
	double x[3]={0}; 
	double b[3]={6, 0, 2};
	double temp;
	
	// 输出矩阵 A
	printf("A =\n");
	MatrixPrint( A, 3, 3 );
	
	// 输出向量 b
	printf("b =\n");
	MatrixPrint( b, 1, 3); 
	
	// Gauss 列主元消元
	GaussianEliminationB(A, b, 3);
	printf("nA =\n");
	MatrixPrint( A, 3, 3);
	
	printf("nb =\n");
	MatrixPrint( b, 1, 3);
	
	// 求解上三角系统
	UpTriSys(A, x, b, 3);
	
	// 输出 x
	printf("x =\n");
	MatrixPrint(x, 1, 3);
	
	// 输出 nA*x
	printf("nA*x =\n");
	for(i=0; i<3; i++){
		temp=0;
		for(j=0; j<3; j++){
			temp=temp+A[i*3+j]*x[j];
		}
		printf("%lf\n", temp);
	} 
	
	// 输出 A*x
	printf("\nA*x =\n");
	for(i=0; i<3; i++){
		temp=0;
		for(j=0; j<3; j++){
			temp=temp+B[i*3+j]*x[j];
		}
		printf("%lf\n", temp);
	} 	 

	
	return 0;
}


// Gauss 主元消去法 
void GaussianEliminationB(double A[], double b[], int n){
	int i, j, k, r;
	double l, temp;
	
	// 主元消元 
	for(i=0; i<n-1; i++){
		// 挑主元
		r=i; temp=fabs(A[i*n+i]);
		for(k=i+1; k<n; k++){
			if(temp<fabs(A[k*n+i])){
				temp=fabs(A[k*n+i]);
				r=k;
			}
		} 
		
		if(r!=i){
			// 换主元
			for(k=i; k<n; k++){
				temp=A[r*n+k]; 
				A[r*n+k]=A[i*n+k];
				A[i*n+k]=temp;
			} 
			// 换右端向量
			temp=b[r]; b[r]=b[i]; b[i]=temp; 
		}
		
		// 消元 
		for(k=i+1; k<n; k++){
			// 对矩阵 A 变换 
			l=A[k*n+i]/A[i*n+i];  A[k*n+i]=0;	
			for( j=i+1; j<n; j++){
				A[k*n+j]=A[k*n+j]-l*A[i*n+j];
			}
			
			// 对右端向量 b 变换 
			b[k]=b[k]-l*b[i];
		}
	}
}

// 输出矩阵：若 A[i, j]<0.000001, 更正为 +0
void MatrixPrint(double A[], int n, int m){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(fabs(A[i*m+j])<0.000001){
				A[i*m+j]=0;
			}
			printf("%lf ", A[i*m+j]);
		}
		printf("\n");
	}
} 

// 上三角矩阵求解 
void UpTriSys(double A[], double x[], double y[], int n){
	int i, j;
	for(i=n-1; i>=0; i--){
		x[i]=y[i]/A[i*n+i];
		for(j=0; j<=i-1; j++){
			y[j]=y[j]-x[i]*A[j*n+i];
		}
	} 
}

