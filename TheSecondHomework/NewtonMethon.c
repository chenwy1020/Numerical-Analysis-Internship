#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//����һ����Ԫţ�ٵ����� ������Сֵ�����ں�������ķǸ��ԣ���Ȼ���ݶ�Ϊ0��ȡ����Сֵ��
//ת��Ϊ����������0�����⣬����ſɱȾ�����棬��ô����̩��չ���������������Ĵ𰸡� 
double newton_method(int n,int m,double *x,double *y,double *a1,double eps);
void ColElim(int n, double **A, double *b, double *x);
void mat_Jf(int n,int m,double **Jf,double*a,double*x,double*y);
void vec_f(int n,int m,double *f,double*a,double*x,double*y);
double max(int m,double *a);
double px(int m,double *a,double x);
void mat_orthogona(int m,double **Jf);

int main()
{
	//*x����ϵ�����꣬*y����ϵ�������
	//n is the number of ��ϵ�  
	//m is the dimention of ���� *a 
	double x[] = {-1.0,-0.8,-0.6,-0.4,-0.2,0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
	double y[] = {-0.8669,-0.2997,0.3430,1.0072,1.6416,2.2022,2.6558,2.9823,3.1755,3.2416,3.1974};
	double a[] = {1.3,2.2,1.1,0.9,1.8};
	double e,r,eps=1e-3;
	int n=11;
	int m=5;
	int i;	
	
	e=newton_method(n,m,x,y,a,eps);
	printf("���: %lf\n",e);
	printf("��������ֵΪ��%.6lf %.6lf %.6lf %.6lf %.6lf",a[0],a[1],a[2],a[3],a[4]);
	
	e=0.0;
	a[0]=1.329;
	a[1]=2.229;
	a[2]=1.477;
	a[3]=0.874;
	a[4]=1.759;
	for(i=0;i<n;i++){
		r=0;
		r=a[0]+a[1]*sin(a[2]*x[i])+a[3]*cos(a[4]*x[i]);
		e+=pow(r-y[i],2);
	}
	
	e = sqrt(e);
	printf("���Ϊ: %lf\n", e);
	
	
	return 0;
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

double newton_method(int n,int m,double *x,double *y,double *a1,double eps){
	int i,j,K=1000,k=0;
	double *a2;
	double dif=0.1;

	double **Jf;
	double *f;
	
	//�����ڴ�ռ䣬����ʼ�� 
	Jf = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		Jf[i] = (double*)malloc(sizeof(double)*(m));
	}
	f = (double *)malloc(sizeof(double )*(m)); 
	a2 = (double *)malloc(sizeof(double )*(m)); 
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			Jf[i][j]=0.0;
		}
		f[i]=0.0;
		a2[i]=0.0;
	}
	
	
	while( dif>eps && k<K)
	{
		vec_f(n,m,f,a1,x,y);
		
		for(i=0;i<m;i++){
			f[i]=-1.0*f[i];
		}
		
	    mat_Jf(n,m,Jf,a1,x,y) ;
	    
		//mat_orthogona(m,Jf);
		
	    ColElim(m, Jf, f, a2);
	    
	    dif=max(m,a2);//a2[]��ģ���ֵ 
	    
	    printf("dif = %lf\n",dif);
	    
		
		for(i=0;i<m;i++){
		    a1[i]=a1[i]+a2[i];
	    }
	    
	    k++;
	}
	return sqrt(dif);
	
}

void mat_Jf(int n,int m,double **Jf,double*a,double*x,double*y){
	int i,j;
	
	for(i=0;i<m;i++){
	 	for(j=0;j<m;j++){
	 		Jf[i][j]=0.0;
		 }
	 }
	 
	for(i=0;i<n;i++){
		Jf[0][0]+= 2;
		//2*(px(m,a,x[i])-y[i])
		Jf[1][0]+= 2*sin(a[2]*x[i]);            
		Jf[1][1]+= 2*pow(sin(a[2]*x[i]),2);
		//2*(px(m,a,x[i])-y[i])*sin(a[2]*x[i])
		Jf[2][0]+= 2*a[1]*x[i]*cos(a[2]*x[i]);  
		Jf[2][1]+= 2*a[1]*x[i]*cos(a[2]*x[i])*sin(a[2]*x[i])+2*(px(m,a,x[i])-y[i])*x[i]*cos(a[2]*x[i]);
		Jf[2][2]+= 2*pow(a[1]*x[i]*cos(a[2]*x[i]),2)       -2*(px(m,a,x[i])-y[i])*a[1]*pow(x[i],2)*sin(a[2]*x[i]);
		//2*(px(m,a,x[i])-y[i])*a[1]*x[i]*cos(a[2]*x[i])
		Jf[3][0]+= 2*cos(a[4]*x[i]); 
		Jf[3][1]+= 2*sin(a[2]*x[i])*cos(a[4]*x[i]);
		Jf[3][2]+= 2*a[1]*x[i]*cos(a[2]*x[i])*cos(a[4]*x[i]); 
		Jf[3][3]+= 2*pow(cos(a[4]*x[i]),2);
		//2*(px(m,a,x[i])-y[i])*cos(a[4]*x[i])
		Jf[4][0]-= 2*a[3]*x[i]*sin(a[4]*x[i]); 
		Jf[4][1]-= 2*sin(a[2]*x[i])*a[3]*x[i]*sin(a[4]*x[i]); 
		Jf[4][2]-= 2*a[1]*x[i]*cos(a[2]*x[i])*a[3]*x[i]*sin(a[4]*x[i]); 
		Jf[4][3]-= 2*cos(a[4]*x[i])*a[3]*x[i]*sin(a[4]*x[i])+2*(px(m,a,x[i])-y[i])*x[i]*sin(a[4]*x[i]);
		Jf[4][4]-= -2*pow(a[3]*x[i]*sin(a[4]*x[i]),2)+2*(px(m,a,x[i])-y[i])*a[3]*pow(x[i],2)*cos(a[4]*x[i]);
		//-2*(px(m,a,x[i])-y[i]) * a[3]*x[i]*sin(a[4]*x[i])
	} 
	
	for(i=0;i<m;i++){
	 	for(j=m-1;j>i;j--){
	 		Jf[i][j]=Jf[j][i];
		 }
	 } 
	 
 
}

void vec_f(int n,int m,double *f,double*a,double*x,double*y){
	int i;
	
	for(i=0;i<m;i++){
		f[i]=0;
	}
	for(i=0;i<n;i++){
		f[0]+=2*(px(m,a,x[i])-y[i]);
		f[1]+=2*(px(m,a,x[i])-y[i])*sin(a[2]*x[i]);
		f[2]+=2*(px(m,a,x[i])-y[i])*a[1]*x[i]*cos(a[2]*x[i]);
		f[3]+=2*(px(m,a,x[i])-y[i])*cos(a[4]*x[i]);
		f[4]-=2*(px(m,a,x[i])-y[i])*a[3]*x[i]*sin(a[4]*x[i]);
	}

}

double px(int m,double *a,double x){
	double px;
	px=a[0]+a[1]*sin(a[2]*x)+a[3]*cos(a[4]*x);
	return px;
	
}

double max(int m,double *a){
	int i;
	double p;
	p=fabs(a[0]);
	for(i=0;i<m;i++){
		if(p<fabs(a[i])){
			p=fabs(a[i]);
		}
	} 
	return p;
}

