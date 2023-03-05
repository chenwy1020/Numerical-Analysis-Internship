//(2）继续编写多关键词字符串过滤函数： 
//void filterx( char *str, char *mask) ，
//    函数参数说明：参数 str 代表待检测的目标字符串；参数 mask 代表由"|"分隔的多个关键词构成的字符串；
//    函数功能说明：函数filterx用于在字符串str中检测是否存在与mask所指定的多个关键词中的任意一个相匹配的字符序列，若检索成功则将str中与对应关键词匹配的字符序列替换成字符个数相等的*号。
//（mask所描述的多个关键词之间用"|"符号(竖线字符）分隔）
//    如：若有 char c1[200]="abcdefgh", *c2="bc|ef";
///    则在运行 filterx(c1, c2) 之后，c1对应的字符串被替换为： a**d**gh
//若有 char c1[200]="abcdefgh", *c2="bc|cd|ef";
//
//（3）请在main函数中准备 目标字符串以及关键词，然后分别调用上述两个函数实现对应的功能（注：filter 单一关键词过滤；filterx 多关键词屏蔽），测试并输出过滤结果。假定目标字符串中不含有"|"(竖线字符）.

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


















