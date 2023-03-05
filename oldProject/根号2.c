#include <stdio.h>

void main( )

{

int i;
float x=2;

for(i=1; i<=10; i++)
{
	x=(x*x+2)/2.0/x;
}

printf("%.15f",x);

}
