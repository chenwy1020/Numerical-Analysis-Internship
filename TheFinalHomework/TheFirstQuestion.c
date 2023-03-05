#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

double f(double x);
void composite_integral(int n, double left, double right, double *result);
double trapezoid(double left, double right);
double Simpson(double left, double right);
double Gauss(double left, double right);
void uniform_partition(int m, double left, double right, double *xs);

int main(){
	
	double left = -1.0, right = 1.0;
	double result[3]; 
	//result��ʾ3�ָ������ֹ�ʽ�ļ����� 
	// result[0]��ʾ�������ι�ʽ,  result[1]��ʾ����Simpson��ʽ, result[2]��ʾ����Gauss��ʽ
	int n = 16;

	composite_integral(n, left, right, result);
	
	//printf("��ȷֵΪ %f\n", sin(1.0));
	//printf("�������ι�ʽ���Ϊ %f\n", result[0]);
	//printf("���Ϊ %e\n", fabs(result[0]-sin(1.0)));
	//printf("����Simpson��ʽ���Ϊ %f\n", result[1]);
	//printf("���Ϊ %e\n", fabs(result[1]-sin(1.0)));
	printf("����Gauss��ʽ���Ϊ %f\n", result[2]);
	//printf("���Ϊ %e\n", fabs(result[2]-sin(1.0)));

	return 0;
}

double f(double x){

	double y; 
	
	y = exp(x*x+x);
	
	return y;
}

void composite_integral(int n, double left, double right, double *result){
	int i;
	double x[n+1];
	double temp;
	uniform_partition(n,left,right,x);
	
	temp=0.0;
	for(i=0;i<n;i++){
		temp+=trapezoid(x[i],x[i+1]);
	}
	result[0]=temp;
	
	temp=0.0;
	for(i=0;i<n;i++){
		temp+=Simpson(x[i],x[i+1]);
	}
	result[1]=temp;
	
	temp=0.0;
	for(i=0;i<n;i++){
		temp+=Gauss(x[i],x[i+1]);
	}
	result[2]=temp;	
	
}
 
double trapezoid(double left, double right){
	double temp;
	
	temp=(right-left)*(f(left)+f(right))/2.0;
	
	return temp;
}
 
double Simpson(double left, double right){
	double temp;
	
	temp=(right-left)*(f(left)+4*f((left+right)/2.0)+f(right))/6.0;
	
	return temp;
}
 
double Gauss(double left, double right){
	double x0,x1,temp;
	
	x0=(1.0/2.0+pow(3,1.0/2.0)/6.0)*left+(1.0/2.0-pow(3,1.0/2.0)/6.0)*right;
	x1=(1.0/2.0-pow(3,1.0/2.0)/6.0)*left+(1.0/2.0+pow(3,1.0/2.0)/6.0)*right;
	
	temp=(right-left)*(f(x0)+f(x1))/2.0;
	
	return temp;
	
} 

void uniform_partition(int m, double left, double right, double *xs){
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
	h = (right-left) / m;
	
	//ÿ���ʷֵ����꼴Ϊ��˵�+����*���� 
	for(i=0;i<m+1;i++){
		xs[i] = left + h*i;
	}
	
}

