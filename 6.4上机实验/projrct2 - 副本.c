#include<stdio.h>
void filter(char *str, char *mask)
{
	int i,j,n,e=1;
	for(i=0;*(str+i)!='\0';i++)
	{
		if(*mask==*(str+i))
			{
				for(j=0; (*(mask+j)!='\0')&&(*(str+i+j)!='\0'); j++)
					if(*(str+i+j) != *(mask+j)) e=0;
				if(e==1)
					for(n=i;n<i+j;n++)
						*(str+n)='*';
				i=i+j-1;			
			}
	}
}
void filterx(char *str, char *mask)
{
	int i,j,n,m=0,e=1,p;
	int y[10];	//����|λ����Ϣ 
	for(i=0,j=0;*(mask+i)!='\0';i++)
	{
		if(*(mask+i)=='|')
			{
				*(y+j)=i;
				j++;
			}	
	}
	p=j;
	for(m=0;m<p;m++)
	{
		
		for(i=0;*(str+i)!='\0';i++)
		{
			if(*(mask+*(y+m)+1)==*(str+i))
			{
				for(j=0; *(mask+*(y+m)+1+j)!='|'&& *(mask+*(y+m)+1+j)!='\0'&& *(str+i+j)!='\0'; j++)
					if(*(str+i+j) != *(mask+*(y+m)+1+j)) e=0;
				if(e==1)
					for(n=i;n<i+j;n++)
						*(str+n)='*';
				i=i+j-1;			
			}	
		}		
	}
	
}
int main()
{
	int i;
	char c1[200]="abcdefgh", *c2="|bc|ef";
	filterx(c1, c2);
	for(i=0;c1[i]!='\0';i++)
		printf("%c",c1[i]);
		
}


















