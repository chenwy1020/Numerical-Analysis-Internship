#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double least_square(int n, double *x, double *y, int m, double *a,double a2,double a4);
void assemble_matrix(int n, double *x, int m, double **A,double a2,double a4);
void right_side(int n, double *x, double *y, int m, double *b,double a2,double a4);
void basis_function(int n, double *x, int i, double *phi_i,double a2,double a4);
double dot(int n, double *vector1, double *vector2);
void output(int n, int m,double *x, double *y, double *a,double xs, double ys,double e); 
void ColElim(int n, double **A, double *b, double *x);
double compute_value(int m, double *a, double xs);
int min(int n,double e[]);
void mat_orthogona(int m,double **Jf); 

int main(){
	/*
	�ó�������������С���˷��������ƽ���ƽ�����ʽ
	
	x ��ʾ��ϵ�����
	y ��ʾ��ϵ㺯��ֵ
	a ��ʾ������Ķ���ʽϵ��
	n ��ʾ��ϵ����
	degree ��ʾ����ʽ����
	m ��ʾ����ʽϵ���ĸ���
	xs ��ʾ����� 
	ys ��ʾ�������Ϻ���ֵ 
	*/
	int i,K=10000,t;
	double x[] = {-1.0,-0.8,-0.6,-0.4,-0.2,0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
	double y[] = {-0.8669,-0.2997,0.3430,1.0072,1.6416,2.2022,2.6558,2.9823,3.1755,3.2416,3.1974};
	double xs = 0.8,a2[2]={1.0,1.3},a4[2]={1.7,2.0},e[4];
	double ys,eps=1e-10;
	double *a;

 	int n = 11;
	int degree = 2;
	int m;
	
	//����ʽϵ������Ϊ����ʽ������1 
	m = degree + 1;
	
	//Ϊ����ʽϵ�������ڴ� 
	a = (double *)malloc(sizeof(double)*m);
	
	for(i=0;i<=K;i++){
		//������С���˷�����ϵ��a 
		e[0]=least_square(n, x, y, m, a,a2[0],a4[0]);
		e[1]=least_square(n, x, y, m, a,a2[1],a4[0]);
		e[2]=least_square(n, x, y, m, a,a2[1],a4[1]);
		e[3]=least_square(n, x, y, m, a,a2[0],a4[1]);
		t=min(4,e);
		printf("%d,%lf\n",t,e[t]);

		if(t==0){
			a2[1]=(a2[0]+a2[1])/2.0;
			a4[1]=(a4[0]+a4[1])/2.0;
		}
		if(t==1){
			a2[0]=(a2[0]+a2[1])/2.0;
			a4[1]=(a4[0]+a4[1])/2.0;
		}
		if(t==2){
			a2[0]=(a2[0]+a2[1])/2.0;
			a4[0]=(a4[0]+a4[1])/2.0;
		}
		if(t==3){
			a2[1]=(a2[0]+a2[1])/2.0;
			a4[0]=(a4[0]+a4[1])/2.0;
		}				
		
		if(a2[1]-a2[0]<eps && a4[1]-a4[0]<eps){
			break;
		}
		printf("%d\n",i);
	}

	
	//����������Ϻ���ֵ 
	//ys = compute_value(m, a, xs);
	
	//��������� 
	output(n, m, x, y, a, xs, ys, e[t]);
	
	printf("��Ϻ���Ϊ��\n");
	printf("%.12lf  %.12lf  %.12lf  %.12lf  %.12lf",a[0],a[1],(a2[0]+a2[1])/2,a[2],(a4[0]+a4[1])/2);
	
	//�ͷ��ڴ� 
	free(a); 
	
	return 0;
}

int min(int n,double e[]){
	int t,i;
	double p;
	p=e[0];
	for(i=0;i<n;i++){
		if(p>e[i]){
			t=i;
			p=e[i];
		}
	}
	
	return t;
}

//���� ��ȡ ���̽� �� ��� 
double least_square(int n, double *x, double *y, int m, double *a,double a2,double a4){
	int i,j; 
	double **A;
	double b[m];
	double e=0,r=0;
	
	//��ʼ�� A b 
	A = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		A[i] = (double*)malloc(sizeof(double)*(m));
	}

	assemble_matrix(n,x,m,A,a2,a4);

	right_side(n,x,y,m,b,a2,a4);

	ColElim(m,A,b,a);
	
	for(i=0;i<n;i++){
		e+=pow(a[0]+a[1]*sin(a2*x[i])+a[2]*cos(a4*x[i])-y[i],2);
	}
	
	e=sqrt(e);
	
	return e;
	
	for( i=0; i<m; i++){
		free(A[i]);
	}
	free(A);
	
	
} 

//��ȡ���� 
void assemble_matrix(int n, double *x, int m, double **A,double a2,double a4){
	int i,j;
	double psi_i[n],psj_j[n];
	 
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			
			basis_function(n,x,i,psi_i,a2,a4);
			basis_function(n,x,j,psj_j,a2,a4);
			A[i][j]=dot(n,psi_i,psj_j);
			//printf("%lf  ",A[i][j]);
		}
	} 
	
} 

//��ȡ�Ҳ����� 
void right_side(int n, double *x, double *y, int m, double *b,double a2,double a4){
	int i;
	double psi[n];
	
	for(i=0;i<m;i++){
		basis_function(n,x,i,psi,a2,a4);
		b[i]=dot(n,y,psi);
	}
}
 
//���ɻ������� 
void basis_function(int n, double *x, int i, double *phi_i,double a2,double a4){
	int k;
	if(i==0){
		for(k=0;k<n;k++){
			phi_i[k]=1;
		}
	}
	if(i==1){
		for(k=0;k<n;k++){
			phi_i[k]=sin(a2*x[k]);
		}
	}
	if(i==2){
		for(k=0;k<n;k++){
			phi_i[k]=cos(a4*x[k]);
		}
	}

} 

//�����ڻ� 
double dot(int n, double *vector1, double *vector2){
	int i;
	double temp=0.0;
	
	for(i=0;i<n;i++){
		temp+=vector1[i]*vector2[i];
	}
	
	return temp;
	
} 

void output(int n,int m, double *x, double *y, double *a,double xs, double ys,double e){
	
	int i;

	printf("��ϵ�Ϊ: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", x[i]); 
	}
	printf("\n");
	
	printf("��ϵ㺯��ֵΪ: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", y[i]); 
	}
	printf("\n");
	
	printf("���Ϊ: %lf\n", e);
	
	//printf("�����Ϊ: %f\n", xs);
	//printf("�������Ϻ���ֵΪ: %f\n", ys);
	
	return;
}

//���ֵ���� 
double compute_value(int m, double *a, double xs){
	int i;
	double ys=0.0;
	
	for(i=0;i<m;i++){
		ys+=a[i]*pow(xs,i);
	}
	
	return ys;
} 

void ColElim(int n, double **A, double *b, double *x){ 
    int i,j,k,r,kk,ik,ki,ri;
    double iMax, t, Aii;
          
    for(k=0; k<n-1; k++)    { 
       	r = k;
       	kk = k*n+k;
       	iMax = fabs(A[k][k]);
       	for(i=k+1; i<n; i++){
          	t = fabs(A[i][k]);
          	if(t>iMax){
             	r = i;
             	iMax = t;                       
          	}
       	}   // ѡ����Ԫ
       	if(r!=k){
          	for(i=k; i<n; i++){
             	ki = k*n+i;
             	ri = r*n+i;             
             	t = A[k][i];
             	A[k][i] = A[r][i];
             	A[r][i] = t;
          	} // �������� A �� r,k ����Ԫ��
          	t = b[k];
          	b[k] = b[r];
          	b[r] = t;  // ���� b �� r,k ����Ԫ�� 
       	}

	   	if(fabs(A[k][k])<1e-12){
          	printf("fail\n"); 
          	return;
       	}
       	for(i=k+1; i<n; i++){
          	ik=i*n+k;
          	A[i][k] /= A[k][k];
          	b[i] -= A[i][k]*b[k];  
          	for(j=k+1; j<n; j++){ 
             	A[i][j] -= A[i][k]*A[k][j];
            } 
          	A[i][k] = 0.0;
       	}
    }
        
    kk = k*n+k;
    if(fabs(A[k][k])<1e-12){
       	printf("fail\n"); 
       	return;
    }  
    
    Aii = A[n-1][n-1];
    if(fabs(Aii)<1e-12){
       	printf("fail\n"); 
       	return;
    }
    else{ 
        x[n-1] = b[n-1];
        if(Aii!=1.0){ 
           x[n-1] /= Aii;
        } 
    }
        
    for(i = n-2; i >= 0; i--){
        Aii = A[i][i];
        if(fabs(Aii)<1e-12){
           printf("fail\n"); 
           return;
        }
        else{
           	x[i] = 0.0;   
           	for(j = i+1; j < n; j++){   
              	x[i] += A[i][j]*x[j];
            } 
           	x[i] = b[i]-x[i];
           	if(Aii!=1.0){ 
              	x[i] /= Aii;
        	}
        }
    }
    
    return;
}

//Gram-Schmidt������ 
void mat_orthogona(int m,double **Jf){
	double **v;
	double v1[m],v2[m];
	int i,j,k;
	
	v = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		v[i] = (double*)malloc(sizeof(double)*(m));
	}
	
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			v[i][j]=Jf[i][j];
		}
	}
	
	for(j=1;j<m;j++){
		for(i=0;i<m;i++){
			v1[i]=Jf[i][j];
		}
		for(k=0;k<j;k++){
			
			for(i=0;i<m;i++){
				v2[i]=v[i][k];
			}

			for(i=0;i<m;i++){
				v[i][j]-=dot(m,v1,v2)*v[i][k]/dot(m,v2,v2);
			}
		}
	}
	
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			Jf[i][j]=v[i][j];
		}
	}
	/*
	printf("Jf=\n");
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			printf("%f\t", Jf[i][j]);
		}
		printf("\n");	
	} 
	*/
}
