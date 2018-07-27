#include <iostream>
using namespace std;
int main()
{
	char **s;
	*s="Miss you";
	*(s+9)="Look Me"
	while(*s){
		cout<<*s;
		*s++;
	}
}