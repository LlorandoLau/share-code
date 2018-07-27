#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int num,char* arr[])
{
	char *var,*value;

	var=arr[1];
	value=getenv(var);
	if(value)
		printf("Variable %s has value %s\n",var,value );
	else
		printf("Variable %s has no value\n",var );

	if(num==3)
	{
		value=getenv(arr[1]);
		char *str;
		strcpy(str,value);
		strcat(str,"=");
		strcat(str,arr[2]);
		printf("Is ready to put %s into environ\n",str );
		if(putenv(str)!=0)
		{
			printf("%s\n",getenv(value));
		}
	}
}