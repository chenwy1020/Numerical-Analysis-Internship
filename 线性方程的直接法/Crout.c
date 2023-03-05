#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(){
	// 相关函数声明 
	void Crout(double A[], int n);
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void MatriceMulti(double A[], double B[], double C[], int n, int k, int m);
	void MatrixPrint(double A[], int n);
	
	int i, j;
	
	// 测试数据
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	// 输出 A
	printf("A =\n");
	MatrixPrint(A, 3);
	
	// Crout 分解
	Crout(A, 3);
	
	// 输出下三角部分
	double L[9];
	MatrixLower(A, L, 3);
	printf("L =\n");
	MatrixPrint(L, 3);	
	
	// 输出单位上三角部分 
	double U[9];
	MatrixUpper(A, U, 3);
	printf("U =\n");
	MatrixPrint(U, 3);	 
	
	// 输出 L*U
	double LU[9];
	MatriceMulti(L, U, LU, 3,3,3);
	printf("\nL*U =\n");
	MatrixPrint(LU, 3); 
	
	return 0;
}

// Crout 算法做 LU 分解
void Crout(double A[], int n){
	int i, j, k;
	
	for(i=0; i<n; i++){
		// 生成矩阵 L 并存储到 A 的下三角部分 
		for(k=i; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[k*n+i]=A[k*n+i]-A[k*n+j]*A[j*n+i]; 
			}
		}
	
		// 生成矩阵 U 并存储到 A 的上三角部分
		for(k=i+1; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[i*n+k]=A[i*n+k]-A[j*n+k]*A[i*n+j];
			}
			A[i*n+k]=A[i*n+k]/A[i*n+i];
		}	 
	} 
} 

// 获取下三角部分
void MatrixLower(double A[], double L[], int n){
	int i, j;
	
	for(i=0; i<n; i++){	L[i*n+i]=A[i*n+i];}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			L[i*n+j]=0;
			L[j*n+i]=A[j*n+i];
		}
	}
}

// 获取上三角部分 
void MatrixUpper(double A[], double U[], int n){
	int i, j;
	
	for(i=0; i<n; i++){	U[i*n+i]=1;}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			U[j*n+i]=0;
			U[i*n+j]=A[i*n+j];
		}
	}
}

// 矩阵乘矩阵 C=AB
void MatriceMulti(double A[], double B[], double C[], int n, int k, int m){
	int i, j, w;
	double c;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			c=0;
			for(w=0; w<k; w++){
				c=c+A[i*k+w]*B[w*m+j];
			}
			C[i*m+j]=c;
		}
	}
} 

// 矩阵输出
void MatrixPrint(double A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%lf ", A[i*n+j]);
		}
		printf("\n");
	}
} 

