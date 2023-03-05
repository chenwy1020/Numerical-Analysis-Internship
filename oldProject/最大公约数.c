#include<stdio.h> 
int main()
{ 
	int m,n,i;
	m=int(input());
	n=int(input()); 
	i=n;
	while(i>=1)
	{
		if(m%i!=0)
		if(n%i!=0) 
			i=i-1;
		else
			printf("m n 的最大公约数是 %d",i);

	}

	return 0;
}


 
