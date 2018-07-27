#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
int main(int argc, char const *argv[])
{
	char s[80];
	int i;
	sscanf("I still miss","%4s",s);
	printf("%s\n", strerror(errno));
	for(i=0;i<80 && s[i]!='\0';i++)
		printf("%c\n", s[i]);

	return 0;
}