#include<stdio.h>
int main()
{
	float j=0,m;
	int i,n,e;
	scanf("%d",&n);
	
	for(i=1;i<=n;i++)
	{
		
		m=1.0/(2*i-1);
		if(m<=1e-6)break;
		e=1;
		if(i%2==0)e=-1;
		j=j+e*m;
		
		
	}
	printf("%f",j);
	return 0;
}
