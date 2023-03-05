#include<stdio.h>
#include<math.h>
//°¢Àï¾ºÈü£¬»¢»¢ÉúÍş 
void AABCP(int n,double p,double q)
{
	double P,a=0;
	int i;
	for(i=4;i<=n;i++)
	{
		
		P=2*q*(pow(p+q,i-1)-pow(p,i-1)-pow(q,i-1)-(i-1)*pow(q,i-2)*p)+(i-1)*p*p*pow(q,i-2)*(pow(2,i-2)-2);
		a+=P*i;
	}
	printf("%lf\n",a);
}

int  main()
{
	void AABCP(int n,double p,double q);
	int n=40;
	
	AABCP(n,1/3.0,1/3.0);
	AABCP(n,0.5,0.25);
	AABCP(n,0.4,0.3);
	AABCP(n,0.75,0.125);
}
