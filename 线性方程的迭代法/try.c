#include<stdio.h>
#include<math.h>
int main(){
	double A[9]={1,2,3,4,5,6,7,8,9},p[3]={1,2,3},Ap[3];
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
			Ap[i]+=A[i*3+j]*p[j];
	}
	printf("%lf\n",Ap[0]);
	printf("%lf\n",Ap[1]);
	printf("%lf\n",Ap[2]);

	
}
