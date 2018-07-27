#include <iostream>
using namespace std;
int main()
{
	char *a[]={
		'a','b','c'
	};
	char b=a;
	while(*b){
		cout<<*b;
		b++;
	}

	
}