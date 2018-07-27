#include "head.h"
int main()
{
	int c;
	FILE* in,*out;

	in=fopen("a.txt","r");
	out=fopen("b.out","w+");

	while((c=fgetc(in))!=EOF)
		fputc(c,out);
}