//(2��������д��ؼ����ַ������˺����� 
//void filterx( char *str, char *mask) ��
//    ��������˵�������� str ���������Ŀ���ַ��������� mask ������"|"�ָ��Ķ���ؼ��ʹ��ɵ��ַ�����
//    ��������˵��������filterx�������ַ���str�м���Ƿ������mask��ָ���Ķ���ؼ����е�����һ����ƥ����ַ����У��������ɹ���str�����Ӧ�ؼ���ƥ����ַ������滻���ַ�������ȵ�*�š�
//��mask�������Ķ���ؼ���֮����"|"����(�����ַ����ָ���
//    �磺���� char c1[200]="abcdefgh", *c2="bc|ef";
///    �������� filterx(c1, c2) ֮��c1��Ӧ���ַ������滻Ϊ�� a**d**gh
//���� char c1[200]="abcdefgh", *c2="bc|cd|ef";
//
//��3������main������׼�� Ŀ���ַ����Լ��ؼ��ʣ�Ȼ��ֱ����������������ʵ�ֶ�Ӧ�Ĺ��ܣ�ע��filter ��һ�ؼ��ʹ��ˣ�filterx ��ؼ������Σ������Բ�������˽�����ٶ�Ŀ���ַ����в�����"|"(�����ַ���.

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
	int i,j,n,e=1;
	int *y;
	for(i=0;*(mask+j)!='0';i++);
	for(i=0;*(str+i)!='\0';i++)
	{
		if(*mask==*(str+i))
			{
				for(j=0; *(mask+j)!='|'&& *(mask+j)!='0'&& *(str+i+j)!='\0'; j++)
					if(*(str+i+j) != *(mask+j)) e=0;
				if(e==1)
					for(n=i;n<i+j;n++)
						*(str+n)='*';
				i=i+j-1;			
			}
		
			
		
	}
	for(i=0;str[i]!='\0';i++)
		printf("%c",str[i]);
	
}
int main()
{
	int i;
	char c1[200]="abcdef", c2[3]="cd";
	filter(c1, c2);
	for(i=0;c1[i]!='\0';i++)
		printf("%c",c1[i]);
		
}


















