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
int min_fire(int n,double e[]);

int main(){
	/*
	该程序用于利用最小二乘法计算最佳平方逼近多项式
	
	x 表示拟合点坐标
	y 表示拟合点函数值
	a 表示计算出的多项式系数
	n 表示拟合点个数
	degree 表示多项式次数
	m 表示多项式系数的个数
	xs 表示待求点 
	ys 表示待求点拟合函数值 
	*/
	int i,K=10000,t;
	double x[] = {-1.0,-0.8,-0.6,-0.4,-0.2,0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
	double y[] = {-0.8669,-0.2997,0.3430,1.0072,1.6416,2.2022,2.6558,2.9823,3.1755,3.2416,3.1974};
	double xs = 0.8,a_2 = 0,a_4 = 0, a2[2]={-10,10},a4[2]={-10,10},e[5];
	double ys,eps=1e-7,T0=10,p,b;
	double *a;

 	int n = 11;
	int degree = 2;
	int m;
	
	//多项式系数个数为多项式次数加1 
	m = degree + 1;
	
	//为多项式系数申请内存 
	a = (double *)malloc(sizeof(double)*m);
	
	for(i=0;i<=K;i++){

		//利用最小二乘法计算系数a 
		e[0]=least_square(n, x, y, m, a,a2[0],a4[0]);
		e[1]=least_square(n, x, y, m, a,a2[1],a4[0]);
		e[2]=least_square(n, x, y, m, a,a2[1],a4[1]);
		e[3]=least_square(n, x, y, m, a,a2[0],a4[1]);
		e[4]=least_square(n, x, y, m, a,a_2,a_4);
		t=min_fire(4,e);
		//printf("%d,%lf\n",t,e[t]);
		
		if(e[t]<=e[4]){
			if(t==0){
				a2[1]=(a2[0]+a2[1])/2.0;
				a4[1]=(a4[0]+a4[1])/2.0;
				a_2=(a2[0]+a2[1])/2.0;
				a_4=(a4[0]+a4[1])/2.0;
			}
			if(t==1){
				a2[0]=(a2[0]+a2[1])/2.0;
				a4[1]=(a4[0]+a4[1])/2.0;
				a_2=(a2[0]+a2[1])/2.0;
				a_4=(a4[0]+a4[1])/2.0;
			}
			if(t==2){
				a2[0]=(a2[0]+a2[1])/2.0;
				a4[0]=(a4[0]+a4[1])/2.0;
				a_2=(a2[0]+a2[1])/2.0;
				a_4=(a4[0]+a4[1])/2.0;
			}
			if(t==3){
				a2[1]=(a2[0]+a2[1])/2.0;
				a4[0]=(a4[0]+a4[1])/2.0;
				a_2=(a2[0]+a2[1])/2.0;
				a_4=(a4[0]+a4[1])/2.0;
			}	
		}
		if(e[t]>e[4]){
			b=rand()/(RAND_MAX+1.0);
			//printf("\n");
			//printf("b=%lf",b);
			//printf("\n");
			p=exp((e[4]-e[t])/T0);
			if(b<=p){
				if(t==0){
					a2[1]=(a2[0]+a2[1])/2.0;
					a4[1]=(a4[0]+a4[1])/2.0;
					a_2=(a2[0]+a2[1])/2.0;
					a_4=(a4[0]+a4[1])/2.0;
				}
				if(t==1){
					a2[0]=(a2[0]+a2[1])/2.0;
					a4[1]=(a4[0]+a4[1])/2.0;
					a_2=(a2[0]+a2[1])/2.0;
					a_4=(a4[0]+a4[1])/2.0;
				}
				if(t==2){
					a2[0]=(a2[0]+a2[1])/2.0;
					a4[0]=(a4[0]+a4[1])/2.0;
					a_2=(a2[0]+a2[1])/2.0;
					a_4=(a4[0]+a4[1])/2.0;
				}
				if(t==3){
					a2[1]=(a2[0]+a2[1])/2.0;
					a4[0]=(a4[0]+a4[1])/2.0;
					a_2=(a2[0]+a2[1])/2.0;
					a_4=(a4[0]+a4[1])/2.0;
				}
			}
			
		}
		
		T0=0.9*T0;
		//printf("\nT=%lf\n",T0);
		a2[0]=a_2-T0; a2[1]=a_2+T0;
		a4[0]=a_4-T0; a4[1]=a_4+T0;
				
		
		if(a2[1]-a2[0]<eps && a4[1]-a4[0]<eps){
			break;
		}
		//printf("%d\n",i);
		
		
	}

	
	//计算待求点拟合函数值 
	//ys = compute_value(m, a, xs);
	
	//输出计算结果 
	//output(n, m, x, y, a, xs, ys, e[t]);
	
	printf("拟合函数为:  ");
	printf("p(x)=%+.3lf %+.3lf sin( %+.3lf x ) %+.3lf cos( %+.3lf x )\n",a[0],a[1],a_2,a[2],a_4);
	printf("误差为:  %lf",e[t]);
	
	
	//释放内存 
	free(a); 
	
	return 0;
}

int min_fire(int n,double e[]){
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

//计算 获取 方程解 和 误差 
double least_square(int n, double *x, double *y, int m, double *a,double a2,double a4){
	int i,j; 
	double **A;
	double b[m];
	double e=0,r=0;
	
	//初始化 A b 
	A = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		A[i] = (double*)malloc(sizeof(double)*(m));
	}

	assemble_matrix(n,x,m,A,a2,a4);

	right_side(n,x,y,m,b,a2,a4);

	ColElim(m,A,b,a);
	
	for(i=0;i<n;i++){
		r=0;
		r+=a[0];
		r+=a[1]*sin(a2*x[i]);
		r+=a[2]*cos(a4*x[i]);
		
		e+=pow(r-y[i],2);
	}
	
	e=sqrt(e);
	
	return e;
	
	for( i=0; i<m; i++){
		free(A[i]);
	}
	free(A);
	
	
} 

//获取矩阵 
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

//获取右侧向量 
void right_side(int n, double *x, double *y, int m, double *b,double a2,double a4){
	int i;
	double psi[n];
	
	for(i=0;i<m;i++){
		basis_function(n,x,i,psi,a2,a4);
		b[i]=dot(n,y,psi);
	}
}
 
//生成基础向量 
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

//计算内积 
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

	printf("拟合点为: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", x[i]); 
	}
	printf("\n");
	
	printf("拟合点函数值为: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", y[i]); 
	}
	printf("\n");
	
	printf("误差为: %lf\n", e);
	
	//printf("待求点为: %f\n", xs);
	//printf("待求点拟合函数值为: %f\n", ys);
	
	return;
}

//拟合值计算 
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
       	}   // 选列主元
       	if(r!=k){
          	for(i=k; i<n; i++){
             	ki = k*n+i;
             	ri = r*n+i;             
             	t = A[k][i];
             	A[k][i] = A[r][i];
             	A[r][i] = t;
          	} // 交换矩阵 A 的 r,k 两行元素
          	t = b[k];
          	b[k] = b[r];
          	b[r] = t;  // 交换 b 的 r,k 两行元素 
       	}

	   	if(fabs(A[k][k])<1e-12){
          	//printf("fail\n"); 
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
       	//printf("fail\n"); 
       	return;
    }  
    
    Aii = A[n-1][n-1];
    if(fabs(Aii)<1e-12){
       	//printf("fail\n"); 
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
           //printf("fail\n"); 
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
