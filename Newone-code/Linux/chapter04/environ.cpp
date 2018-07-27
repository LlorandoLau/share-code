#include <iostream>
using namespace std;
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
		
	}
}