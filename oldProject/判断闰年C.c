#include<stdio.h>


int main()
{	
	int n;
	scanf("%d",&n);
	int year;
	year = n; 
	
	while(year <= 2020)
	{
	
		if(year%4!=0)
			printf("%d ��������\n",year);
		else
			if(year%100!=0)
				printf("%d ������\n",year);
			else
				if(year%400==0)
					printf("%d ������\n",year);
				else
					printf("%d ��������\n",year);
	year = year + 1;
	}
	return 0;
							
}
 
