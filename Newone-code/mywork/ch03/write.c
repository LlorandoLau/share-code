#include <unistd.h>
#include <stdlib.h>

int main()
{
	if(write(1,"Here is my present!",18)<0)
		write(2,"I am sorry about the mistake",46);

	exit(0);
}