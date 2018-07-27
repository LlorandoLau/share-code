#include <unistd.h>
#include<fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

void isWhat(struct stat buf);
void info(struct stat buf);
int main()
{
	struct stat buf;
	int in=open("a.txt",O_RDONLY);
	fstat(in,&buf);
	info(buf);
}

void isWhat(struct stat buf)
{
	mode_t modes=buf.st_mode;
	if(S_ISBLK(modes))
		printf("is block file\n");
	else if(S_ISCHR(modes))
		printf("is char file\n");
	else if(S_ISDIR(modes))
		printf("is dir\n");
	else if(S_ISFIFO(modes))
		printf("is FIFO\n");
	else if(S_ISREG(modes))
		printf("is regular file\n");
	else if(S_ISLNK(modes))
		printf("is link\n");
}

void info(struct stat sb)
{
	       printf("I-node number:            %ld\n", (long) sb.st_ino);

           printf("Mode:                     %lo (octal)\n",
                   (unsigned long) sb.st_mode);

           printf("Link count:               %ld\n", (long) sb.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n",
                   (long) sb.st_uid, (long) sb.st_gid);

           printf("Preferred I/O block size: %ld bytes\n",
                   (long) sb.st_blksize);
           printf("File size:                %lld bytes\n",
                   (long long) sb.st_size);
           printf("Blocks allocated:         %lld\n",
                   (long long) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));


}