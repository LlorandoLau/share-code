#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	char c[1024];
	int in=open("a.txt",O_RDONLY);
	int out=open("b.out",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	while(read(in,c,1024)>0)
		write(out,c,1024);
	exit(0);
}