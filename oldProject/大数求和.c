#include<stdio.h>
#include<string.h>

int Input(char *pA, int *psize)
{
	char *s[51]={'\0'};
	int i;
	gets(*s);
	for(i=0;*s[i]!='\0';i++);
	*psize = i;
	for(i=0;i<*psize;i++)
		pA[i]=*s[*psize-1-i];
}
int Output(char *pA, int psize)
{
	int i;
	for(i=psize-1;i>=0;i--)
		printf("%c",pA[i]);
}
int Add(char *pA1, int psize1,char *pA2, int psize2, char *pA, int *psize)
{
	int t=0,s=0;
	int i;
	pA[0]='1';
	for(i=0;pA[i]!='\0';i++)
	{
		s=pA1[i]-'0'+pA2[i]-'0';
		pA[i]=(s+t)%10+'0';
		t=(s+t)/10;
	}
	 *psize=i;
}
int main()
{
	char pA1[51],pA2[51],pA[51];
	int psize1,psize2,psize;
	Input(pA1, &psize1);
	Input(pA2, &psize2);
	Output(pA1,psize1);
	Output(pA2,psize2);
	Add(pA1, psize1, pA2, psize2, pA, &psize);
	Output(pA,psize);
	return 0;
}

