#include<stdio.h>
#include<stdlib.h>
struct Student
{
	char *name;
	int age;
	float height;
	float weight;
	struct Student *p;
};
struct Student x1,x2;

int main()
{
	x1.name = "³ÂÎÄÓî";
	x1.age = 21;
	x1.height = 1.73;
	x1.weight = 68.5;
	
	x2=x1;
	printf("%s %d %f %f\n",x2.name, x2.age, x2.height, x2.weight);

}
