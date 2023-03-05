#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

double f(double x);
double composite_integral(int n, double left, double right);
double trapezoid(double left, double right);
void uniform_partition(int cells, double left, double right, double *xs);
void Romberg(int m, int n0, double left, double right, double *int_f);

int main(){
	
	double left = 0.0, right = 1.0;
	double *int_f;
	int m = 4;
	int n0 = 4;
	int i;
	
	int_f = (double *)malloc(sizeof(double)*m);
	
	Romberg(m, n0, left, right, int_f);
	
	printf("��ȷֵΪ %.16f\n", sin(1.0));
	
	for(i=0;i<m;i++){
		printf("\nС������Ϊ %d\n", n0*(int)(pow(2,i)));
		printf("Romberg���ַ����Ϊ %.16f\n", int_f[i]);
		printf("���Ϊ %e\n", fabs(int_f[i]-sin(1.0)));
	}
	
	free(int_f);
	
	return 0;
}

double f(double x){

	double y; 
	
	y = cos(x);
	
	return y;
}

double composite_integral(int n, double left, double right){
	int i;
	double x[n+1];
	double temp;
	uniform_partition(n,left,right,x);
	
	temp=0.0;
	for(i=0;i<n;i++){
		temp+=trapezoid(x[i],x[i+1]);
	}
	return temp;
	
}
 
double trapezoid(double left, double right){
	double temp;
	
	temp=(right-left)*(f(left)+f(right))/2.0;
	
	return temp;
}
 
void uniform_partition(int cells, double left, double right, double *xs){
	/*
	�ó������ڶ�������о����ʷ�, �����ʷֵ���������˵� 
	
	m ��ʾ�ʷֵ���� 
	left ��ʾ������˵�
	right ��ʾ�����Ҷ˵�
	xs ��ʾ�ʷֵ����� 
	*/	
	int i;
	double h;  
	
	//h��ʾ�ʷֲ��� 
	h = (right-left) / cells;
	
	//ÿ���ʷֵ����꼴Ϊ��˵�+����*���� 
	for(i=0;i<cells+1;i++){
		xs[i] = left + h*i;
	}
	
	return;
}

void Romberg(int m, int n0, double left, double right, double *int_f){
	
	double **int_table;
	int i,j,n;
	
	int_table = (double **)malloc(sizeof(double *)*m);
	for(i=0; i<m; i++ ){
		int_table[i]= (double*)malloc(sizeof(double)*m);
	}
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			int_table[i][j]=0.0;
		}
	}
	
	for(i=0;i<m;i++){
		n=n0*pow(2,i);
		int_table[i][0]=composite_integral(n,left,right);
	}
	for(j=1;j<m;j++){
		for(i=j;i<m;i++){
			int_table[i][j]=(pow(4,j)*int_table[i][j-1]-int_table[i-1][j-1])/(pow(4,j)-1);
		}
	}
	for(i=0;i<m;i++){
		int_f[i]=int_table[i][i];
	}

}









