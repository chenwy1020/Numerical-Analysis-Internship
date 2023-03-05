#include<stdio.h>
int main()
{
	int i,j,n,e,m,n_dollor,n_space;
	scanf("%d",&n);
	m=(n+1)/2;
	e=1;
	if(n%2==0)e=0;
	for(i=1;i<=m;i++)
	{
		n_dollor=2*i-e;
		n_space=m-i;
		for(j=1;j<=n_space;j++) printf(" ");
		for(j=1;j<=n_dollor;j++) printf("$");
		printf("\n");
	}
	for(i=1;i<=(n-m);i++)
	{
		n_dollor=n-2*i;
		n_space=i;
		for(j=1;j<=n_space;j++) printf(" ");
		for(j=1;j<=n_dollor;j++) printf("$");
		printf("\n");
	}
	
}
