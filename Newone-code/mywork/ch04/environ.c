#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int num,char* arr[])
{
	char *var,*value;
	if(num==1 || num>3)
	{
		fprintf(stderr, "We will not do this again\n");
		exit(0);
	}
	var=arr[1];
	value=getenv(var);
	if(value)
		printf("Variable %s has value %s\n",var,value );
	else
		printf("Variable %s has no value\n",var );

	if(num==3)
	{
		value=arr[2];
		char *str=malloc(strlen(arr[1])+strlen(arr[2])+2);
		strcpy(str,var);
		strcat(str,"=");
		strcat(str,value);
		printf("Is ready to put %s into environ\n",str );
		if(putenv(str)!=0)
		{
			fprintf(stderr,"%s\n",getenv(value));
			exit(1);
		}
	}
}