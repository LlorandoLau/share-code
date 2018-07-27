#include <stdio.h>
int main(){
	int a[]={1,3,6,4,5,9,40};
	int max=-1;
	int i;
	for(i=0;i<7;i++)
	{
		if(a[i]>max)
			max=a[i];
	}
	printf("%d\n",max );
}