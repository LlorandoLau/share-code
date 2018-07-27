#include "header.h"
#include "jpeglib.h"

int main(int argc, char const *argv[])
{
	char* path="1.jpeg";
	int fd=open(path,O_RDWR);

	struct stat statbuff;
	unsigned long fileSize=-1;
	stat(&statbuff);
	fileSize=statbuff.st_size;
	
	return 0;
}