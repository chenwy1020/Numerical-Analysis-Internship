#include <graphics.h>	
#include<stdio.h>
#include <math.h> 	  	
int main()
{
	float dt=2,v1=50,v2=100,x1=0,x2=1000,h1=500,h2=0,s1=500,s2=100,sin,cos;	
	initgraph(1200, 720, 0);
	setcaption("The plane");
	setbkcolor(BLACK);
	setcolor(GREEN);
	for( ;s1>=0.5; )
	{
		s1=sqrt((x2-x1)*(x2-x1)+(h1-h2)*(h1-h2));
		sin=(h1-h2)/s1;
		cos=sqrt(1-sin*sin);
		
		moveto(x1,h1);
		x1=v1*dt+x1;
		lineto(x1,h1);
		
		moveto(x2,h2);
		x2=x2-v2*cos*dt;
		h2=v2*sin*dt+h2;
		lineto(x2,h2);
		
		s2=sqrt((x2-x1)*(x2-x1)+(h1-h2)*(h1-h2));
		dt=s2/s1*dt;
		s1=s2;	
	}
	getch();
	closegraph();
	return 0;
}
