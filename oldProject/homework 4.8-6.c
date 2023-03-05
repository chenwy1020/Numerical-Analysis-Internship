#include<stdio.h>
int main()
{
	float x,y;
	printf("ÇëÊäÈëxµÄÖµ"); 
	scanf("%f",&x);
	if(x<1)y=x;
	else if(x<=10)y=2*x-1;
	else y=3*x-1;
	printf("y= %f",y);
	return 0;
	
}
