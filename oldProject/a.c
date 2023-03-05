#include<stdio.h>
#define PI 3.141592653
int main()
{
	float s=0;
	int i;
	
	for(i=1; ;i++)
	{
		s+=1.0/(2*i+1);
		if(s>=PI/2.0) 
		{
			printf("1\n");
			break;
		}
	}
	printf("%f\n%d",s,i);	
	return 0;
} 
